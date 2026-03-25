(*
/* Author:         Daniel Tripoli                           */
/* Major:          Computer Science                         */
/* Creation Date:  February 14, 2026                        */
/* Due Date:       February 23, 2026                        */
/* Course: CPSC    310 010                                  */
/* Professor Name: Dr. Dylan Schwesinger                    */
/* Project:        #1                                       */
/* Filename:       student.ml                               */
/* Purpose:        Unit test our warmup.ml functions to make*/
/*                 sure they work                           */
*)

open OUnit2
open Warmup



let test_abs _ = 
  assert_equal 0 (abs 0) ~msg:"student_abs (1)";
  assert_equal 5 (abs (-5) ) ~msg:"student_abs (2)";
  assert_equal 5 (abs (5) ) ~msg:"student_abs (3)";
  assert_equal 1000 (abs (-1000) ) ~msg:"student_abs (4)"

let test_is_odd _ =
  assert_equal true (is_odd (-21)) ~msg: "student_is_odd (1)";
  assert_equal false (is_odd 100) ~msg: "student_is_odd (2)";
  assert_equal false (is_odd 0) ~msg: "student_is_odd (3)"
  
let test_divides _ = 
  assert_equal false (divides 0 0 ) ~msg: "student_divides (1)";
  assert_equal false (divides 0 15 ) ~msg: "student_divides (2)";
  assert_equal true (divides 3 36 ) ~msg: "student_divides (3)"
  
let test_area _ =
  assert_equal 4 (area ((-1), (-1)) (1, 1)) ~msg: "student_area (1)"

let test_equiv_frac _ =
  assert_equal true (equiv_frac (5, 10) (50, 100) ) ~msg: "student_equivalent_frac (1)";
  assert_equal true (equiv_frac (1, 3) (2, 6) ) ~msg: "student_equivalent_frac (2)"
 
let test_gcd _ =
  assert_equal 0 (gcd 0 0) ~msg: "student_gcd (1)";
  assert_equal 15 (gcd 0 15) ~msg: "student_gcd (2)" 

let test_ack _ =
  assert_equal 1 (ack 0 0) ~msg:"student_ack (1)";
  assert_equal 6 (ack 0 5) ~msg:"student_ack (2)";
  assert_equal 5 (ack 3 0) ~msg:"student_ack (3)"

let test_pow _ =
  assert_equal 0 (pow 0 3) ~msg:"student_pow (1)";
  assert_equal 1 (pow 3 0) ~msg:"student_pow (2)";
  assert_equal (-1) (pow (-1) 7) ~msg:"student_pow (3)"

let test_log _ =
  assert_equal 0 (log 2 1) ~msg:"student_log (1)";
  assert_equal 6 (log 2 103) ~msg:"student_log (2)"

let test_len _ =
  assert_equal 1 (len 0) ~msg:"student_len (1)";
  assert_equal 5 (len (-12349)) ~msg:"student_len (2)" (*Accounts for negative case that was not specified if it was needed or not*)

let test_get _ =
  assert_raises (Failure ("Out of bounds"))  (fun() -> get 1000 [1;2;3;4;5])~msg:"student_get (1)";
  assert_equal "f" (get 5 ["a";"b";"c";"d";"e";"f"])~msg:"student_get (2)"
 
let test_partial_sum _ = 
  assert_equal 5 (partial_sum 0 [5;6;7;3]) ~msg:"student_partial_sum (1)";
  assert_equal 5 (partial_sum 100 [1;1;1;1;1]) ~msg:"student_partial_sum (2)";
  assert_equal 0 (partial_sum 100 []) ~msg:"student_partial_sum (3)"

let test_partial_sums _ =
  assert_equal [4;10] (partial_sums [1;4] [2;2;2;2;2] ) ~msg:"student_partial_sums (1)";
  assert_equal [0;0;0] (partial_sums [0;1;100] []) ~msg:"student_partial_sums (2)"

let test_zip _ =
  assert_equal (zip [1;2;3] [4;5;6;7]) [(1,4); (2,5); (3,6)] ~msg:"student_zip (1)";
  assert_equal [(1,2)] (zip [1] [2;3]) ~msg:"student_zip (2)"


let test_merge _ =
  assert_equal [2;3] (merge [] [2;3]) ~msg:"student_merge (1)";
  assert_equal [1; 2; 2; 3; 3; 4] (merge [1; 2; 3; 4] [2; 3]) ~msg:"student_merge (2)";
  assert_equal [2;3] (merge [2;3] []) ~msg:"student_merge (3)"

let test_shift_left _ = 
  assert_equal [] (shift_left 2 [])~msg: "student_shift_left (1)";
  assert_equal ["a"; "b"; "c"; "d"] (shift_left 0 ["a"; "b"; "c"; "d"]) ~msg: "student_shift_left (2)";
  assert_equal ["b"; "c"; "d"; "a"] (shift_left 1 ["a"; "b"; "c"; "d"]) ~msg: "student_shift_left (3)";
  assert_equal ["c"; "d"; "a"; "b"] (shift_left 2 ["a"; "b"; "c"; "d"]) ~msg: "student_shift_left (4)"; 
  assert_equal ["d"; "a"; "b"; "c"] (shift_left 3 ["a"; "b"; "c"; "d"]) ~msg: "student_shift_left (5)"; 
  assert_equal ["a"; "b"; "c"; "d"] (shift_left 4 ["a"; "b"; "c"; "d"]) ~msg: "student_shift_left (6)"; 
  assert_equal ["b"; "c"; "d"; "a"] (shift_left 5 ["a"; "b"; "c"; "d"]) ~msg: "student_shift_left (7)";
  assert_equal ["b"] (shift_left 5 ["b"]) ~msg: "student_shift_left (8)"  

let suite =
  "studentTests" >::: [
    "student_abs" >:: test_abs;
    "student_is_odd" >:: test_is_odd;
    "student_divides" >:: test_divides;
    "student_area" >:: test_area;
    "student_equiv_frac" >:: test_equiv_frac;
    "student_gcd" >:: test_gcd; 
    "student_ack" >:: test_ack; 
    "student_pow" >:: test_pow;
    "student_log" >:: test_log;
    "student_len" >:: test_len;
    "student_get" >:: test_get;
    "student_partial_sum" >:: test_partial_sum;
    "student_partial_sums" >:: test_partial_sums;
    "student_zip" >:: test_zip; 
    "student_merge" >:: test_merge;
    "student_shift_left" >:: test_shift_left
  ]

let _ = run_test_tt_main suite
