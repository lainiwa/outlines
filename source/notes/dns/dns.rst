
===
DNS
===
* `NsLookup Learning Center <https://www.nslookup.io/learning/>`_
* `Troubleshooting DNS with dig <https://youtu.be/cFmy2wNw9RQ>`_
* `DNS Root Servers <https://securitytrails.com/blog/dns-root-servers>`_
* `The Sisyphean Task Of DNS Client Config on Linux <https://tailscale.com/blog/sisyphean-dns-client-linux/>`_
* `Anatomy of a Linux DNS Lookup – Part I <https://zwischenzugs.com/2018/06/08/anatomy-of-a-linux-dns-lookup-part-i/>`_
    - https://zwischenzugs.com/2018/06/08/anatomy-of-a-linux-dns-lookup-part-i/
    - https://zwischenzugs.com/2018/06/18/anatomy-of-a-linux-dns-lookup-part-ii/
    - https://zwischenzugs.com/2018/07/06/anatomy-of-a-linux-dns-lookup-part-iii/
    - https://zwischenzugs.com/2018/08/06/anatomy-of-a-linux-dns-lookup-part-iv/
    - https://zwischenzugs.com/2018/09/13/anatomy-of-a-linux-dns-lookup-part-v-two-debug-nightmares/
* https://sookocheff.com/post/networking/how-does-dns-work/
* https://doc.powerdns.com/authoritative/appendices/types.html

Online DNS Check Tools
######################
* `Zonemaster <https://zonemaster.net/en/run-test>`_
* `Cloudflare Radar <https://radar.cloudflare.com/scan>`_
* `DNS Spy <https://dnsspy.io/>`_


Vocabulary
##########
* Records
    - **A**: Points to IP address
    - **AAAA**: Same as A, but for IPv6
    - **CNAME**: Canonical Name Record. Points to alias (domain/subdomain name)
    - **MX**: Mail eXchange records; tells email delivery agents where to deliver mail
    - **TXT**: flexible Text records, for storing strings for a variety of uses
    - **SOA**: singular Start of Authority record kept at the top level of the domain. Contains specific required information about the domain, for example its primary name server
    - **NS**: The name servers associated with the domain
* ``example.com`` = apex/root/naked domain name


Query
#####
::

    Browser --asks--> ISP DNS
    Browser --asks--> ISP DNS --asks--> root server --returns list of TLD (e.g. .com) servers-->..
                ..--> ISP DNS --asks--> TLD server --returns the authoritative name server-->

.. image:: imgs/recursive_iterative_referral_authoritative.png
  :width: 100%
  :target: https://youtu.be/cFmy2wNw9RQ

Root servers: ``{a..m}.root-servers.net.``


NSSwitch
########

Many programs use libc call `getaddrinfo <http://man7.org/linux/man-pages/man3/getaddrinfo.3.html>`_.

Example: ``ping`` uses nsswitch, while ``host`` doesn't (but both read ``resolv.conf``):

.. code-block:: sh

    strace -f -e trace=open,openat \
        ping -c1 google.com 2>&1 >/dev/null |grep -z -e resolv.conf -e nsswitch

    strace -f -e trace=open,openat \
        host google.com 2>&1 >/dev/null |grep -z -e resolv.conf -e nsswitch

.. image:: imgs/nsswitch.png
  :width: 50%
  :target: https://zwischenzugs.com/2018/06/08/anatomy-of-a-linux-dns-lookup-part-i/


Possible Issues
###############
* `Why a domain’s root can’t be a CNAME — and other tidbits about the DNS <https://www.freecodecamp.org/news/why-cant-a-domain-s-root-be-a-cname-8cbab38e5f5c/>`_

WWW Problem
===========
A record::

    A: www.example.com --> 123.123.123.123
    A:     example.com --> 123.123.123.123

CNAME record::

    CNAME: www.example.com --> example.com
    A:         example.com --> 123.123.123.123


Scripting
=========
* use: ``getent hosts example.com`` (is `IPv6-first <https://unix.stackexchange.com/q/50365>`_ though)
* don't: ``host example.com`` (doesn't respect nsswitch; not reliable output format)


Using ``dig``
#############
* `Useful Linux Dig Examples for the Network Admin <https://adamtheautomator.com/linux-dig/>`_
* `JEvans: How to use dig <https://jvns.ca/blog/2021/12/04/how-to-use-dig/>`_
    - `HN <https://news.ycombinator.com/item?id=29441333>`__

DNS Query Options
=================

1. **name**: e.g ``jvns.ca``. Default is ``.``
2. **query type**: e.g. ``A`` or ``CNAME``. Default is ``A``
3. **DNS server**: e.g. ``@8.8.8.8``. Default is whatever is in ``/etc/resolv.conf``

Examples:

* ``dig @8.8.8.8 jvns.ca``
* ``dig ns jvns.ca``

Reverse DNS Lookup
==================

.. code-block:: sh

    $ dig -x 172.217.13.174
    174.13.217.172.in-addr.arpa. 72888 IN   PTR yul03s04-in-f14.1e100.net.

    # `-x 172.217.13.174` is a shortcut for
    $ dig ptr 174.13.217.172.in-addr.arpa.

Formatting response
===================

.. code-block:: sh

    $ dig +noall +answer ns google.com
    google.com.     158564  IN  NS  ns4.google.com.
    ...

    $ dig +short ns google.com
    ns2.google.com.
    ...

    $ # Return behavior by default (if non-empty ~/.digrc)
    $ dig +all jvns.ca

digrc
=====

.. code-block:: sh
    :caption: ~/.digrc

    +noall +answer


.. Root Servers
.. ############


..     dig example.com +trace


