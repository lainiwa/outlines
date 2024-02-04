
=====
Idris
=====
* `A Crash Course in Idris 2 <https://idris2.readthedocs.io/en/latest/tutorial/index.html>`_

Types and Functions
###################
* https://idris2.readthedocs.io/en/latest/tutorial/typesfuns.html

.. code-block:: idris

   -- allows `data` declarations in `where` blocks
   foo : Int -> Int
   foo x = case isLT of
               Yes => x*2
               No => x*4
       where
          data MyLT = Yes | No

          isLT : MyLT
          isLT = if x < 20 then Yes else No

   -- To temporarily allow non-total function (disable "covering" enforcement)
   partial fromMaybe : Maybe a -> a
   fromMaybe (Just x) = x

   -- Holes
   main : IO ()
   main = putStrLn ?greeting
   -- :t greeting
   -- greeting : String
   even : Nat -> Bool
   even Z = True
   even (S k) = ?even_rhs
   -- :t even_rhs
   --    k : Nat
   -- even_rhs : Bool

   -- First Class Types
   isSingleton : Bool -> Type
   isSingleton True = Nat
   isSingleton False = List Nat
   --
   mkSingle : (x : Bool) -> isSingleton x
   mkSingle True = 0
   mkSingle False = []
   --
   sum : (single : Bool) -> isSingleton single -> Nat
   sum True x = x
   sum False [] = 0
   sum False (x :: xs) = x + sum False xs

   -- Vector
   (++) : Vect n a -> Vect m a -> Vect (n + m) a
   (++) Nil       ys = ys
   (++) (x :: xs) ys = x :: xs ++ ys

   import Data.Fin
   x : Fin 4  -- `Fin 3` Fails
   x = FS (FS (FS FZ))

   module Main
   import Data.Fin
   import Data.Vect

   -- index : forall a, n . Fin n -> Vect n a -> a
   -- index : (i : Fin n) -> (xs : Vect n a) -> a
   index : Fin n -> Vect n a -> a
   index FZ     (x :: xs) = x
   index (FS k) (x :: xs) = index k xs

   mutual
     even : Nat -> Bool
     even Z = True
     even (S k) = odd k

     odd : Nat -> Bool
     odd Z = False
     odd (S k) = even k

   ifThenElse : Bool -> Lazy a -> Lazy a -> a
   ifThenElse True  t e = t
   ifThenElse False t e = e
