
=====
Socat
=====

Snippets
========
* `Getting started with socat, a multipurpose relay tool for Linux <https://www.redhat.com/sysadmin/getting-started-socat>`_

HTTP client
-----------

.. code-block:: sh

    {
    cat <<EOF ; sleep 1;
    GET / HTTP/1.0
    Host: wttr.in
    User-Agent: curl

    EOF
    } | socat - TCP4:wttr.in:80


TCP port forwarding
-------------------
* `curl another host <https://daniel.haxx.se/blog/2018/04/05/curl-another-host/>`_
* `Can anyone explain docker.sock <https://stackoverflow.com/questions/35110146/can-anyone-explain-docker-sock>`_
* `Docker Tips : about /var/run/docker.sock <https://betterprogramming.pub/about-var-run-docker-sock-3bfd276e12fd>`_

.. code-block:: sh

    # Simple TCP forward (SSH)
    socat TCP4-LISTEN:9999 TCP4:localhost:22
    ssh lain@localhost -p 9999

    # HTTP forward (example with curl --header)
    socat TCP4-LISTEN:9999,fork,reuseaddr TCP4:wttr.in:80
    curl --header "Host: wttr.in" localhost:9999

    # HTTPS forward (example with curl --connect-to)
    socat TCP4-LISTEN:9999,fork,reuseaddr TCP4:wttr.in:443
    curl --connect-to wttr.in:443:localhost:9999 https://wttr.in

    # Redirect incoming data to file
    socat -u TCP4-LISTEN:3334,reuseaddr,fork OPEN:/tmp/test.log,creat,append
    echo $(whoami) | socat - TCP4:localhost:3334
    tail -f /tmp/test.log

    socat - UDP4-DATAGRAM:225.255.0.1:6666,bind=:6666,ip-add-membership=225.255.0.1:enp0s3

    # Forward docker.sock
    # by default docker.sock can be communicated with as follows:
    # curl -v --unix-socket /var/run/docker.sock http://localhost/images/json | jq
    #
    # Get all images info
    socat TCP-LISTEN:3307,reuseaddr,fork UNIX-CONNECT:/var/run/docker.sock
    curl http://localhost:3307/images/json | jq
    # Create nginx container
    docker pull nginx
    curl -XPOST --unix-socket /var/run/docker.sock -d '{"Image":"nginx"}' -H 'Content-Type: application/json' http://localhost:3307/containers/create
    docker ps -a
    # docker rm ...