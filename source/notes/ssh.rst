
===
SSH
===

Todo:

* `Arch Wiki: OpenSSH <https://wiki.archlinux.org/index.php/OpenSSH#Two-factor_authentication_and_public_keys>`_
* `Arch Wiki: Google_Authenticator <https://wiki.archlinux.org/index.php/Google_Authenticator_(Русский)>`_

Run commands on every login: ``~/.ssh/rc``.


############
Private Keys
############

Private Keys Surveillance
=========================

Sources:

* `ssh whoami.filippo.io <https://blog.filippo.io/ssh-whoami-filippo-io>`
* `Public SSH keys can leak your private infrastructure <https://rushter.com/blog/public-ssh-keys>`
* `SSH key validation example <https://github.com/rushter/blog_code/tree/master/ssh>`

If someone knows your public key,
he can chack if it is among the ``~/.ssh/authorized_keys`` file.

List public ssh keys on github: ``curl https://github.com/lainiwa.keys``.
Same for gitlab (even private).

Example of how a service can know your github name by your ssh key:

.. code-block:: sh

    ssh whoami.filippo.io

Generate Keys and Install
=========================

Sources:

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

Sources:

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




