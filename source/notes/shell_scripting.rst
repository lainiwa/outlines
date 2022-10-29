
===============
Shell Scripting
===============


#####################
Logging and Debugging
#####################
* `Structured Logging in a Shell Script with jq <https://medium.com/@jesse.riddle/structured-logging-in-a-shell-script-with-jq-f7542a94a1f6>`_
* `COLODEBUG: a simple way to improve bash script debugging <https://johannes.truschnigg.info/writing/2021-12_colodebug/>`_
* `Shell Scripting: Expert Recipes for Linux, Bash, and More: logger <https://www.oreilly.com/library/view/shell-scripting-expert/9781118166321/c14-anchor-6.xhtml>`_
* `Simple bash debugger using trap DEBUG <https://selivan.github.io/2022/05/21/bash-debug.html>`_

Structured logging with jq:

.. code-block:: sh

    __log(){
      jq \
        --monochrome-output \
        --compact-output \
        --raw-output \
        --arg timestamp "$(date "+%Y%m%dT%H%M%S")" \
        --arg log_level "${1}" \
        --arg message   "${2}" \
         '.timestamp=$timestamp|.log_level=$log_level|.message=$message' \
         <<<'{}' >&2
    }

    __log "INFO" "Hello, World"

Print with a colon:

.. code-block:: sh

    if [[ -n ${COLODEBUG:-} && ${-} != *x* ]]; then
        :() {
          [[ ${1:--} != ::* ]] && return 0
          printf '%s\n' "${*}" >&2
        }
    fi

    : :: note this line
    : ::NOTICE::

    # This is an example comment
    : This is a colon comment
    : :: This is a more verbose colon comment

    # Example usage:
    # COLODEBUG=1 ./myscript.sh

Write logs to syslog/journald:

.. code-block:: sh

    logger -t checkfs -s -p user.err "Filesystem $filesystem is at $usage"
    # or, with long options:
    logger --tag checkfs --stderr --priority user.err "Filesystem $filesystem is at $usage"

Besides traps(handlers) for signals, bash have 4 special traps:

* ``EXIT`` to run on exit from the shell.
* ``RETURN`` to run each time a function or a sources script finishes.
* ``ERR`` to run each time command failure would cause the shell to exit if ``set -e`` is used.
* ``DEBUG`` to execute before every command.

The last one allows to create a simple debugger inside a bash script:

.. code-block:: sh

    function _trap_DEBUG() {
        echo "# $BASH_COMMAND";
        while read -r -e -p "debug> " _command; do
            if [ -n "$_command" ]; then
                eval "$_command";
            else
                break;
            fi;
        done
    }

    trap '_trap_DEBUG' DEBUG

Alternatives:

* `selivan/bash-debug <https://github.com/selivan/bash-debug>`_
* `bashdb <http://bashdb.sourceforge.net/>`_


#######
Locking
#######
* `Bash: execute a script only when no other instance of the script is running. <https://lovethepenguin.com/bash-execute-a-script-only-when-no-other-instance-of-the-script-is-running-283e7d726547>`_

Run only one instance of the script:

.. code-block:: sh

    # inside the script
    [ "$(pidof -x $(basename $0))" != $$ ] && exit

    # or, controlling outside the script:
    # -w 0: wait for the lock release for 0s (exit immediately)
    flock \
        -w 0 /tmp/test.lock \
        -c 'echo "sleeping" && sleep 60' ||
    echo "cannot be executed an instance already runs"


#########
Functions
#########
* `SO: difference between function foo and foo" <https://unix.stackexchange.com/a/73854>`_
* `Bash functions are better than I thought <https://cuddly-octo-palm-tree.com/posts/2021-10-31-better-bash-functions/>`_

In bash/zsh keyword ``function`` intruduced for historical reasons. Use more portable ``f() ...``

Local variables are dinamically scoped (seen by functions down the call stack):

.. code-block:: sh

    f1() { local a; a=1 f3; }
    f2() { local a; a=2 f3; }
    f3() { echo $a; }

    f1  # prints 1
    f2  # prints 2
