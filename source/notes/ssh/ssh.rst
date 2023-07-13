
===
SSH
===

Todo:

* `Arch Wiki: OpenSSH <https://wiki.archlinux.org/index.php/OpenSSH#Two-factor_authentication_and_public_keys>`_
* `Arch Wiki: Google_Authenticator <https://wiki.archlinux.org/index.php/Google_Authenticator_(Русский)>`_
* https://blog.zsec.uk/locking-down-ssh-the-right-way/
* https://highon.coffee/blog/ssh-lateral-movement-cheat-sheet/
* https://johannes.truschnigg.info/writing/2022-07_advanced_ssh_usage/

Run commands on every login: ``~/.ssh/rc``.


Snippets
########
* SSH quoting
    - `Article <https://www.chiark.greenend.org.uk/~cjwatson/blog/ssh-quoting.html>`__
        + | In ``ssh server bash -lc "pwd;cd /tmp;pwd"`` the remote command becomes
          | ``sh -c 'bash -lc pwd; cd /tmp; pwd'``
        + The right way is ``ssh server 'bash -lc "cd /tmp;pwd"'``
    - `HN <https://news.ycombinator.com/item?id=27483077>`__
        + ``ssh server bash <script``
        + ``ssh server "echo $(cat script|base64 -w0) | base64 -d | bash"`` is same, but doesn't use stdin
        + ``echo command | tee | ssh bash -seux``
    - Run a script with ``ssh server "$(< script.sh)"``


.. include:: .tunneling.rst
.. include:: .signing.rst


Authorized Keys
###############
* `TIL authorized_keys files can contain more than just public keys <https://twitter.com/cyb3rops/status/1395009709787258882>`_
* `man 5 authorized_keys: AUTHORIZED_KEYS FILE FORMAT <https://www.commandlinux.com/man-page/man5/authorized_keys.5.html#lbAH>`_

Adding keys to accepted:

.. code-block:: sh

    cat lainiwa_id_rsa_key.pub >> ~/.ssh/authorized_keys
    # or, downloading from Github
    curl -q https://github.com/lainiwa.keys >> ~/.ssh/authorized_keys
    # or, same as above
    ssh-import-id gh:lainiwa

Options:

.. code-block:: sh

    from="*.sales.example.net,!pc.sales.example.net"    ssh-rsa AAAA...YZ== john@example.net
    command="dump /home",no-pty,no-port-forwarding      ssh-dss AAAA...YZ== mary@example.net
    permitopen="192.0.2.1:80",permitopen="192.0.2.2:25" ssh-dss AAAA...YZ== luke@example.net
    tunnel="0",command="sh /etc/netstart tun0"          ssh-rsa AAAA...YZ== jane@example.net
    command="echo go away"                              ssh-rsa AAAA...YZ== gary@example.net


Private Keys
############

Private Keys Surveillance
=========================
* `ssh whoami.filippo.io <https://blog.filippo.io/ssh-whoami-filippo-io>`_
* `Public SSH keys can leak your private infrastructure <https://rushter.com/blog/public-ssh-keys>`_
* `SSH key validation example <https://github.com/rushter/blog_code/tree/master/ssh>`_

If someone knows your public key,
he can check if it is among the ``~/.ssh/authorized_keys`` file.

List public ssh keys on github: ``curl https://github.com/lainiwa.keys``.
Same for gitlab (even private).

Example of how a service can know your github name by your ssh key:

.. code-block:: sh

    ssh whoami.filippo.io

Generate Keys and Install
=========================
* `SSH algos comparison <https://goteleport.com/blog/comparing-ssh-keys/>`_

Use either RSA-4096 for legacy and AWS
or Ed25519 (EdDSA) for speed.
Avoid ECDSA/DSA though.

.. code-block:: sh

    # Generate key
    ssh-keygen [-b 4096 -t rsa | -t ed25519] \
               -f ~/.ssh/id_rsa_aws_$(date +%Y-%m-%d) \
               -C "Login to production cluster at xyz corp"
    # Install key
    ssh-copy-id [-i ~/.ssh/your-key] user@host
    # or
    # cat ~/.ssh/id_rsa.pub | ssh user@host 'cat >> .ssh/authorized_keys && echo "Key copied"'
    # Test
    ssh -i ~/.ssh/your-key user@host


Multi Factor Authenticator
##########################
* `Trying to get SSH with public key (no password) + google authenticator working <https://serverfault.com/a/740881>`_
* `SSH с авторизацией через Google Authenticator <https://habr.com/ru/sandbox/33416/>`_
* `TOTP + password OR public key seems to be impossible to achieve <https://superuser.com/questions/1163942/#comment1678474_1163942>`_

Install google-authenticator on server:

.. code-block:: sh

    sudo apt install libpam-google-authenticator

Edit:

.. code-block:: sh
    :caption: /etc/pam.d/sshd

    auth sufficient pam_google_authenticator.so
    ...

.. code-block:: sh
    :caption: /etc/ssh/sshd_config

    ChallengeResponseAuthentication yes
    UsePAM yes
    AuthenticationMethods publickey,keyboard-interactive
    PasswordAuthentication no

Restart:

.. code-block:: sh

    sudo systemctl restart sshd.service


Configuration
#############

Editing:

#. ``sudoedit /etc/ssh/sshd_config``
#. Test with ``sudo sshd -t`` or extended test ``sudo sshd -T``
#. ``sudo systemctl restart sshd``

To disable root login::

    PermitRootLogin no

To disable login by password::

    PubkeyAuthentication yes
    ChallengeResponseAuthentication no
    PasswordAuthentication no

SFTP security
#############

Wrong
=====

Creating a user and attributing to placeholder shell
(``/usr/bin/nologin`` or ``/usr/bin/false``).

It can be bypassed by specifying execute command:

.. code-block:: sh

    ssh name@ip /usr/bin/id

Right
=====

.. code-block:: sh
    :caption: /etc/ssh/sshd_config

    Match User lain
        ChrootDirectory %h
        ForceCommand internal-sftp
        AllowTcpForwarding no
        PermitTunnel no
        X11Forwarding no
        PermitTTY no


Authentification Methods
########################

Examples:

.. code-block:: sh

    ssh 192.168.0.123 -o PreferredAuthentications=password
    ssh 192.168.0.123 -o PubkeyAuthentication=no


Attack
######
* `SSH Pentesting Guide <https://community.turgensec.com/ssh-hacking-guide/>`_

Misconfigurations:

* ``#PermitRootLogin yes``
    - Fix with ``PermitRootLogin no``
* SFTP ``/usr/bin/false``/``/usr/bin/nologin`` placeholder: can be bypassed by ``ssh user@host /bin/bash``
    - Restrict in SFTP block: `link <https://community.turgensec.com/ssh-hacking-guide/#SFTP_command_execution>`__
* Password login enabled
    - Can be bruteforced by: metasploit, hydra, medusa, ncrack


Linters
#######
* `mozilla/ssh_scan <https://github.com/mozilla/ssh_scan>`_

Examples:

.. code-block:: sh

    docker run -it mozilla/ssh_scan -t 127.0.0.1 |jq

SSH escape sequences
####################
* `Closing a stale SSH connection <https://davidisaksson.dev/posts/closing-stale-ssh-connections/>`_
    - `HN <https://readhacker.news/c/5Cbzc>`__

.. code-block:: text

    user@host:~$ ~?
    Supported escape sequences:
     ~.   - terminate session
     ~B   - send a BREAK to the remote system
     ~R   - request rekey
     ~#   - list forwarded connections
     ~?   - this message
     ~~   - send the escape character by typing it twice
    (Note that escapes are only recognized immediately after newline.)


ssh-agent
#########
* `Про SSH Agent <https://habr.com/ru/company/skillfactory/blog/503466/>`_
* https://rabexc.org/posts/using-ssh-agent
* https://rabexc.org/posts/pitfalls-of-ssh-agents
    - https://news.ycombinator.com/item?id=28576617
* https://smallstep.com/blog/ssh-agent-explained/
    - https://news.ycombinator.com/item?id=23241934
