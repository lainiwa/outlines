
======
Python
======

.. include:: .dataclasses.rst
.. include:: .decorators.rst
.. include:: .immutability.rst
.. include:: .parsing.rst

* https://peps.python.org/pep-0570/
* https://stackoverflow.com/questions/22500267/type-classes-in-dynamic-languages

Pattern Matching
################
* https://mathspp.gumroad.com/l/cheatsheet_match_statement
* https://mathspp.com/blog/pydonts/structural-pattern-matching-tutorial
* https://mathspp.com/blog/pydonts/structural-pattern-matching-anti-patterns
* https://earthly.dev/blog/structural-pattern-matching-python/
* https://www.infoworld.com/article/3609208/how-to-use-structural-pattern-matching-in-python.html

Memoization and Caching
#######################

String Formatting
#################
* https://pybit.es/articles/python-f-string-codes-i-use-every-day/

.. code-block:: py

    # Print key=value
    print(f"{key=}")

    # Floats
    pi = 3.141592
    precision = 3
    print(f"{pi:.{precision}f}") # "3.142"

    # Percentage
    val = 1.255
    print(f"{val:%}")    # 125.500000%
    print(f"{val:.0%}")  # 125%
    print(f"{val:.1%}")  # 125.5%

    # Scientific notation
    val = 1.2345e3
    print(f"{val:e}")    # 1.234500e+03
    print(f"{val:E}")    # 1.234500E+03
    print(f"{val:.2e}")  # 1.23e+03

    # Integers
    val = 1_000_000
    print(f"{val:,d}")  # 1,000,000
    print(f"{val:_d}")  # 1_000_000

    # Numbers
    val = 1
    print(f"{val =: n}")  # val = 1

    # Dates
    day = date(year=2022, month=9, day=1)
    print(f"{day}")
    print(f"{day:%Y-%m-%d}")  # default appearance
    print(f"{day:%Y/%m/%d}")  # use `/` as separator
    print(f"{day:%Y %b %d}")  # 2022 Sep 01
    print(f"{day:%Y %B %d}")  # 2022 September 01
    print(f"{day:%Y %b %d (%A)}")  # 2022 Sep 01 (Thursday)

    # Datetime
    day_and_time = datetime(year=2022, month=9, day=1, hour=17, minute=30, second=45)
    now = datetime.now()
    print(f"{day_and_time}")                   # 2022-09-01 17:30:45
    print(f"{now}")                            # 2022-12-08 15:49:37.810347
    print(f"{now:%Y-%m-%d %H:%M:%S.%f}")       # 2022-12-08 15:49:37.810347
    print(f"{now:%Y-%m-%d %H:%M:%S.%f}"[:22])  # 2022-12-08 15:49:37.81

    # Padding
    val = 1
    print(f"{val:3d}")   # "  1"
    print(f"{val:03d}")  # "001"

    # Positive/negative sign
    positive = 1.23
    negative = -1.23
    print(f"1: {positive:+.2f}   {negative:+.2f}")  # 1: +1.23   -1.23
    print(f"2: {positive:-.2f}   {negative:-.2f}")  # 2: 1.23   -1.23
    print(f"3: {positive: .2f}   {negative: .2f}")  # 3:  1.23   -1.23


Profiling
#########
* `plasma-umass/scalene <https://github.com/plasma-umass/scalene>`_
    - has comparison with other profilers: `img <https://raw.githubusercontent.com/plasma-umass/scalene/master/docs/images/profiler-comparison.png>`__
* `bloomberg/memray <https://github.com/bloomberg/memray>`_
    - has pytest plugin
* `benfred/py-spy <https://github.com/benfred/py-spy>`_
* `joerick/pyinstrument <https://github.com/joerick/pyinstrument>`_
    - can integrate with FastAPI, call stack is available when ``?profile=true`` is added to the url


TODO
####
* https://adamj.eu/tech/2021/05/11/python-type-hints-args-and-kwargs/
* https://rednafi.com/python/annotate_args_and_kwargs/
* https://rednafi.com/python/statically_enforcing_frozen_dataclasses/
* https://www.stuartellis.name/articles/python-modern-practices/
