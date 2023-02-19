


===================
Linux C Programming
===================

Prepare environment:

.. code-block:: sh

    sudo apt install build-essential
    gcc --version
    make --version

Basic
=====

Create a hello world and run it with: ``gcc main.c -o hello && ./hello && rm ./hello``

.. literalinclude:: main.c
  :caption: main.c
  :language: C
  :linenos:

Shared library
==============

Create the files:

.. literalinclude:: libdemo/hello.h
  :caption: libdemo/hello.h
  :language: C
  :linenos:

.. literalinclude:: libdemo/hello.c
  :caption: libdemo/hello.c
  :language: C
  :linenos:

.. literalinclude:: libdemo/main.c
  :caption: libdemo/main.c
  :language: C
  :linenos:

Now compile step by step:

.. code-block:: sh

    gcc -o hello.o -c hello.c        # Compile object files
    gcc -o main.o  -c main.c
    gcc -o hello.exe hello.o main.o  # Produce the executable

Manually compile shared library:

.. code-block:: sh

    gcc -o libHello.so -shared hello.c

Run ``nm libHello.so`` and see the name in the shared library::

    ...
    0000000000001119 T hello_message
    ...

Manually compile shared library the main executable and run it:

.. code-block:: sh

    gcc main.c -L. -lHello -o hello
    ./hello  # ERROR: cannot open shared object file
    LD_LIBRARY_PATH=. ./hello

C++ name mangling
-----------------

Copy a ``.c`` to ``.cpp`` file:

.. code-block:: sh

    cp hello.c hello.cpp

Now create a shared library from it, just like with ``.c`` version:

.. code-block:: sh

    gcc -o libHello.so -shared hello.cpp

The ``hello_message`` would me mangled (``nm libHello.so |grep hello_message``)::

    0000000000001119 T _Z13hello_messagePKc

Cannot run ``./hello`` now::

    ./hello: symbol lookup error: ./hello: undefined symbol: hello_message

Decode it back:

.. code-block:: sh

    c++filt _Z13hello_messagePKc  # --> hello_message(char const*)
    # or just
    nm -C libHello.so

Dependency graph
----------------

.. graphviz::
    :name: sphinx.ext.graphviz
    :caption: Sphinx and GraphViz Data Flow
    :alt: How Sphinx and GraphViz Render the Final Document
    :align: center

    digraph "Makefile" {
        // size="6,4";
        rankdir="LR";
        graph [fontname="Verdana", fontsize="12"];
        node [fontname="Verdana", fontsize="12"];
        edge [fontname="Sans", fontsize="9"];

        main_c      [label="main.c",      shape="folder", fillcolor=yellow, style=filled];
        hello_h     [label="hello.h",     shape="folder", fillcolor=grey,   style=filled];
        hello_c     [label="hello.c",     shape="folder", fillcolor=yellow, style=filled];
        libHello_so [label="libHello.so", shape="folder", fillcolor=white,  style=filled];
        hello       [label="hello",       shape="folder", fillcolor=orange, style=filled];

        libHello_so -> hello_h [style=dashed];
        libHello_so -> hello_c [style=dashed];

    }

::

    hello       ---> main.c  ---\
                                 ---> hello.h
    libHello.so ---> hello.c ---/

Makefile
--------

.. literalinclude:: libdemo/Makefile
  :caption: libdemo/Makefile
  :language: make
  :linenos:

Run and then we can check shared dependencies:

.. code-block:: sh

    ldd hello        # --> ./libHello.so is in dependency list
    ldd libHello.so
