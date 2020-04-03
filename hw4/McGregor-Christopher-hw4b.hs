
-- CSCE 314 [Section 501] Programming Languages Spring 2020
-- Homework Assignment 4B Monadic Parsing
-- Due by 10:00 p.m. on Monday, March 23

-- Problem 1 (4 points)
-- Student Name: Christopher McGregor
-- UIN: 726009537
-- (ACKNOWLEDGE ANY HELP RECEIVED HERE)


module Parsing (module Parsing, module Control.Applicative) where

import Control.Applicative
import Data.Char

-- Basic definitions

newtype Parser a = P (String -> [(a,String)])

parse :: Parser a -> String -> [(a,String)]
parse (P p) inp = p inp

item :: Parser Char
item = P (\inp -> case inp of
                     []     -> []
                     (x:xs) -> [(x,xs)])

-- Sequencing parsers

instance Functor Parser where
   -- fmap :: (a -> b) -> Parser a -> Parser b
   fmap g p = P (\inp -> case parse p inp of
                            []        -> []
                            [(v,out)] -> [(g v, out)])

instance Applicative Parser where
   -- pure :: a -> Parser a
   pure v = P (\inp -> [(v,inp)])

   -- <*> :: Parser (a -> b) -> Parser a -> Parser b
   pg <*> px = P (\inp -> case parse pg inp of
                             []        -> []
                             [(g,out)] -> parse (fmap g px) out)

instance Monad Parser where
   -- (>>=) :: Parser a -> (a -> Parser b) -> Parser b
   p >>= f = P (\inp -> case parse p inp of
                           []        -> []
                           [(v,out)] -> parse (f v) out)

-- Making choices

instance Alternative Parser where
   -- empty :: Parser a
   empty = P (\inp -> [])

   -- (<|>) :: Parser a -> Parser a -> Parser a
   p <|> q = P (\inp -> case parse p inp of
                           []        -> parse q inp
                           [(v,out)] -> [(v,out)])

-- Derived primitives

sat :: (Char -> Bool) -> Parser Char
sat p = do x <- item
           if p x then return x else empty

digit :: Parser Char
digit = sat isDigit

lower :: Parser Char
lower = sat isLower

upper :: Parser Char
upper = sat isUpper

letter :: Parser Char
letter = sat isAlpha

alphanum :: Parser Char
alphanum = sat isAlphaNum

char :: Char -> Parser Char
char x = sat (== x)

string :: String -> Parser String
string []     = return []
string (x:xs) = do char x
                   string xs
                   return (x:xs)

ident :: Parser String
ident = do x  <- lower
           xs <- many alphanum
           return (x:xs)

nat :: Parser Int
nat = do xs <- some digit
         return (read xs)

int :: Parser Int
int = do char '-'
         n <- nat
         return (-n)
       <|> nat

-- Handling spacing

space :: Parser ()
space = do many (sat isSpace)
           return ()

token :: Parser a -> Parser a
token p = do space
             v <- p
             space
             return v

identifier :: Parser String
identifier = token ident

natural :: Parser Int
natural = token nat

integer :: Parser Int
integer = token int

symbol :: String -> Parser String
symbol xs = token (string xs)


-- Problem 2.1 (13 points) Explain the step-by-step working of
-- > parse expr "2*(3+4)"
-- resulting in
-- [(14,"")]
-- using the definitions of expr, term and factor given in section 13.8.
{- Write your explanation here

                 expr
                  |
                 term
              /   |   \
         factor   *  factor
          |          |
        nat         expr
         |        /  |  \
         2    term  +  expr
                   |        |
               factor     term
                  |         |
                 nat      factor
                  |         |
                  3        nat
                            |
                            4

parse expr "2*(3+4)"                          applying expr becomes
parse term "2*(3+4)"                          applying term becomes
parse factor "2 *" parse term "(3+4)"         applying factor becomes
parse nat "2 *" parse term "(3+4)"            applying parse becomes
2 * parse term "(3+4)"                        applying term becomes
2 * parse factor "(3+4)"                      applying factor becomes
2 * parse expr "3+4"                          applying expr becomes
2 * (parse term "3" + parse expr "4")         applying term becomes
2 * (parse factor "3" + parse expr "4")       applying factor becomes
2 * (parse nat "3" + parse expr "4")          applying parse becomes
2 * (3 + parse expr "4")                      applying expr becomes
2 * (3 + parse term "4")                      applying term becomes
2 * (3 + parse factor "4")                    applying factor becomes
2 * (3 + parse nat "4")                       applying parse becomes
2 * (3 + 4)
14
[(14,"")]

-}

-- Problem 2.2 (13 points) Explain the step-by-step working of
-- > parse expr "1+2*3"
-- resulting in
-- [(7,"")]
-- using the definitions of expr, term and factor given in section 13.8.
{- Write your explanation here

                expr
             /   |   \
         term   +  expr
          |       /  |  \
      factor    term  *  expr
         |        |         |
        nat      factor    term
         |        |         |
         1       nat       facrot
                  |         |
                  2         nat
                            |
                            3

parse expr "1+2*3"                      applying expr becomes
parse term "1" + parse expr "2*3"       applying term becomes
parse factor "1" + parse expr "2*3"     applying factor becomes
parse nat "1" + parse expr "2*3"        applying parse becomes
1 + parse expr "2*3"                    applying expr becomes
1 + (parse term "2" * parse expr "3")   applying term becomes
1 + (parse factor "2" * parse expr "3") applying factor becomes
1 + (parse nat "2" * parse expr "3")    applying parse becomes
1 + (2 * parse expr "3")                applying expr becomes
1 + (2 * parse term "3")                applying term becomes
1 + (2 * parse factor "3")              applying factor becomes
1 + (2 * parse nat "3")                 applying parse becomes
1 + (2 * 3)
7
[(7,"")]

-}

-- Problem 3 (30 points) Parser for Expr

data Expr = Val Int | Add Expr Expr | Mul Expr Expr  deriving Show

expr :: Parser Expr  -- 10 points
expr = do
  t <- term
  do
    symbol "+"
    e <- expr
    return (Add t e)
    <|> return t


term :: Parser Expr  -- 10 points
term = do
  f <- factor
  do
    symbol "*"
    t <- term
    return (Mul f t)
    <|> return f


factor :: Parser Expr  -- 10 points
factor = do
  f <- integer
  return (Val f)
  <|> do
    symbol "("
    e <- expr
    symbol ")"
    return e


-- Examples that you can use to test your definitions for expr, term and factor
e1 = "2*(3+4)"
-- > parse expr e1
-- should result in
-- [(Mul (Val 2) (Add (Val 3) (Val 4)),"")]

e2 = "1+2*3"
-- > parse expr e2
-- should result in
-- [(Add (Val 1) (Mul (Val 2) (Val 3)),"")]

-- Feel free to add more expressions for your test
