
===============
Shell Scripting
===============

#######
Logging
#######
* `Structured Logging in a Shell Script with jq <https://medium.com/@jesse.riddle/structured-logging-in-a-shell-script-with-jq-f7542a94a1f6>`_
* `COLODEBUG: a simple way to improve bash script debugging <https://johannes.truschnigg.info/writing/2021-12_colodebug/>`_
* `Shell Scripting: Expert Recipes for Linux, Bash, and More: logger <https://www.oreilly.com/library/view/shell-scripting-expert/9781118166321/c14-anchor-6.xhtml>`_

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
    /usr/bin/flock \
        -w 0 /tmp/test.lock \
        -c 'echo "sleeping" && sleep 60' ||
    echo "cannot be executed an instance already runs"
