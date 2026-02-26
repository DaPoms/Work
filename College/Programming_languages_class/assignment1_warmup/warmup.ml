(* CSC 310, Spring 2021 *)

(****************************************************************************)
(* Part 1: Non-Recursive Functions *)
(****************************************************************************)

(* Implement the following functions that do not require recursion.
You may add the rec keyword to any of the following functions or write a
recursive helper function. Just remember that if you write a helper function,
it must be defined in the file before it is called. *)

(*
Type: int -> int

Description: Returns the absolute value of x.

Examples:
    abs 1 = 1
    abs (-5) = 5
*)

let abs x = if x < 0 then -x else x

(*
Type: int -> bool

Description: Returns whether or not x is odd.

Examples:
  is_odd 1 = true
  is_odd 4 = false
  is_odd (-5) = true
*)

let is_odd x = if  not(x mod 2 = 0) then true else false 

(*
Type: int -> int -> bool

Description: Returns true iff x divides y. Formally, x | y iff x ≠ 0 and there
exists integer k such that y = xk.

Examples:
    divides 10 5 = false 
    divides 10 20 = true
    divides 10 10 = true
    divides 10 0 = true
    divides 0 15 = false
    divides 0 0 = false
*)

let divides x y = if not(x = 0) && (y mod x = 0) then true else false
(*This is an alternate goofy version I made of the right && expression, ignore it: ( (float) y /. (float) x = (float)(y / x) ) *)

(*
Type: int * int -> int * int -> int

Description: Takes in the Cartesian coordinates (2-dimensional) of any pair of
opposite corners of a rectangle and returns the area of the rectangle. The
sides of the rectangle are parallel to the axes.

Examples:
  area (1, 1) (2, 2) = 1
  area (2, 2) (1, 1) = 1
  area (2, 1) (1, 2) = 1
  area (0, 1) (2, 3) = 4
  area (1, 1) (1, 1) = 0
  area ((-1), (-1)) (1, 1) = 4
*)

(*helper function for area:*)
let subPair (first1, second1) (first2, second2) = (first1 - first2, second1 - second2)

let area x y = 
  let first, second = subPair x y in abs(first) * abs(second)
  
 (* match ans with
  | (first, second) -> abs(first) * abs(second) *)
  
(*
Type: (int * int) -> (int * int) -> bool

Description: Takes in two fractions in the form of 2-tuples, a/b and c/d, and
returns whether or not the two fractions are equivalent. In the case of
division by 0, false should be returned. The optimal solution does not
require recursion, but you may add rec keyword or define your own recursive
helper function if you would like.

Examples:
    equiv_frac (1, 2) (2, 4) = true
    equiv_frac (2, 4) (1, 2) = true
    equiv_frac (1, 2) (1, 2) = true
    equiv_frac (3, 12) (2, 6) = false
    equiv_frac (1, 2) (3, 4) = false
    equiv_frac (1, 0) (2, 0) = false
*)
let equiv_frac (a, b) (c, d) = if (b != 0 && d != 0) && ( (float) a /. (float) b = (float) c /. (float) d) then true else false

(****************************************************************************)
(* Part 2: Recursive Functions *)
(****************************************************************************)
(* Implement the following functions with recursion *)

(*
Type: int -> int -> int

Description: Returns the greatest common divisor of a and b. Utilize the
recursive Euclidean Algorithm to accomplish this:
https://en.wikipedia.org/wiki/Euclidean_algorithm

Examples:
    gcd 8 12 = 4
    gcd 54 24 = 6
    gcd 10 0 = 10
    gcd 0 10 = 10
    gcd 0 0 = 0 
*)

let subLeftByRight x y =  (* this is made to ensure immutability of the above function*)
  if x > y then 
    x - y
  else
    y - x

let rec gcd a b =
  if a = b then (* base case *)
    a
  else if a > b then
    gcd (subLeftByRight a b) b
  else
    gcd (subLeftByRight b a) a
  
(*
Type: int -> int -> int

Description: Returns the value of the Ackermann–Péter function for m and n:
https://en.wikipedia.org/wiki/Ackermann_function

Examples:
  ack 0 0 = 1
  ack 0 5 = 6
  ack 3 0 = 5
  ack 3 3 = 61
*)
let rec ack m n = (* failwith "unimplimented" *)
  match (m,n) with
  | (0,n) -> n + 1
  | (m,0) -> ack (m-1) 1
  | (m,n) -> ack (m-1) (ack m (n-1)) 

(*
Type: int -> int -> int

Description: Returns x raised to the power y.

Assumptions: y is non-negative, your code will not be tested for integer
overflow cases.

Examples:
  pow 3 1 = 3
  pow 3 2 = 9
  pow (-3) 3 = -27
*)
let rec pow x y =
  if y = 0 then
    1
  else
    x * (pow x (y - 1))

(*
Type: int -> int -> int

Description: Returns the log of y with base x rounded-down to an integer.

Assumptions: You may assume the answer is non-negative, x >= 2, and y >= 1.

Examples:
  log 4 4 = 1
  log 4 16 = 2
  log 4 15 = 1
  log 4 64 = 3
*)
let rec log x y =
  match y with
  | 0 -> -1 (* if the log doesn't work out to a whole number, it will ALWAYS return 0 at the end as we are using operator/ (int) not operator/. (float), so we return -1 to take away the turn that just made the base higher than the value of what we are doing the log of. EX: for log4(14), at 2, 14/16 < 1 *)
  | 1 -> 0
  | _ -> 1 + log x (y/x)
  
(*   This was my original approach before the idea came to me to use match case
  if(y < 1) then (* the "<" part makes sure we round down when the log doesn't lead naturally to a whole number*)
    -1
  else if (y = 1) then
    0 
  else
    1 + (log x (y/x))  
*)
    
    (*Because we cannot do power of x due to only having 2 parameters (we would need a parameter to track what power we are on), instead of doing x^n till its >= y, we can do y/x till y <= 1 *)
    (* This works because log is basically stating (like for example) log4(16): 4 to what power gives you 16? That means if we divide by 16 2 times and get 1, that 4^2 gave us 16 as 16/16 = 1 *)
                       

    

  
  


(*
Type: int -> int

Description: Returns the number of numerical digits in x.

Examples:
    len 1 = 1
    len 10 = 2
    len 15949 = 5
*) (*I personally would've just used log base 10 to find this but this has to be recursion :C*)
let rec len x = 
  if(x < 10) then (*we need to do this to account for len 0 should = 1 but also to not discount a single digit that isnt 0*)
    1 (*One's digit is already accounted for at the end, so 0 does not count towards the digit count*)
  else
    1 + len(x/10)

(****************************************************************************)
(* Part 3: Lists *)
(****************************************************************************)

(*
Type: int -> 'a list -> 'a

Description: Returns the element at the index idx in the list lst. If idx is
past the bounds of lst, raise an error using failwith "Out of bounds".

Assumptions: idx is non-negative.

Examples:
  get 0 [26; 11; 99] = 26
  get 1 [26; 11; 99] = 11
  get 2 [26; 11; 99] = 99
  get 3 [26; 11; 99] = Exception
  get 0 ["a"; "b"] = "a"
  get 1 ["a"; "b"] = "b"
  get 2 ["a"; "b"] = Exception
*)
let rec get idx lst =  
  match lst with
  | (x::xs) -> 
    if idx = 0 then
      x
    else
      get (idx - 1) xs
  | [] -> failwith "Out of bounds"
(*
Type: int -> int list -> int

Description: Returns the sum of the values from index 0 to index idx
(0-indexed) of lst inclusive. If idx is greater than greatest index of lst,
return the sum of all elements of lst. You may assume idx is non-negative, and
your implementation does not have to consider this case.

Examples:
    partial_sum 0 [5;6;7;3] = 5
    partial_sum 1 [5;6;7;3] = 11
    partial_sum 4 [5;6;7;3] = 21
    partial_sum 2 [] = 0
*)
let rec partial_sum idx lst = 
    match lst with
    | (x::xs) -> 
        if idx = 0 then 
          x
        else
          x + partial_sum (idx - 1) xs
    | [] -> 0

(*
Type: int list -> int list -> int list

Description: Returns a list where the values correspond to the partial sums
from 0 to each index of lst listed in xs. Follows the same rules as partial_sum
for special cases.

Examples:
    partial_sums [0;1] [5;6;7;3] = [5;11] 
    partial_sums [1;4] [5;6;7;3] = [11;21]
    partial_sums [] [5;6;7;3] = []
    partial_sums [0;1] [] = [0;0]
*)
let rec partial_sums xs lst = 
  match xs with
  | (h::t) -> partial_sum h lst :: partial_sums t lst
  | [] -> []

(*
Type: 'a list -> 'b list -> ('a * 'b) list

Description: Given two lists, returns list of pairs where elements at the same
index are paired up in the same order. If one of the lists runs out of
elements, then do not construct any more pairs.

Examples:
    zip [1;3] [2;4] = [(1,2);(3,4)] 
    zip [1;3] [2;4;5] = [(1,2);(3,4)] 
    zip [] [5;4;3] = []
    zip [] [] = []
*)
let rec zip lst1 lst2 =
  
  match (lst1, lst2) with
  | ([],_) -> []
  | (_,[]) -> []
  | (x::xs,h::t) -> (x,h) :: (zip xs t)
  
 (*   My more fun nested approach of the zip function (looks ugly though), can also use begin and end specifiers
  match lst1 with
  | (x::xs) ->
      (match lst2 with
      | (h::t) -> (x,h) :: zip xs t
      | [] -> [])
  | [] -> []  *)




(*
Type: 'a list -> 'a list -> 'a list

Description: Merge two sorted lists, lst1 and lst2, and return the result as a
sorted list.

Examples:
  merge [1] [2] = [1;2]
  merge [] [] = []
  merge [1; 4] [2; 3] = [1; 2; 3; 4]
  merge [1] [0] = [0; 1]
*)


let rec merge lst1 lst2 = (*elements might not be the same size*)

  match (lst1,lst2) with
  | (lst,[]) -> lst (*since we know the other lst does not have any more elements, we can just use the remaining values as the base case. Note that even ([],[]) evaluates to the match (lst, []) as lst essentially just references the entirety of the list1 in the variable lst*)
  | ([], lst) -> lst 
  | (x::xs, h::t) -> 
      if x > h then
        h :: x :: merge xs t (*due to the nature of a linked list, the right most element added will be a higher index then the leftmost (ex: 1 :: 2 :: [] is stored as [1;2])*)
      else
        x :: h :: merge xs t

(*
This is a BONUS problem.

Type: int -> 'a list -> 'a list

Description: Move every element over in lst to the left by the given shift
(looping around).

Assumptions: shift is non-negative.

Note: There are no tests for this function; write your own tests to
verify that your behavior is what you would expect.

Examples:
  shift_left 0 ["a"; "b"; "c"; "d"] = ["a"; "b"; "c"; "d"]
  shift_left 1 ["a"; "b"; "c"; "d"] = ["b"; "c"; "d"; "a"]
  shift_left 2 ["a"; "b"; "c"; "d"] = ["c"; "d"; "a"; "b"]
  shift_left 3 ["a"; "b"; "c"; "d"] = ["d"; "a"; "b"; "c"]
  shift_left 4 ["a"; "b"; "c"; "d"] = ["a"; "b"; "c"; "d"]
  shift_left 5 ["a"; "b"; "c"; "d"] = ["b"; "c"; "d"; "a"]
*)


 let rec shift_left shift lst = 
  match (shift,lst) with
  | (_,[]) -> []
  | (_,[x]) -> [x] (* only benefit of this is it removes a shift count of necessary recursive call operations for 1 element linked lists.*)
  | (0,lst) -> lst
  | (_,x::xs) -> shift_left (shift - 1) (xs @ [x]) (*adds element to the back of the list as shifting left is effectively just putting leftmost value to the back as it shifts everything else left *)

(* Just for fun, this is the function I made to (when used properly with 2 reverse calls + cons operator (::)) to replicate the behavior of @ (append operator). To be fair I also didnt read the instructions that we could use anything in stdlib so I ended up with this, so this is just a relic of my mistake
let rec reverse lst =
  let rec aux acc restLst = 
    match restLst with
    | [] -> acc
    | x :: xs -> aux (x :: acc) xs (*Here we add to our answer list in the order that the linked list is traversed. Due to the nature of linked lists, it properly reverses it as we are storing from the head to the tail*)
  in
  aux [] lst
*)

(* Just another function I made for quick code testing (without unit tests), ignore
let rec printLst lst = 
  match lst with 
  | (x::xs) -> print_string (x ^ " ");
    printLst xs
  | [] -> print_string ""
*)


