
-- CSCE 314 [Section 501] Programming Languages Spring 2020
-- Homework Assignment 2

-- Problem 1 (5 points)
-- This is head comment (single line comment should be preceded by two dashes)
-- Student Name: Christopher McGregor
-- UIN: 726009537
-- (ACKNOWLEDGE ANY HELP RECEIVED HERE)

module Main where

import Prelude hiding ((&&))

import Test.HUnit
import System.Exit
import Data.Char


-- Problem 2 (5 points) Chapter 4, Exercise 5
(&&) :: Bool -> Bool -> Bool
(&&) x y = if x then (if y then True else False) else False


-- Problem 3 (10+10 = 20 points) Chapter 4, Exercise 8
luhnDouble :: Int -> Int  -- 10 points
luhnDouble x | (2*x) > 9 = 2*x - 9
             | otherwise = 2*x

luhn :: Int -> Int -> Int -> Int -> Bool  -- 10 points
luhn x y z w = if ((luhnDouble x + luhnDouble z + y + w) `mod` 10 == 0) then True else False


-- Problem 4 (10 points) Chapter 5, Exercise 6
factors :: Int -> [Int]
factors n = [x | x <- [1..n], n `mod` x == 0]

perfects :: Int -> [Int]
perfects n = [x | x <- [1..n], (sum(factors x) - x) == x]



-- Problem 5 (7+7+6 = 20 points) Chapter 6, Exercise 5
{- Write your answer in this block comment neatly and clearly.

1. length [1,2,3]
= {applying length}
  1 + length [2,3]
= {applying length}
  1 + (1 + length [3])
= {applying length}
  1 + (1 + (1 + length []))
= {applying length base case}
  1 + (1 + (1 + 0))
= {applying +}
  4

2. drop 3 [1,2,3,4,5]
= {applying drop}
  drop 2 [2,3,4,5]
= {applying drop}
  drop 1 [3,4,5]
= {applying drop}
  drop 0 [4,5]
= {applying drop base case}
  [4,5]

3. init [1,2,3]
= {applying init}
  1 : init [2,3]
= {applying init}
  1 : 2 : init [3]
= {applying init base case}
  1 : 2 : []
= {applying list}
  [1,2]

-}



-- Problem 6 (8+7=15 points)
halve :: [a] -> ([a], [a])
halve xs = splitAt ((length xs) `div` 2) xs

mergeBy :: (a -> a -> Bool) -> [a] -> [a] -> [a]  -- 8 points
mergeBy p xs [] = xs
mergeBy p [] ys = ys
mergeBy p (x:xs) (y:ys) = if (p x y) then x : mergeBy p xs (y:ys)
                          else y : mergeBy p (x:xs) ys


msortBy :: (a -> a -> Bool) -> [a] -> [a]  -- 7 points
msortBy p xs | length xs < 2 = xs
             | otherwise = mergeBy p (msortBy p beg) (msortBy p end)
              where beg = fst (halve xs)
                    end = snd (halve xs)


-- Problem 7 (10+5 = 15 points) Chapter 7, Exercise 9
altMap :: (a -> b) -> (a -> b) -> [a] -> [b]  -- 10 points
altMap f g (x:y:xs) = if length xs < 2 then f x : g y : map f xs
                      else f x : g y : altMap f g xs

{- (5 points)
   Explain how your altMap works when it is applied as below.
   > altMap (*2) (`div` 2) [0..6]
   = {applying altmap using else}
    [(*2) 0, (`div` 2) 1, altmap (*2) (`div` 2) [2,3,4,5,6]]
   = {applying altmap using else}
    [(*2) 0, (`div` 2) 1, (*2) 2, (`div` 1) 3, altmap (*2) (`div` 2) [4,5,6]]
   = {applying altmap using if}
    [(*2) 0, (`div` 2) 1, (*2) 2, (`div` 1) 3, (*2) 4, (`div` 2) 5, map (*2) [6]]
   = {applying (*2), (`div` 2) and map}
    [0, 0, 4, 1, 8, 2, 12]

-}


-- Problem 8 (10 points)
concatenateAndUpcaseOddLengthStrings :: [String] -> String
concatenateAndUpcaseOddLengthStrings xs = foldr (++) "" (map(map toUpper) ys)
                                         where ys = filter (odd . length) xs



myTestList =
  TestList [

      "&& 1" ~: (&&) True True ~=? True
    , "&& 2" ~: (&&) True False ~=? False
    , "&& 3" ~: (&&) False True ~=? False
    , "&& 4" ~: (&&) False False ~=? False

    , "luhnDouble 1" ~: luhnDouble 3 ~=? 6
    , "luhnDouble 2" ~: luhnDouble 6 ~=? 3
    , "luhnDouble 3" ~: luhnDouble 5 ~=? 1

    , "luhn 1" ~: luhn 1 7 8 4 ~=? True
    , "luhn 2" ~: luhn 4 7 8 3 ~=? False

    , "perfects 1" ~: perfects 500 ~=? [6,28,496]

    , "mergeBy 1" ~: mergeBy (>) "FED" "GBA" ~=? "GFEDBA"
    , "mergeBy 2" ~: mergeBy (<) "Howdy" "Maui" ~=? "HMaouiwdy"

    , "msortBy 1" ~: msortBy (<) "gig 'em" ~=? " 'eggim"
    , "msortBy 2" ~: msortBy (>) "Jack be nimble" ~=? "nmlkieecbbaJ  "
    , "msortBy 3" ~: msortBy (<) "" ~=? ""

    , "altMap 1" ~: altMap (* 10) (* 100) [1,2,3,4,5] ~=? [10,200,30,400,50]
    , "altMap 2" ~: and (altMap even odd [1..10]) ~=? False
    , "altMap 3" ~: altMap toLower toUpper "Haskell IS fun!" ~=? "hAsKeLl iS FuN!"

    , "concatenateAndUpcaseOddLengthStrings" ~:
         concatenateAndUpcaseOddLengthStrings ["here's ", "an ", "a ", "example"] ~=? "HERE'S AN EXAMPLE"

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
