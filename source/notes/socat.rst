
=====
Socat
=====
* https://gist.github.com/mario21ic/c09f0a648130ad6a91abdde41cb011c8
* http://www.dest-unreach.org/socat/doc/socat-openssltunnel.html
* http://www.dest-unreach.org/socat/doc/socat-tun.html

Snippets
########
* `Getting started with socat, a multipurpose relay tool for Linux <https://www.redhat.com/sysadmin/getting-started-socat>`_

HTTP client
===========

.. code-block:: sh

    {
    cat <<EOF ; sleep 1;
    GET / HTTP/1.0
    Host: wttr.in
    User-Agent: curl

    EOF
    } | socat - TCP4:wttr.in:80


Port forwarding
===============

Simple TCP port forwarding
--------------------------

.. code-block:: sh

    # Simple TCP forward (SSH)
    socat TCP4-LISTEN:9999 TCP4:localhost:22
    ssh lain@localhost -p 9999

HTTP port forwarding
--------------------
* `curl another host <https://daniel.haxx.se/blog/2018/04/05/curl-another-host/>`_

.. code-block:: sh

    # HTTP forward (example with curl --header)
    socat TCP4-LISTEN:9999,fork,reuseaddr TCP4:wttr.in:80
    curl --header "Host: wttr.in" localhost:9999

    # HTTPS forward (example with curl --connect-to)
    socat TCP4-LISTEN:9999,fork,reuseaddr TCP4:wttr.in:443
    curl --connect-to wttr.in:443:localhost:9999 https://wttr.in

Socket forwarding
-----------------
* `Can anyone explain docker.sock <https://stackoverflow.com/questions/35110146/can-anyone-explain-docker-sock>`_
* `Docker Tips: about /var/run/docker.sock <https://betterprogramming.pub/about-var-run-docker-sock-3bfd276e12fd>`_
* `SO: Is it possible to access a Unix socket over the network? <https://unix.stackexchange.com/questions/683688/is-it-possible-to-access-a-unix-socket-over-the-network>`_

.. code-block:: sh

    # Forward docker.sock
    # by default docker.sock can be communicated with as follows:
    # curl --unix-socket /var/run/docker.sock http://localhost/images/json | jq
    #
    # Get all images info
    socat TCP-LISTEN:3307,reuseaddr,fork UNIX-CONNECT:/var/run/docker.sock
    curl http://localhost:3307/images/json | jq
    # Create nginx container
    docker pull nginx
    curl -XPOST --unix-socket /var/run/docker.sock -d '{"Image":"nginx"}' -H 'Content-Type: application/json' http://localhost:3307/containers/create
    docker ps -a
    # docker rm ...

    # Mounting a remote unix socket
    # on the server:
    socat TCP-LISTEN:6644,reuseaddr,fork UNIX-CONNECT:/path/to/socket/file
    # on the client:
    socat UNIX-LISTEN:/tmp/remote_socket,fork,reuseaddr,unlink-early,user=file_owner,group=file_group,mode=770 TCP:1.2.3.4:6644

MITM
----
* https://stackoverflow.com/questions/46050238/socat-how-to-listen-on-non-ssl-tcp-and-forward-to-ssl-tcp-endpoint
* https://funoverip.net/2011/01/reverse-ssl-backdoor-with-socat-and-metasploit/

.. code-block:: sh

    curl -s https://storage.yandexcloud.net/cloud-certs/CA.pem > ca.pem
    socat \
        TCP-LISTEN:8443,fork,reuseaddr \
        OPENSSL:rc1b-inserttheaddress.mdb.yandexcloud.net:8443,cafile=ca.pem,verify=1
    # Check it's working:
    echo 'SHOW DATABASES' |
        curl 'http://localhost:8443/?user=admin&password=NimdaLol' --data-binary @-

Encrypted TLS-authenticated bind shell
--------------------------------------
* `ncat doesn't allow client authentication <https://github.com/nmap/nmap/issues/1898>`_
* https://book.hacktricks.xyz/generic-methodologies-and-resources/tunneling-and-port-forwarding#bind-shell

.. code-block:: sh

    mkdir -p certs

    # Generate CA
    openssl req -new -x509 -days 365 -nodes -keyout certs/ca.key -out certs/ca.crt \
        -subj "/CN=My CA"

    # Generate Server Key and Certificate
    openssl req -newkey rsa:4096 -nodes -keyout certs/server.key -out certs/server.csr \
        -subj "/CN=lainiwa.duckdns.org"
    openssl x509 -req -in certs/server.csr -CA certs/ca.crt -CAkey certs/ca.key -CAcreateserial \
        -out certs/server.crt -days 365

    # Combine server certificate and key for socat
    cat certs/server.crt certs/server.key > certs/server.pem

    # Generate Client Key and Certificate
    openssl req -newkey rsa:4096 -nodes -keyout certs/client.key -out certs/client.csr \
        -subj "/CN=Client"
    openssl x509 -req -in certs/client.csr -CA certs/ca.crt -CAkey certs/ca.key -CAcreateserial \
        -out certs/client.crt -days 365

    # Combine client certificate and key for socat
    cat certs/client.crt certs/client.key > certs/client.pem

    # Start socat with SSL, requiring and verifying client certificates, and execute a shell upon connection
    # socat OPENSSL-LISTEN:8888,cert=certs/server.pem,cafile=certs/ca.crt,verify=1,reuseaddr,fork EXEC:"/bin/bash",pty,stderr,setsid,sigint,sane

    # Client command to connect to the bind shell (commented out)
    # Replace 'lainiwa.duckdns.org' with the server's address if not running locally.
    # socat - OPENSSL:lainiwa.duckdns.org:8888,cert=certs/client.pem,cafile=certs/ca.crt,verify=1

Other examples
--------------

.. code-block:: sh

    # Redirect incoming data to file
    socat -u TCP4-LISTEN:3334,reuseaddr,fork OPEN:/tmp/test.log,creat,append
    echo $(whoami) | socat - TCP4:localhost:3334
    tail -f /tmp/test.log

    socat - UDP4-DATAGRAM:225.255.0.1:6666,bind=:6666,ip-add-membership=225.255.0.1:enp0s3
