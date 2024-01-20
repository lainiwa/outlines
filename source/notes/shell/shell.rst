
===============
Shell Scripting
===============
* https://mywiki.wooledge.org/BashPitfalls
* https://raimonster.com/scripting-field-guide/
* https://github.com/dylanaraps/pure-sh-bible
* https://github.com/dylanaraps/pure-bash-bible
* https://www.oreilly.com/library/view/bash-cookbook/0596526784/ch05s02.html
* https://google.github.io/styleguide/shellguide.html
* https://news.ycombinator.com/item?id=36605869

.. include:: .help.rst
.. include:: .logging_debugging.rst
.. include:: .locking.rst
.. include:: .functions.rst
.. include:: .shebangs.rst
.. include:: .traps.rst
.. include:: .self_extracting.rst
.. include:: .argparse.rst
.. include:: .zsh.rst

Script Template
###############
* `My Minimal, Safe Bash Script Template <https://link.medium.com/ARddINhvUcb>`_

.. literalinclude:: template.sh
  :caption: template.sh
  :language: shell

Testing
#######
* `Writing Unit-Tests and Mocks for UNIX Shells <https://poisel.info/posts/2022-05-10-shell-unit-tests/>`_

Exit Codes
##########
* `Bash command line exit codes demystified <https://www.redhat.com/sysadmin/exit-codes-demystified>`_
* `Man SYSEXITS(3) <https://www.freebsd.org/cgi/man.cgi?query=sysexits>`_

Redirections
############
* `Bash One-Liners Explained, Part III: All about redirections <https://catonmat.net/bash-one-liners-explained-part-three>`_
* `Bash Redirections Cheat Sheet <https://catonmat.net/ftp/bash-redirections-cheat-sheet.pdf>`_

Working with JSON
#################
* `shell tip: print json with printf <https://j3s.sh/thought/shell-tip-print-json-with-printf.html>`_
  - `lobste.rs <https://lobste.rs/s/4wiwig/shell_tip_print_json_with_printf>`__

.. code-block:: bash

  $ printf '{"name": "%s", "sign": "%s"}' "$name" "$sign"
  {"name": "jes", "sign": "aquarius"}

  $ jo hostname=$(hostname) meta=$(jo user=$USER term=$TERM)
  {"hostname":"localhost","meta":{"user":"root","term":"xterm-256color"}}

  $ jq --null-input --arg username jdoe --arg password '$ec\ret"' '{"username":$username, "password":$password}'
  {
    "username": "jdoe",
    "password": "$ec\\ret\""
  }

Network
#######
* https://unix.stackexchange.com/a/421403

Parallelization
###############

ZSH Zargs
=========
* `zsh-builtin xargs <https://neg-serg.github.io/2017/03/zargs-howto/>`_

Xargs
=====
* https://zsh.sourceforge.io/Doc/Release/User-Contributions.html
* https://www.pixelstech.net/article/1700239426-How-to-use-xargs-command-in-Linux

GNU Parallel
============
