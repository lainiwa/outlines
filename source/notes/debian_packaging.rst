
================
Debian Packaging
================

Repositories
############
* `How to Switch From Debian Stable to Debian Testing <https://www.makeuseof.com/switch-from-debian-stable-to-testing/>`_
* `How to safely upgrade from Debian Stable to Debian sid/unstable? <https://www.reddit.com/r/debian/comments/d2si9u/how_to_safely_upgrade_from_debian_stable_to/>`_
* `How to Convert Debian Stable Version to Testing <https://www.debugpoint.com/debian-stable-to-testing/>`_
* https://www.reddit.com/r/ansible/comments/15j5w74/how_to_make_sure_contrib_repo_is_enabled_on_debian/

.. code-block:: text
   :caption: /etc/apt/sources.list

   deb     http://deb.debian.org/debian/              sid               main contrib non-free non-free-firmware
   deb-src http://deb.debian.org/debian/              sid               main contrib non-free non-free-firmware
   deb     http://security.debian.org/debian-security bookworm-security main contrib non-free non-free-firmware
   deb-src http://security.debian.org/debian-security bookworm-security main contrib non-free non-free-firmware
   deb     http://deb.debian.org/debian/              bookworm-updates  main contrib non-free non-free-firmware
   deb-src http://deb.debian.org/debian/              bookworm-updates  main contrib non-free non-free-firmware

.. code-block:: sh

   sudo apt update && sudo apt full-upgrade

Keys
====
* https://stackoverflow.com/questions/68104343/ansible-tasks-for-adding-the-google-cloud-sdk-apt-repository-signing-key
* https://stackoverflow.com/questions/68992799/warning-apt-key-is-deprecated-manage-keyring-files-in-trusted-gpg-d-instead

Notes:

* ``/etc/apt/trusted.gpg.d`` is insecure because it adds the key for all repositories
* That's why ``apt-key`` had to be deprecated
* Use ``/usr/share/keyrings`` (or ``/etc/apt/keyrings``) for 3rd party gpg keys
* Put ``signed-by=/usr/share/keyrings/key.(gpg|asc)`` in repo definition
* Prefer binary signatures (``.gpg`` files),
  but ascii armored keys seems to work (as long as the extension is ``.asc``)
* No need to install ``gnupg`` (as long as you don't use ``apt-key`` commands)

Using the newer DEB822 format
=============================

Versioning
==========
* https://readme.phys.ethz.ch/documentation/debian_version_numbers/

Python
======
* https://medium.com/@pyc0d3r/packaging-python-project-to-debian-deb-part-1-f01f510d7d10
* https://medium.com/@pyc0d3r/packaging-python-project-to-debian-deb-part-2-ea6d98e2d716
