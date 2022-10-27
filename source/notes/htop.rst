
====
Tops
====
* `TOP'ай сюда <https://habr.com/ru/post/114082/>`_


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


###
Top
###
* `top customized <https://pascalth.medium.com/top-customized-170653201ddd>`_
* `How to Make Sense of Linux System Stats in Top <https://www.tutorialworks.com/linux-top-command-explained/>`_
* `Linux top Command Tutorial for Beginners <https://www.howtoforge.com/linux-top-command/>`_
* `A Guide to the Linux Top Command <https://www.booleanworld.com/guide-linux-top-command/>`_


#####
Iotop
#####

------
IOWAIT
------
Shown by ``top`` at ``wa%``: percentage of time that all CPUs are waiting for disk accesses before they can do useful work (e.g on 4 cores max ``wa%`` is ``400.0``).
Doesn't tell much on it's own.

-----
Iotop
-----

Start ``iotop`` with:

.. code-block:: sh

    sudo iotop -oPa
    # short for `sudo iotop --only --processes --accumulated`

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
