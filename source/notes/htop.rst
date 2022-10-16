
====
Tops
====
* `TOP'ай сюда <https://habr.com/ru/post/114082/>`_

######
Uptime
######
* https://peteris.rocks/blog/htop/

.. code-block:: sh

    $ uptime
     02:52:30 up 17 days,  6:47,  4 users,  load average: 1.68, 1.59, 1.47

    $ strace uptime 2>&1 |grep open
    ...
    openat(AT_FDCWD, "/proc/uptime", O_RDONLY) = 3
    openat(AT_FDCWD, "/var/run/utmp", O_RDONLY|O_CLOEXEC) = 4
    openat(AT_FDCWD, "/proc/loadavg", O_RDONLY) = 4

.. code-block:: text
    :caption: /proc/uptime

    1493239.36 4687326.28
                \_ time spent in idle state [seconds]
     \_ total time the machine is up [seconds]

.. code-block:: text
    :caption: /proc/loadavg

                     _ # of processes (currently running / all)
                    /
    1.68 1.59 1.47 2/887 41591 <-- last PID used
     \__________/
        \_ load avg for 1m, 5m and 15m

#########################
Load (Average) Definition
#########################
* Load: number of processes currently running.
* Load average:
    - Simple definition: average Load during last 1, 5 and 15 minutes
    - Correct definition: exponentially damped moving average of the load number

From Wikipedia::

    Mathematically speaking, all three values
    always average all the system load since the system started up.
    They all decay exponentially, but they decay at different speed.
    Hence, the 1-minute load average will add up 63% of the load from last minute,
    plus 37% of the load since start up excluding the last minute.
    Therefore, it's not technically accurate
    that the 1-minute load average only includes the last 60 seconds activity
    (since it still includes 37% activity from the past),
    but that includes mostly the last minute.

Converting to percent load: divide by number of cores (``nproc``).

Important::

    Because the load number also includes processes in uninterruptible states
    which don't have much effect on CPU utilization,
    it's not quite correct to infer CPU usage from load averages.
    This also explains why you may see high load averages but not much load on the CPU.

.. code-block:: sh

    $ curl -s https://raw.githubusercontent.com/torvalds/linux/v4.8/kernel/sched/loadavg.c | head -n 7
    /*
     * kernel/sched/loadavg.c
     *
     * This file contains the magic bits required to compute the global loadavg
     * figure. Its a silly number but people think its important. We go through
     * great pains to make it work on big machines and tickless kernels.
     */

There are tools like mpstat that can show the instantaneous CPU utilization:

.. code-block:: sh

    $ sudo apt install -y sysstat
    $ mpstat 1
    Linux 4.4.0-47-generic (hostname)   12/03/2016      _x86_64_        (1 CPU)

    10:16:20 PM  CPU    %usr   %nice    %sys %iowait    %irq   %soft  %steal  %guest  %gnice   %idle
    10:16:21 PM  all    0.00    0.00  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00
    10:16:22 PM  all    0.00    0.00  100.00    0.00    0.00    0.00    0.00    0.00    0.00    0.00

###############
Files in procfs
###############

First look:

.. code-block:: sh

    $ sleep 1000 &
    [1] 12503

    $ echo $!
    12503

    $ ls /proc/12503

Exploring:

.. code-block:: sh

    $ cat /proc/12503/cmdline
    sleep1000$

    $ od -c /proc/12503/cmdline
    0000000   s   l   e   e   p  \0   1   0   0   0  \0
    0000013

    $ tr '\0' '\n' < /proc/12503/cmdline
    sleep
    1000
    $ strings /proc/12503/cmdline
    sleep
    1000

Procfs can have links:

.. code-block:: sh

    $ ls -ld /proc/$$/*(@)  # zsh: list symlinks
    lrwxrwxrwx 1 lain lain 0 Sep  2 22:26 /proc/1622585/cwd -> /home/lain/projects/outlines
    lrwxrwxrwx 1 lain lain 0 Sep  2 22:26 /proc/1622585/exe -> /usr/bin/zsh
    lrwxrwxrwx 1 lain lain 0 Sep  2 22:27 /proc/1622585/root -> /

So this is how htop, top, ps and other diagnostic utilities
get their information about the details of a process:
they read it from ``/proc/<pid>/<file>``.

#############
Process State
#############

Possible states::

    R    running or runnable (on run queue)
    S    interruptible sleep (waiting for an event to complete)
    D    uninterruptible sleep (usually IO)
    Z    defunct ("zombie") process, terminated but not reaped by its parent
    T    stopped by job control signal
    t    stopped by debugger during the tracing
    X    dead (should never be seen)

R - running or runnable (on run queue)
======================================
Process is currently running
or on a run queue waiting to run.

S - interruptible sleep (waiting for an event to complete)
==========================================================
Not currently being executed on the CPU.
Instead, this process is waiting for something - an event or a condition - to happen.
When an event happens, the kernel sets the state to running.

.. code-block:: sh

    $ sleep 1000 &
    [1] 2264633

    $ ps -C sleep f  # or `ps f |grep sleep`
        PID TTY      STAT   TIME COMMAND
    2264633 pts/1    S      0:00 sleep 1000

    $ kill -INT 2264633  # Sends Ctrl+C / the interrupt signal / kill -2
                         # kill sends SIGTERM by default

D - uninterruptible sleep (usually IO)
======================================
Cannot receive a signal.

This state is used if the process must wait without interruption
or when the event is expected to occur quickly.
Example: disk I/O.

.. TODO: nfs mounting example still can be killed with `kill -INT`. Why?

Z - defunct ("zombie") process, terminated but not reaped by its parent
=======================================================================
When a process ends via exit and it still has child processes,
the child processes become zombie processes.

* OK if exist for a short time
* Indicate a bug in a program otherwise
* Does not consume memory, only PID
* Can't be killed
* You can ask nicely the parent process to reap the zombies (``kill -CHLD``)
* You can kill the zombie's parent process to get rid of the parent and its zombies

.. code-block:: c

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>

    int main() {
      printf("Running\n");

      int pid = fork();

      if (pid == 0) {
        printf("I am the child process\n");
        sleep(30);
        printf("The child process is exiting now\n");
        exit(0);
      } else {
        printf("I am the parent process\n");
        printf("The parent process is sleeping now\n");
        sleep(60);
        printf("The parent process is finished\n");
      }

      return 0;
    }

.. code-block:: sh

    $ gcc zombie.c -o zombie && ./zombie

    $ ps f
      PID TTY      STAT   TIME COMMAND
     3514 pts/1    Ss     0:00 -bash
     7911 pts/1    S+     0:00  \_ ./zombie
     7912 pts/1    Z+     0:00      \_ [zombie] <defunct>
     1317 pts/0    Ss     0:00 -bash
     7913 pts/0    R+     0:00  \_ ps f

Why keep the zombie processes around then?

The parent process has the option to find out its child process exit code (in a signal handler) with the ``wait`` system call. If a process is sleeping, then it needs to wait for it to wake up.

.. TODO: kill -CHLD on parent process does not get rid of the zombie

T - stopped by job control signal
=================================
Control with ``Ctrl+Z`` and ``fg``.
Another option: ``kill -STOP`` and ``kill -CONT``.

t - stopped by debugger during the tracing
==========================================

.. code-block:: sh

    $ nc -l 1234 &
    [1] 3905

    $ sudo gdb -p 3905

    $ ps u
    USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
    ubuntu    3905  0.0  0.1   9184   896 pts/0    t    07:41   0:00 nc -l 1234


####
Htop
####
* https://peteris.rocks/blog/htop/

.. role:: raw-html(raw)
   :format: html

------------
Reading htop
------------
* `Understanding and using htop to monitor system resources <https://www.deonsworld.co.za/2012/12/20/understanding-and-using-htop-monitor-system-resources/>`_

System wide cpu usage
=====================
* :raw-html:`<font color="blue">low priority processes (nice > 0)</font>`
* :raw-html:`<font color="green">normal (user) processes</font>`
* :raw-html:`<font color="red">kernel processes</font>`
* :raw-html:`<font color="orange">IRQ time</font>`
* :raw-html:`<font color="magenta">Soft IRQ time</font>`
* :raw-html:`<font color="gray">IO Wait time</font>`

System wide memory usage
========================
* :raw-html:`<font color="green">Used memory pages</font>`
* :raw-html:`<font color="blue">Buffer pages</font>`
* :raw-html:`<font color="orange">Cache pages</font>`

Load average
============
* 100% utilization is 1 CPU fully loaded
* Load average: for 1/5/15 minutes
* Note that loads can exceed 1.0 this just means that processes have to wait longer for the cpu.

Information on processes
========================
* **PID:** A process's process ID number.
* **USER:** The process's owner.
* **PR:** The process's priority. The lower the number, the higher the priority.
* **NI:** The nice value of the process, which affects its priority.
* **VIRT:** How much virtual memory the process is using.
* **RES:** How much physical RAM the process is using, measured in kilobytes.
* **SHR:** How much shared memory the process is using.
* **S:** The current status of the process (zombied, sleeping, running, uninterruptedly sleeping, or traced).
* **%CPU:** The percentage of the processor time used by the process.
* **%MEM:** The percentage of physical RAM used by the process.
* **TIME+:** How much processor time the process has used.
* **COMMAND:** The name of the command that started the process

The difference between VIRT, RES and SHR
========================================
* **VIRT:** virtual size of a process; a sum of memory it is actually using, memory it has mapped into itself (for instance the video card's RAM for the X server), files on disk that have been mapped into it (most notably shared libraries), and memory shared with other processes. VIRT represents how much memory the program is able to access at the present moment.
* **RES:** resident size; actual physical memory a process is consuming. Corresponds directly to the %MEM column
* **SHR** indicates how much of the VIRT size is actually sharable memory or libraries. In the case of libraries, it does not necessarily mean that the entire library is resident. For example, if a program only uses a few functions in a library, the whole library is mapped and will be counted in VIRT and SHR, but only the parts of the library file containing the functions being used will actually be loaded in and be counted under RES.

---------
Internals
---------
* `htop explained <https://peteris.rocks/blog/htop/>`_


#####
Iftop
#####

Example::

                                                __ 2s, 10s and 40s
                                               /
                                              /
    foo.example.com  =>  bar.example.com      1Kb  500b   100b
                     <=                       2Mb    2Mb    2Mb

* TX: Transmit (from this server)
* RX: Receive (to this server)


#######
Netstat
#######

#######
Nethogs
#######
