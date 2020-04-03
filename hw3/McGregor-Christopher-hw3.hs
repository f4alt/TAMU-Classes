
-- CSCE 314 [Section 501] Programming Languages Spring 2020
-- Homework Assignment 3

-- Problem 1 (5 points)
-- Student Name: Christopher McGreogr
-- UIN: 726009537
-- (ACKNOWLEDGE ANY HELP RECEIVED HERE)

module Main where

import Test.HUnit
import System.Exit

data Nat = Zero | Succ Nat   deriving (Show, Eq)

add :: Nat -> Nat -> Nat
add Zero n = n
add (Succ m) n = Succ (add m n)

-- Problem 2 (10 points) Chapter 8, Exercise 1
mult :: Nat -> Nat -> Nat
mult Zero n = Zero
mult n Zero = Zero
mult (Succ m) n = add n (mult m n)

{- Here, write your step-by-step explanation of how 2*2=4 proceeds.
to get 2*2 we call mult 2 2:
mult 2 2 = mult (Succ 2) 2 = add 2 (Mult 1 2)
                           = add 2 (mult (Succ 1) 2) = add 2 (add 2 (mult 0 2))
                                                     = add 2 (add 2 (Zero)) = add 2 (2)
                                                                            = 4
-}



-- Problem 3 (25 points, see below the points distribution)
-- Chapter 16, Exercise 6 (Modified)

data Tree = Leaf Int | Node Tree Tree

--------------- Tree objects
tree1 :: Tree   -- to be used to test Problem 3.1
tree1 = Node
           (Node
              (Node (Leaf 1) (Leaf 2))
              (Leaf 3)
           )
           (Node
              (Leaf 4)
              (Node (Leaf 5) (Leaf 6))
           )

tree2 :: Tree   -- to be used to test Problem 3.1
tree2 = Node
           (Leaf 7)
           (Node
              (Node (Leaf 8) (Leaf 9))
              (Node (Leaf 10) (Leaf 11))
           )
---------------

-- Problem 3.1 (5 + 5 = 10 points)
leaves :: Tree -> Int
leaves (Leaf _) = 1
leaves (Node left right) = leaves left + leaves right

nodes :: Tree -> Int
nodes (Leaf _) = 0
nodes (Node left right) = 1 + nodes left + nodes right

-- Problem 3.2 (Base case 5 points + inductive case 10 points = 15 points)
{-- (Write your induction proof within this block comment.)
Base case:
A tree of height 0 is a single node with no children and therefore is considered just a leaf thus:
leaves (leaf 0) = 1 = nodes (leaf 0) + 1 = 0 + 1 = 1

Inductive case:
As induction hypothesis, assume that the result holds for all n >= 0;
i.e. a binary tree's leaves n = nodes n + 1

That is, a node can produce two more nodes and a node with no children is a leaf. Thus,
leaves (n + 1) = nodes (n + 1) + 1

Therefore the claim follow by induction on n
--}


-- Problem 4 (60 points) Chapter 8, Exercise 9
data Expr = Val Int | Add Expr Expr | Mul Expr Expr

type Cont = [Op]

data Op = EVALA Expr | ADD Int | EVALM Expr | MUL Int

eval :: Expr -> Cont -> Int
-- Give three definitions for eval.
-- First two definitions,
-- 1) for (Val n) and c as arguments and
-- 2) for (Add x y) and c as arguments
-- are already given in the text Section 8.7, but
-- you need to modify the second definition slightly
-- and give the third definition for (Mul x y)
eval (Val n)   c = exec c n
eval (Add x y) c = eval x (EVALA y : c)
eval (Mul x y) c = eval x (EVALM y : c)

exec :: Cont -> Int -> Int
-- Give five definitions for exec, one for an empty list and
-- one for each of the four constructors of the data type Op
exec [] n = n
exec (EVALA y : c) n = eval y (ADD n : c)
exec (ADD n : c) m = exec c (n+m)
exec (EVALM y : c) n = eval y (MUL n : c)
exec (MUL n : c) m = exec c (m * n)

value :: Expr -> Int
value e = eval e []

-- Following expressions are to test your eval and exec definitions
-- (2 + 3) + 4 = 9
e1 = (Val 3)    -- 3
e2 = (Add (Val 4) (Val 3))  -- 4 + 3 = 7
e3 = (Mul (Val 4) (Val 3))  -- 4 * 3 = 12
e4 = (Add (Add (Val 2) (Val 3)) (Val 4))  -- (2 + 3) + 4 = 9
e5 = (Mul (Mul (Val 2) (Val 3)) (Val 4))  -- (2 * 3) * 4 = 24
e6 = (Mul (Add (Val 2) (Val 3)) (Val 4))  -- (2 + 3) * 4 = 20
e7 = (Add (Mul (Val 2) (Val 3)) (Val 4))  -- (2 * 3) + 4 = 10
e8 = (Add (Mul (Val 2) (Val 3)) (Add (Val 4) (Val 5))) -- (2 * 3) + (4 + 5) = 15
e9 = (Mul (Add (Val 2) (Val 3)) (Add (Val 4) (Val 5))) -- (2 + 3) * (4 + 5) = 45
e10 = (Add (Mul (Add (Val 2) (Val 3)) (Mul (Val 4) (Val 5))) (Mul (Val 3) (Add (Val 4) (Val 7)))) -- ((2 + 3) * (4 * 5)) + (3 * (4 + 7)) = 133


myTestList =
  TestList [

    "add 1" ~: add (Succ (Succ Zero)) (Succ Zero) ~=? Succ (Succ (Succ Zero))
  , "mult 1" ~: mult (Succ (Succ Zero)) (Succ Zero) ~=? Succ (Succ Zero)
  , "mult 2" ~: mult (Succ (Succ Zero)) (Succ (Succ Zero)) ~=? Succ (Succ (Succ (Succ Zero)))
  , "mult 3" ~: mult (Succ (Succ (Succ Zero))) (Succ (Succ Zero)) ~=? Succ (Succ (Succ (Succ (Succ (Succ Zero)))))

  , "leaves 1" ~: leaves tree1 ~=? 6
  , "leaves 2" ~: leaves tree2 ~=? 5
  , "nodes 1" ~: nodes tree1 ~=? 5
  , "nodes 1" ~: nodes tree2 ~=? 4

  , "value 1" ~: value e1 ~=? 3
  , "value 2" ~: value e2 ~=? 7
  , "value 3" ~: value e3 ~=? 12
  , "value 4" ~: value e4 ~=? 9
  , "value 5" ~: value e5 ~=? 24
  , "value 6" ~: value e6 ~=? 20
  , "value 7" ~: value e7 ~=? 10
  , "value 8" ~: value e8 ~=? 15
  , "value 9" ~: value e9 ~=? 45
  , "value 10" ~: value e10 ~=? 133

    ]

main = do c <- runTestTT myTestList
          putStrLn $ show c
          let errs = errors c
              fails = failures c
          exitWith (codeGet errs fails)

codeGet errs fails
 | fails > 0       = ExitFailure 2
 | errs > 0        = ExitFailure 1
 | otherwise       = ExitSuccess
