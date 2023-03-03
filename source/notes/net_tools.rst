
===================
Network debug tools
===================

Sources:

* https://habr.com/en/post/320278/


Ping & Traceroute
#################
#. ``ping <host>`` - check node is available by sending ICMP packets
    * ``ping -[a]udible`` doesn't work
#. ``traceroute <host>`` - ping every node on the way to ``<host>``
#. ``mtr <host>`` - sort of a union of ping and traceroute
    * has gtk gui

netstat
#######
Print:

* network connections
* routing tables
* interface statistics
* masquerade connections
* multicast memberships

Usage::

    netstat
    netstat [-t|--tcp] [-u|--udp]
            [-l|--listening]  <-- listening addresses
            [-p|--program]    <-- print PID/program using the address
            [-r|--route]      <-- routing table

ss
###
Another utility to investigate sockets.

Sources:

* `Что обозначает вывод «ss -s» <https://habr.com/ru/post/503648>`_
* `ss command: Display Linux TCP / UDP Network/Socket Information <https://www.cyberciti.biz/tips/linux-investigate-sockets-network-connections.html>`_

Usage::

    ss
    ss [-t|--tcp] [-u|--udp]
       [-4|--ipv4|-f inet] [-6|--ipv6|-f inet6] [-x|--unix|-f unix] ...
       [-a|--all]
       [-r|--resolve]
       [-l|--listening]  <-- listening addresses
       [-p|--processes]  <-- show process using socket
       [-n|--numeric]    <-- don't try to be "human-readable"

Examples:

.. code-block:: bash

    # Show which services are listening
    sudo ss -lptn
    # Display all established HTTPS connections
    sudo ss -o state established '( dport = :https or sport = :https )'

nslookup
########
Query internet name servers.

Usage::

    nslookup 1.1.1.1          <-- reverse DNS lookup
    nslookup one.one.one.one  <-- print IP (A record) for domain

    nslookup -type=ns  microsoft.com  <-- name servers that are authoritative for domain
    nslookup -type=mx  microsoft.com  <-- map of mail exchange servers
    nslookup -type=soa microsoft.com  <-- SOA ("Start Of Authority") record (technical info)
    nslookup -type=any microsoft.com  <-- all types (error: NOT IMPlemented in bind<9.3)

vnstat
######
Console-based network traffic monitor

vnstati: png image output support for vnStat

Install::

    sudo apt install vnstat vnstati

Usage::

    sudo vnstat
    sudo vnstat [-i|--iface] enp0s3

    sudo vnstat [-l|--live] [0|1]  <-- live mode=0 for packets/second
                                            mode=1 for transfer counters

    vnstati [-s|--summary] \
            [-i|--iface] enp0s3 \
            [-o|--output] summary.png            <-- dump stats summary to image

    sxiv =(vnstati -s -i enp0s3 -o -)  <-- view image (`=(...)` is zsh-ism)

    vnstati [-h|--hours] -i enp0s3 -o summary.png  <-- hourly statistics
    vnstati -s -i docker0+enp0s3 -o summary.png    <-- cumulative output

iptraf
######
Interactive colorful IP LAN monitor

ntop
####
Display top network users (Web GUI)

nmap
####

tcpdump
#######
