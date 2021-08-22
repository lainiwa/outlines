
===
SSH
===

Todo:

* `Arch Wiki: OpenSSH <https://wiki.archlinux.org/index.php/OpenSSH#Two-factor_authentication_and_public_keys>`_
* `Arch Wiki: Google_Authenticator <https://wiki.archlinux.org/index.php/Google_Authenticator_(Русский)>`_

Run commands on every login: ``~/.ssh/rc``.


########
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


#########
Tunneling
#########
* A visual guide to SSH tunnels
    - `Article <https://robotmoon.com/ssh-tunnels/>`__
    - `HN <https://news.ycombinator.com/item?id=26053323>`__
* https://en.wikibooks.org/wiki/OpenSSH/Cookbook/Tunnels
* https://posts.specterops.io/offensive-security-guide-to-ssh-tunnels-and-proxies-b525cbd4d4c6

Local Port Forwarding
=====================
* Accessing a remote service (redis, memcached, etc.) listening on internal IPs
* Locally accessing resources available on a private network
* Transparently proxying a request to a remote service

.. image:: imgs/forward_local.png
  :width: 400
  :target: https://unix.stackexchange.com/questions/46235/how-does-reverse-ssh-tunneling-work/118650#answer-118650

Examples::

    # Forwards connections to 127.0.0.1:8080 on your local system
    # to port 80 on example.org through ssh-server.
    # 127.0.0.1:8080 --> ssh-server --> example.org:80
    ssh -L   127.0.0.1:8080:example.org:80 ssh-server

    # Forwards connections to port 8080 on all interfaces on your local system
    # to example.org:80 through a tunnel to ssh-server.
    # *:8080 --> ssh-server --> example.org:80
    ssh -L             8080:example.org:80 ssh-server
    ssh -L           *:8080:example.org:80 ssh-server

    # Forwards connections to 192.168.0.1:5432 on your local system
    # to 127.0.0.1:5432 on ssh-server.
    # 192.168.0.1:5432 --> ssh-server --> 127.0.0.1:5432
    ssh -L 192.168.0.1:5432:127.0.0.1:5432 ssh-server

Remote Port Forwarding
======================
* Making a local development server available over a public network
* Granting IP-restricted access to a remote resource on a private network

.. image:: imgs/forward_remote.png
  :width: 400
  :target: https://unix.stackexchange.com/questions/46235/how-does-reverse-ssh-tunneling-work/118650#answer-118650

Examples::

    # Forwards traffic to all interfaces on port 8080 on ssh-server
    # to localhost port 80 on your local computer.
    # anyone --> ssh-server:8080 --> localhost:80
    ssh -R         8080:localhost:80 ssh-server

    # Forwards traffic to ssh-server:8080
    # to localhost:80 on your local system
    # while only allowing access from IP address 1.2.3.4.
    # 1.2.3.4 --> ssh-server:8080 --> localhost:80
    ssh -R 1.2.3.4:8080:localhost:80 ssh-server

    # Forwards traffic to all interfaces on ssh-server:8080
    # to localhost:80 on your local system.
    # From your local system, traffic is then forwarded to example.org:80.
    # anyone --> ssh-server:8080 --> example.org:80
    ssh -R         8080:example.org:80 ssh-server

Dynamic Port Forwarding
=======================
Dynamic port forwarding opens a SOCKS proxy on the SSH client that lets you forward TCP traffic through the SSH server to a remote host.

Examples::

    # Opens a SOCKS proxy on port 3000 of all interfaces on your local system.
    #         *:3000 --> ssh-server --> *:*
    ssh -D 3000 ssh-server

    # Opens a SOCKS proxy on 127.0.0.1:3000 on your local system.
    # 127.0.0.1:3000 --> ssh-server --> *:*
    ssh -D 127.0.0.1:3000 ssh-server

    # curl -x socks5://127.0.0.1:12345 https://curlmyip.net

Jump hosts and proxy commands
=============================
Transparently connecting to a remote host through intermediate hosts.

Examples::

    # Establishes an SSH connection with jump-host
    # and forwards TCP traffic to remote-host.
    # you --> user1@jump-host --> user2@remote-host
    ssh -J user1@jump-host user2@remote-host
    ssh -o "ProxyJump user1@jump-host" user2@remote-host

    # you --> jump-host1 --> jump-host2 --> ssh-server
    ssh -J jump-host1,jump-host2 ssh-server

    ssh -o ProxyCommand="nc -X 5 -x localhost:3000 %h %p" user@remote-host


############
Private Keys
############

Private Keys Surveillance
=========================
* `ssh whoami.filippo.io <https://blog.filippo.io/ssh-whoami-filippo-io>`_
* `Public SSH keys can leak your private infrastructure <https://rushter.com/blog/public-ssh-keys>`_
* `SSH key validation example <https://github.com/rushter/blog_code/tree/master/ssh>`_

If someone knows your public key,
he can chack if it is among the ``~/.ssh/authorized_keys`` file.

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


##########################
Multi Factor Authenticator
##########################
* `Trying to get SSH with public key (no password) + google authenticator working <https://serverfault.com/a/740881>`_
* `SSH с авторизацией через Google Authenticator <https://habr.com/ru/sandbox/33416/>`_
* `TOTP + password OR public key seems to be impossible to achieve <https://superuser.com/questions/1163942/#comment1678474_1163942>`

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


#############
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

#############
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


########################
Authentification Methods
########################

Examples:

.. code-block:: sh

    ssh 192.168.0.123 -o PreferredAuthentications=password
    ssh 192.168.0.123 -o PubkeyAuthentication=no


######
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

#####################
Signing with SSH Keys
#####################
* `SSH is the new GPG <https://blog.sigstore.dev/ssh-is-the-new-gpg-74b3c6cc51c0>`_

Sign:

.. code-block:: sh

    ssh-keygen -Y sign -n file -f ~/.ssh/id_rsa.pub <FILE-TO-SIGN>


Create allowed signers file:

.. code-block:: sh

    GH_NAME=lainiwa
    curl -s https://github.com/${GH_NAME}.keys |
        sed "s/^/${GH_NAME} /" |
        tee -a allowed_signers.github

Verify:

.. code-block:: sh

    cat git_tutorial.zip |
        ssh-keygen -Y verify \
                   -n file \
                   -f allowed_signers.github \
                   -I ${GH_NAME} \
                   -s git_tutorial.zip.sig


#######
Linters
#######
* `mozilla/ssh_scan <https://github.com/mozilla/ssh_scan>`_

Examples:

.. code-block:: sh

    docker run -it mozilla/ssh_scan -t 127.0.0.1 |jq
