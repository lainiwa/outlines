
================
Computer Science
================

Type Theory
###########

Unit Type
=========
* `Unit Type <https://en.wikipedia.org/wiki/Unit_type>`_
* `Void vs Unit <http://james-iry.blogspot.com/2009/07/void-vs-unit.html>`_
* `SO: What is () in Haskell, exactly? <https://stackoverflow.com/questions/16892570/what-is-in-haskell-exactly>`_

Unit type is a type that allows only one value.

* Can be thought of as the type of 0-tuples (i.e. the product of no types)
* In Haskell: the type is called ``()`` and the value is also ``()``
* In Python: type ``NoneType`` allows single value ``None``

Type theorists will also call the unit type "1" (not to be confused with the value 1).
Consider type ``(Foo, unit)`` which can also be written as ``Foo × 1``.
See that unit has only 1 value, and behaves like a 1 at the type level.

Unit type vs Void type
----------------------
* Void type serves some of its functions, but it has some limitations
* Both void and unit are used to indicate
  that a function is called only for its side effects

Difference in calling convention:

Unit type may always be the type of the argument to a function,
but the void type cannot be the type of an argument.

.. code:: cpp

    void a(void) {}
    void b(void) {}

    unit_type c(unit_type) { return the_unit; }
    unit_type d(unit_type) { return the_unit; }

    class unit_type {};  // C++ allows empty classes
    const unit_type the_unit;

    int main(void)
    {
      a(b());         // compile-time error here
      c(d(the_unit)); // OK
      return 0;
    }

Difference in storage:

Void type is special and can never be stored in a record type.
While this may seem a useless feature,
it does allow one for instance to elegantly implement a set as a map to the unit type;
in the absence of a unit type,
one can still implement a set this way by storing some dummy value of another type for each key.


Bottom Type: ⊥
==============
* `Getting to the Bottom of Nothing At All <http://james-iry.blogspot.com/2009/08/getting-to-bottom-of-nothing-at-all.html>`_
* `Bottom type <https://en.wikipedia.org/wiki/Bottom_type>`_
* `Haskell Wiki: Bottom <https://wiki.haskell.org/Bottom>`_

The bottom type of a type system is the type that is a subtype of all other types.
Typically no distinction is drawn between the bottom type and the empty type (also known as "zero" or "never" type).

In languages:

* In Haskell: ``undefined`` constant or terms created by ``error`` constructor. Also: ``Data.Void``
  may be assigned any type.
  Evaluating them causes the code to abort unrecoverably.
* In Python: bottom type is ``typing.NoReturn`` (``typing.Never`` since version 3.11)

Functions that return nothing, not even ``()`` (they *diverge* rather than *converge*):

* ``X foo(){ while(true); }`` or ``X foo(){ return foo(); }``
* ``X foo(){ throw new RuntimeException(); }``
* ``X foo(){ System.exit(1); return null; }``

If you set ``X`` to e.g. ``String``, that would pass type checking.
Since type checker can't detect non-termination (c.f. Turing Halting Problem) it:

* assumes ``foo()`` declaration is correct and does return a ``String``
* goes looking for a contradiction
* inside the function compiler sees ``return foo()``
* which it already assumed a ``String``
* no contradiction
* the word "tautology" should come to mind: by assuming X is true, the type checker has proved that X is true

It's just proving something a bit weaker than you might think at first.
Instead of proving that "```foo()`` will compute something that is a ``String``"
it's proving that "```foo()`` won't compute something that isn't a ``String``.

Category Theory
###############

Abstract Algebra
################
* https://en.wikipedia.org/wiki/Associative_property
* https://en.wikipedia.org/wiki/Commutative_property

Semigroup
=========
* https://en.wikipedia.org/wiki/Semigroup

Semigroup is an algebraic structure consisting of a set together with an associative internal binary operation on it.

Monoid
======
* https://math.stackexchange.com/questions/4052477/what-is-a-monoid-in-simple-terms
* https://dev.to/nickytonline/explain-what-a-monoid-is-like-im-five-4gpf
* https://en.wikipedia.org/wiki/Monoid
* https://habr.com/ru/companies/jugru/articles/340178/

Monoid is a set equipped with an associative binary operation and an identity element. For example, the nonnegative integers with addition form a monoid, the identity element being 0.

Laziness
########
* http://james-iry.blogspot.com/2011/05/why-eager-languages-dont-have-products.html
* https://www.quora.com/What-is-meant-by-lazy-languages-dont-have-real-sums-and-eager-languages-dont-have-real-products
* https://www.reddit.com/r/types/comments/72djqu/eager_languages_dont_have_product_and_lazy/

