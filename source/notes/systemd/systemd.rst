
=======
Systemd
=======

Todo/To read:

* https://habr.com/ru/company/redhatrussia/blog/468931/
* https://telegra.ph/Haker---Poleznyj-demon-Kak-perestat-boyatsya-systemd-i-sdelat-svoj-servis-dlya-Linux-12-10
* https://wiki.archlinux.org/index.php/Systemd#See_also
* https://wiki.archlinux.org/index.php/Systemd#Mounting
* https://wiki.archlinux.org/index.php/Systemd#Enable_installed_units_by_default
* https://www.redhat.com/files/summit/session-assets/2019/T4D2A2.pdf
* https://www.designed-cybersecurity.com/tutorials/harden-gnupg-config/
* https://nardifairuz.wordpress.com/2019/04/30/automate-backups-with-restic-and-systemd/
* https://habr.com/ru/post/270165/
* https://opensource.com/article/20/4/systemd
* Автомонтирование разделов GPT
* network awareness - run these services when connected to this type of networks
* logind - user session manger
* https://wiki.archlinux.org/index.php/Systemd_(Русский)/User_(Русский)
* https://habr.com/ru/post/270165/
* http://manpages.ubuntu.com/manpages/bionic/man5/systemd.preset.5.html#examples
* https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/html/system_administrators_guide/ch-keyboard_configuration
* http://0pointer.net/blog/walkthrough-for-portable-services.html
* https://opensource.com/article/20/7/systemd-timers
* https://medium.com/@nickodell/sandboxing-nginx-with-systemd-80441923c555
* https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/8/html/configuring_basic_system_settings/configuring-a-remote-logging-solution_configuring-basic-system-settings
* apt search systemd-coredump
* Logs
    - https://habr.com/ru/company/selectel/blog/264731/
    - https://www.dmosk.ru/miniinstruktions.php?mini=journald-remote
    - https://www.digitalocean.com/community/tutorials/how-to-centralize-logs-with-journald-on-ubuntu-20-04
    - https://max-ko.ru/33-logi-v-linux-1.html
* Critics
    - https://blog.erratasec.com/2018/10/systemd-is-bad-parsing-and-should-feel.html
* Resource accounting - nspawn
    - https://selectel.ru/blog/mexanizmy-kontejnerizacii-namespaces/
    - https://0xax.gitbooks.io/linux-insides/content/Cgroups/linux-cgroups-1.html
    - https://wiki.archlinux.org/index.php/Systemd-networkd_(Русский)
    - https://wiki.archlinux.org/index.php/Access_Control_Lists#Enable_ACL
    - https://wiki.archlinux.org/index.php/Cgroups
    - https://nspawn.org/faq/
    - https://wiki.debian.org/nspawn
    - https://patrickskiba.com/sysytemd-nspawn/2019/02/08/introduction-to-systemd-nspawn.html
    - https://lwn.net/Articles/572957/
    - https://medium.com/@huljar/setting-up-containers-with-systemd-nspawn-b719cff0fb8d
    - https://tina.pm/blog/posts/Creating_containers_with_systemd/
    - http://ludiclinux.com/Nspawn-Steam-Container/
    - https://blog.selectel.com/systemd-containers-introduction-systemd-nspawn/
    - https://kitsunemimi.pw/notes/posts/opening-a-shell-inside-non-systemd-nspawn-containers.html
    - https://wiki.arcoslab.org/doku.php?id=tutorials:systemd-nspawn
    - https://ramsdenj.com/2016/09/23/containerizing-graphical-applications-on-linux-with-systemd-nspawn.html
    - http://blog.oddbit.com/post/2016-02-07-systemd-nspawn-for-fun-and-well-mostly-f/
* Systemd logs
    - https://max-ko.ru/33-logi-v-linux-1.html
    - http://www.k-max.name/linux/rsyslog-na-debian-nastrojka-servera/
* Systemd-homed
    - https://news.ycombinator.com/item?id=22285538
    - https://hackaday.com/2019/10/16/pack-your-bags-systemd-is-taking-you-to-a-new-home/
    - https://systemd.io/HOME_DIRECTORY/


Shutdown and Reboot
===================

With systemd:

.. code-block:: sh

    sudo systemctl poweroff
    sudo systemctl reboot

Without systemd:

.. code-block:: sh

    poweroff
    reboot
    shutdown -r 2  # schedule reboot at 2 minutes


Daemon Management
=================

SysV init style scripts:

.. code-block:: sh

    ls /etc/init.d/

.. code-block:: sh

    sudo systemctl [enable|disable] name.service
    sudo systemctl [start|stop|restart|reload|reload-or-restart] name.service
    systemctl status [-l|--full] [name.service|pid]
    systemctl list-unit-files --type service
    systemctl [is-active|is-enabled|is-failed] name.service
    # Masked service is unable to start - even as a dependency (somewhat dangerous)
    sudo systemctl [mask|unmask] name.service
    # Show documentation
    systemctl help name.service
    # Enable and start immediately
    sudo systemctl enable --now unit

Reset failed statuses:

.. code-block:: sh

    sudo systemctl reset-failed



.. include:: .time_loc.rst
.. include:: .targets.rst
.. include:: .units.rst
.. include:: .static_files.rst
.. include:: .tmpfiles.rst
.. include:: .timers.rst
.. include:: .network.rst
.. include:: .journal.rst
.. include:: .nspawn.rst
.. include:: .caps.rst



Perfomance
==========

Show how much time each service takes to start:

.. code-block:: sh

    systemd-analyze blame

Plot for more information:

.. code-block:: sh

    systemd-analyze plot > systemd-perf.svg
    firefox systemd-perf.svg


Other
=====

IPMI was failing for whatever reason, so I disabled it:

.. code-block:: sh

    sudo systemctl disable openipmi.service
