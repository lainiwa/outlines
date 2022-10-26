
=============
Load Averages
=============
* `htop explained <https://peteris.rocks/blog/htop/>`_
* `UNIX Load Average Part 1: How It Works <https://www.helpsystems.com/resources/guides/unix-load-average-part-1-how-it-works>`_
* `Linux Load Averages: Solving the Mystery <https://www.brendangregg.com/blog/2017-08-08/linux-load-averages.html>`_
* `High System Load with Low CPU Utilization on Linux? <https://tanelpoder.com/posts/high-system-load-low-cpu-utilization-on-linux/>`_
* `Where Linux's load average comes from in the kernel <https://utcc.utoronto.ca/~cks/space/blog/linux/LoadAverageWhereFrom>`_
* `Linux load average - the definitive summary  <http://blog.angulosolido.pt/2015/04/linux-load-average-definitive-summary.html>`_
* `SO: Understanding top and load average <https://unix.stackexchange.com/questions/9465/understanding-top-and-load-average>`_
* `Load average explained <https://wiki.nix-pro.com/view/Load_average_explained>`_


######
Uptime
######

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
    :caption: /proc/loadavg (man 5 proc)

                       # of processes (currently running (state R) or
                     _ #               waiting for disk IO (state D) / all)
                    /
    1.68 1.59 1.47 2/887 41591 <-- last PID used
     \__________/
        \_ load avg for 1m, 5m and 15m


############
Instant Load
############
Instantaneous load of a system:
the number of tasks (processes and threads)
that are willing to run at a given time t.

Willing to run:
means in state R (running/runnable)
or D (waiting uninterruptably; blocked on some resource, usually IO):

.. code-block:: sh

    $ ps -eL h -o state | egrep "R|D" | wc -l
    2

Note:
Same can be parsed from
``/proc/loadavg`` (4th field) or
``/proc/stat`` (``procs_running``, ``procs_blocked``) but:

* ``/proc/loadavg`` doesn't seem to count processes in state D
* both do not include threads, even though they are taken into account in the load average numbers exposed by the kernel


#########################
Load (Average) Definition
#########################
* Exponentially-damped/decaying moving average of the **Load** number
* Average length of run queue
* Number of running tasks

Load average formula::

    a(t,A) = a(t-1) * exp(-5/60A)
           + l(t) * (1-exp(-5/60A))
    where:
      A = 1, 5 or 15
      l(t) = instantaneous load

     The load average values are calculated by the kernel every 5 seconds using a(t,A).

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


#######################################
CPU Load Average to System Load Average
#######################################
The change (the swapping state was later removed from Linux)::

    From: Matthias Urlichs <urlichs@smurf.sub.org>
    Subject: Load average broken ?
    Date: Fri, 29 Oct 1993 11:37:23 +0200

    The kernel only counts "runnable" processes when computing the load average.
    I don't like that; the problem is that processes which are swapping or
    waiting on "fast", i.e. noninterruptible, I/O, also consume resources.

    It seems somewhat nonintuitive that the load average goes down when you
    replace your fast swap disk with a slow swap disk...

    Anyway, the following patch seems to make the load average much more
    consistent WRT the subjective speed of the system. And, most important, the
    load is still zero when nobody is doing anything. ;-)

    --- kernel/sched.c.orig Fri Oct 29 10:31:11 1993
    +++ kernel/sched.c  Fri Oct 29 10:32:51 1993
    @@ -414,7 +414,9 @@
        unsigned long nr = 0;

        for(p = &LAST_TASK; p > &FIRST_TASK; --p)
    -       if (*p && (*p)->state == TASK_RUNNING)
    +       if (*p && ((*p)->state == TASK_RUNNING) ||
    +                  (*p)->state == TASK_UNINTERRUPTIBLE) ||
    +                  (*p)->state == TASK_SWAPPING))
                nr += FIXED_1;
        return nr;
     }
    --
    Matthias Urlichs        \ XLink-POP N|rnberg   | EMail: urlichs@smurf.sub.org
    Schleiermacherstra_e 12  \  Unix+Linux+Mac     | Phone: ...please use email.
    90491 N|rnberg (Germany)  \   Consulting+Networking+Programming+etc'ing


#########
Tick Rate
#########
Tick rate has a frequency of HZ hertz and a period of 1/HZ seconds.
If HZ is defined as 1000 that means that maximum amount of time that a process can take a CPU to run its instructions is 1/1000 of a second, after this period the interrupt will occur and internal Linux timer will take over a control on this CPU.

.. code-block:: text
    :caption: include/asm-i386/param.h

    #define HZ 1000        /* internal kernel time frequency */

Find current ``HZ`` with ``grep 'CONFIG_HZ=' /boot/config-$(uname -r)``.


#####
Jiffs
#####
Show current jiffs: ``sudo grep -E "^cpu|^jiff" /proc/timer_list``

The load average consists of measurements (samples) taken every 5 seconds:

.. code-block:: text
    :caption: include/linux/sched/loadavg.h

    #define LOAD_FREQ       (5*HZ+1)        /* 5 sec intervals */


########################
Load Average is Relative
########################
The number of tasks willing to run depends on:

* the architecture of the software (single process? multiple processes? do they depend on each other?)
* the CPU and IO throughput requested by the software that is running
* the CPU and IO performance of that system
* the number of available cores

The acceptable load average is empirically discovered.

Furthermore:

* For same requested IO an implementation with more tasks (processes and threads) will generate higher load
* software setting all CPU cores to 100% will genrate higher LA on system with with smaller number of (or slower) cores


#################################
Load Average and CPU Usage Values
#################################
Expressed in % of CPU time:

* ``%usr``: Time spent running non-kernel code. (user time, including nice time)
* ``%sys``: Time spent running kernel code. (system time)
* ``%wait``: Time spent waiting for IO. Note: ``%iowait`` is not an indication of the amount of IO going on, it is only an indication of the extra %usr time that the system would show if IO transfers weren't delaying code execution.
* ``%idle``: Time spent idle.

Summary:

* if %sys+%usr=100 for all cores, then the Instant Load (IL) >= ``nproc``
* the inverse might not be true, since many processes may be I/O waiting (state D)
* if IL > ``nproc`` then system can't be mostly idle
* system can be slow even if IL < ``nproc``, because IO-intensive tasks might be a bottleneck
* if IO is negligible (no state D) and ``%idle > 0`` then ``IL = ((100 - %idle)/100) * nproc``. Example: 4 cores, ``%sys+%usr=90`` the IL would be ``((100-10)/100)*4 = 3.6`` Can be tested with ``stress -c X``, where ``X < nproc``, otherwise it will cause ``%idle=0``.

It is more complicated with Hyperthreading.


######
mpstat
######
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
