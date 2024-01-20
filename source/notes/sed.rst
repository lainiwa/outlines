
===
Sed
===

In-place editing and backups:

.. code-block:: sh

    # In-place
    sed -i 's/a/b/' config.txt

    # Backup
    sed -i.bak        's/a/b/' c.txt
    sed -i.bak        's/a/b/' c1.txt c2.txt  # Backup two files
    sed -i'bkp.*'     's/a/b/' c.txt          # Use prefix
    sed -i'backups/*' 's/a/b/' c1.txt c2.txt  # Move backups to existing directory


Search and replace with ``s/address/replacment/flags``:

.. code-block:: sh

    printf 'one two three' |sed 's/t/T/'   # one Two three
    printf 'one two three' |sed 's/t/T/g'  # one Two Three


Map pattern space from source to destination with ``y/src/dst``:

.. code-block:: sh

     printf 'one two three four five' |sed 'y/aeiouy/AEIOUY/'  # OnE twO thrEE fOUr fIvE

Conditional execution with ``/address/flags`` or ``/address/flags!`` for inverted:

.. code-block:: sh

    $ printf '1,2,3,4\na,b,c,d\n' | sed '/2/ s/,/-/g'
    1-2-3-4
    a,b,c,d

    $ printf '1,2,3,4\na,b,c,d\n' | sed '/2/! s/,/-/g'
    1,2,3,4
    a-b-c-d

Drop lines:

.. code-block:: sh

    $ # same as: grep -v 'at'
    $ printf 'sea\neat\ndrop\n' | sed '/at/d'
    sea
    drop

    $ # same as: grep 'at'
    $ printf 'sea\neat\ndrop\n' | sed '/at/!d'
    eat

    $ # same as: cat file
    $ sed '!d' file


.. .....


Quit:

.. code-block:: sh

    $ # Exit after matching line
    $ sed '/match/q' file
    $ # Exit before matching line
    $ sed '/match/Q' file

    $ # To get lines after match, use tac
    $ tac file | sed '/match/q' | tac

    $ # Provide exit status
    $ sed '/match/q255'

Notice: for multiple files, sed will quit after the match, even if there files left to be processed. Otherwise, `use -s flag <https://unix.stackexchange.com/a/309516>`_
