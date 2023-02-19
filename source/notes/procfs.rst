
====================
``/proc`` filesystem
====================
* `How to check if pid is threads or process <https://stackoverflow.com/a/60260253>`_
* `Does /proc/ contains tid? <https://unix.stackexchange.com/a/608301>`_

Process or a thread?

.. code-block:: sh

    $ PID=$(pgrep -x multipathd)
    $ echo $PID  # 521

    $ # Same Pid and Thread group id: task 521 is a process
    $ egrep '^(Tgid|Pid)' /proc/$PID/task/521/status
    Tgid:   521
    Pid:    521

    $ # Different Pid and Thread group id: task 526 is a thread
    $ egrep '^(Tgid|Pid)' /proc/$PID/task/526/status
    Tgid:   521
    Pid:    526

.. code-block:: sh

    # Lists only pids, not tids
    ls /proc
    # But tids still can be accessed through /proc
