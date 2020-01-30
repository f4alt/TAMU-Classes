
-- CSCE 314 [Section 501] Programming Languages Spring 2020
-- Homework Assignment 1

-- Problem 1 (5 points)
-- Student Name: Christopher McGregor
-- UIN: 726009537
-- (ACKNOWLEDGE ANY HELP RECEIVED HERE)

module Main where

import Test.HUnit
import System.Exit

-- Problem 2 (10 points)
lucas :: Int -> Int
lucas n | n == 0    = 2
        | n == 1    = 1
        | otherwise = lucas (n-1) + lucas (n-2)



-- Problem 3 (5+10 = 15 points)
qsort1 :: Ord a => [a] -> [a]
---- Question 3.1 (5 points)
qsort1 [] = []
qsort1(x:xs) = qsort1 larger ++ [x] ++ qsort1 smaller
               where
                 smaller = [a | a <- xs, a <= x]
                 larger  = [b | b <- xs, b > x]

---- Question 3.2 (10 points)
{- Write your answer for Question 3.2 within this block comment.

qsort1 [3,2,3,1,4]
looks like:                       qsort1 [1,2]             ++ [3] ++                         qsort1 [3,4]          || qsort1 is 2 times
looks like:               (qsort1 [] ++ [1] ++ qsort1 [2]) ++ [3] ++              (qsort1 [3] ++ [4] ++ qsort1 []) || qsort1 is called 4 more times
looks like: (qsort1 [] ++ [1] ++ [2] ++ qsort1 [] )        ++ [3] ++        (qsort [0] ++ [3] ++ [4] ++ qsort1 []) || qsort1 is called 4 more times
then applying ++: [1,2] ++ [3] ++ [3,4]
finally applying ++ again: [1,2,3,3,4] || qsort1 is called 10 times

-}


-- Problem 4 (Chapter 5, Exercise 9) (10+10=20 points)
scalarproduct :: [Int] -> [Int] -> Int
---- Question 4.1 (10 points)
scalarproduct xs ys = sum [(x * y) | (x,y) <- zip xs ys]

---- Question 4.2 (10 points)
{- Write your answer for Question 4.2 within this block comment.

it zips until one list is exhausted: [(1,4), (2,5), (3,6)]
then applies the multiplication of each zipped pair: 1*4, 2*5, 3*6
then applys the sum of each: 1*4 + 2*5 + 3*6
reaching the answer: 32

-}



-- Problem 5 (Chapter 6, Exercise 7) (10 points)
merge :: Ord a => [a] -> [a] -> [a]
merge xs [] = xs
merge [] ys = ys
merge (x:xs) (y:ys) = if x > y then y : merge (x:xs) ys
                      else x : merge (y:ys) xs



-- Problem 6 (Chapter 6, Exercise 8) (8+7=15 points)
halve :: [a] -> ([a], [a])  -- 7 points
halve xs = splitAt ((length xs) `div` 2) xs



msort :: Ord a => [a] -> [a]  -- 8 points
msort xs | length xs < 2 = xs
         | otherwise = merge (msort beg) (msort end)
         where beg = fst (halve xs)
               end = snd (halve xs)



-- Problem 7 (10 points)
isElem :: Eq a => a -> [a] -> Bool
isElem a (x:xs) | null xs = False
                | otherwise = if a == x then True else isElem a xs


type Set a = [a]
-- Problem 8 (15 points)
toSet :: Eq a => [a] -> Set a
toSet (x:xs) | null xs = [x] ++ xs
             | otherwise = if isElem x xs then toSet xs else (x : toSet xs)



myTestList =
  TestList [

      "lucas 1" ~: lucas 0 ~=? 2
    , "lucas 2" ~: lucas 1 ~=? 1
    , "lucas 3" ~: lucas 4 ~=? 7

    , "qsort1 1" ~: qsort1 [3, 2, 5, 1, 6] ~=? [6,5,3,2,1]
    , "qsort1 2" ~: qsort1 "howdy" ~=? "ywohd"

    , "scalarproduct 1" ~: scalarproduct [4,5,6] [1,2,3] ~=? 32
    , "scalarproduct 2" ~: scalarproduct [2,3] [1,-1] ~=? -1
    , "scalarproduct 3" ~: scalarproduct [1..10] [1..5] ~=? 55

    , "merge 1" ~: merge "EGG" "ABCDEFGH" ~=? "ABCDEEFGGGH"
    , "merge 2" ~: merge "Hello" "e" ~=? "Heello"

    , "halve 1" ~: halve "" ~=? ("","")
    , "halve 2" ~: halve "halves" ~=? ("hal","ves")
    , "halve 21" ~: halve "halve" ~=? ("ha","lve")

    , "msort 1" ~: msort "Howdy all!" ~=? " !Hadllowy"
    , "msort 2" ~: msort "" ~=? ""
    , "msort 3" ~: msort "Mississippi" ~=? "Miiiippssss"

    , "isElem 1" ~: (isElem 'h' "happy") ~=? True
    , "isElem 2" ~: (isElem 'o' "happy") ~=? False

    , "mkSet 1" ~: length (toSet "aardvark") ~=? 5
    , "mkSet 2" ~: length (toSet "Bart") ~=? 4

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
