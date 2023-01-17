
===
ZSH
===

###########
Completions
###########
* https://blog.mads-hartmann.com/2017/08/06/writing-zsh-completion-scripts.html
* https://zsh.sourceforge.io/Refcard/
    - rendered: http://www.bash2zsh.com/zsh_refcard/refcard.pdf

###############
Alternate Forms
###############
* https://zsh.sourceforge.io/Doc/Release/Shell-Grammar.html#Alternate-Forms-For-Complex-Commands
* https://unix.stackexchange.com/questions/468582/examples-of-zsh-alternate-forms-of-complex-commands


#########
Expansion
#########
* ``man 1 zshexpn``

---------
Modifiers
---------
* `Zshell path modifiers <https://www.tlbx.app/blog/zshell-path-modifiers>`_
* `Modifiers <http://zsh.sourceforge.net/Doc/Release/Expansion.html#Modifiers>`_
* ``LESS="$LESS+/^ *Modifiers$" man 1 zshexpn``

.. code-block:: bash

    ${VAR:modifier}
    ${VAR:modifier1:modifier2}

    VAR=/path/to/image.png
    echo ${VAR:h}  # --> /path/to
    echo ${VAR:t}  # --> image.png
    echo ${VAR:r}  # --> /path/to/image
    echo ${VAR:e}  # --> png

    VAR=image.png
    echo ${VAR:a}  # --> /home/lain/image.png

    CMD=nvim
    echo ${CMD:c}  # --> /usr/local/bin/nvim

    STR="file1.txt file2.txt"
    echo ${STR:s/txt/md}    # --> file1.md file2.txt
    echo ${STR:gs/txt/md}   # --> file1.md file2.md
    MYFILE=img/large/01.png
    echo ${MYFILE:gs_/_._}  # --> img.large.01.png

    print -l **/*.jpg(:t:r)

    VAR="Hello zshell 'world'"
    echo ${VAR:q}  # --> Hello\ zshell\ \'world\'
    VAR="Hello\ zshell\ \'world\'"
    echo ${VAR:q}  # --> Hello zshell 'world'

    VAR="UP down"
    echo ${VAR:l}   # --> up down
    echo ${VAR:u}   # --> UP DOWN

    STR="0123456789"
    echo ${STR:0:4}   # --> 012
    echo ${STR:0:-2}  # --> 01234567
    echo ${STR:2}     # --> 23456789


-------------------
Parameter Expansion
-------------------
* `Zshell path modifiers <https://www.tlbx.app/blog/zshell-path-modifiers>`_
* `Modifiers <http://zsh.sourceforge.net/Doc/Release/Expansion.html#Parameter-Expansion-Flags>`_
* ``LESS="$LESS+/^ *Parameter Expansion Flags$" man 1 zshexpn``

.. code-block:: bash

    VAR="UP down"
    echo ${(L)VAR}  # --> up down
    echo ${(C)VAR}  # --> Up Down
    echo ${(U)VAR}  # --> UP DOWN

    STR="foo
    bar"
    array=(${(f)STR})       # $array[1] == foo
    array=(${(ps/\n/)STR})  # $array[2] == bar
    string=${(F)array}      # $string == $STR
    string=${(pj/\n/)array}

---------------
Glob Qualifiers
---------------
* `Glob Qualifiers <http://zsh.sourceforge.net/Doc/Release/Expansion.html#Glob-Qualifiers>`_
* ``LESS="$LESS+/^ *Glob Qualifiers$" man 1 zshexpn``

.. code-block:: bash

    print -l **/*(/)        # show only directories
    print -l **/*(.)        # show only regular files
    ls -l    **/*(L0)       # show empty files
    ls -l    **/*(Lk+3)     # show files greater than 3 KB
    print -l **/*(mh-1)     # show files modified in the last hour
    ls -l    **/*(om[1,3])  # sort files from most to least recently modified and show the last 3

    ls *.^c(.)            # all files excluding c files
    ls -l *.(png|jpg|gif) # images only
    ls *(*)               # executables only
    ls /etc/**/zsh        # which directories contain 'zsh'?
    ls **/*(/^F)          # list empty directories
    ls /etc/*(@)          # symlinks only
    ls **/*(-@)           # list dangling symlinks

    # .     - regular files
    # Lm-2  - files smaller than 2 MB
    # mh-1  - files modified in the last hour
    # om    - recent first
    # [1,3] - first 3 files
    ls -l zsh_demo/**/*(.Lm-2mh-1om[1,3])

    # show every continent that doesn't contain a country named malta
    # e         - estring (delimited with e.g. `:`)
    # $REPLY    - current file
    # [[ ... ]] - conditional expression
    print -l zsh_demo/*/*(e:'[[ ! -e $REPLY/malta ]]':)

    # Return the parent folder of the first file
    print -l zsh_demo/data/europe/poland/*.txt([1]:h)

    my_file=(zsh_demo/data/europe/poland/*.txt([1]))
    print -l $my_file(:h)    # this is the syntax we saw before
    print -l ${my_file:h}    # I find this syntax more convenient

    echo ${(s._.)file:t}
