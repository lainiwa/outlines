
=======
Python
=======


$ python -q

.. code-block:: python

    >>> from types import ModuleType
    >>> ModuleType
    <class 'module'>

    >>> import sys
    >>> ModuleType is type(sys)
    True

    >>> m = ModuleType('m')
    >>> m.__dict__
    {'__name__': 'm', '__doc__': None, '__package__': None, '__loader__': None, '__spec__': None}

    >>> __name__  # global variable
    '__main__'
    >>> current_module = sys.modules[__name__]  # sys.modules stores imported modules
    >>> current_module.__dict__ is globals()
    True
    >>> # Built-in modules are C modules compiled into the python executable
    >>> sys.builtin_module_names
    ('_abc', '_ast', '_codecs', '_collections', '_functools', '_imp', '_io', '_locale', '_operator', '_peg_parser', '_signal', '_sre', '_stat', '_string', '_symtable', '_thread', '_tracemalloc', '_warnings', '_weakref', 'atexit', 'builtins', 'errno', 'faulthandler', 'gc', 'itertools', 'marshal', 'posix', 'pwd', 'sys', 'time', 'xxsubtype')

Switch to other venv in runtime
-------------------------------
Check ``.venv/pyvenv.cfg`` for ``include-system-site-packages`` line.
If ``False``:

.. code-block:: python

    import sys

    list(
        map(
            lambda x: sys.path.remove(x)
            if x.endswith('-packages')
            or '/dist-packages/' in x
            or '/site-packages/' in x
            else False,
            sys.path.copy(),
        )
    )

else if ``True``:

.. code-block:: python

    sys.path.insert(
        0,
        f'.venv/lib/python{sys.version_info.major}.{sys.version_info.minor}/site-packages',
    )
