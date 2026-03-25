open OUnit2
open Warmup

let test_abs _ =
  assert_equal 1 (abs 1) ~msg:"abs (1)";
  assert_equal 1 (abs (-1)) ~msg:"abs (2)";
  assert_equal 13 (abs 13) ~msg:"abs (3)";
  assert_equal 13 (abs (-13)) ~msg:"abs (4)"

let test_is_odd _ =
  assert_equal true (is_odd 1) ~msg:"is_odd (1)";
  assert_equal true (is_odd (-1)) ~msg:"is_odd (2)";
  assert_equal false (is_odd 12) ~msg:"is_odd (3)";
  assert_equal false (is_odd 0) ~msg:"is_odd (4)"

let test_divides _ = 
  assert_equal true (divides 5 10) ~msg:"divides (1)";
  assert_equal false (divides 3 7) ~msg:"divides (2)";
  assert_equal false (divides 10 5) ~msg:"divides (3)"

let test_area _ =
  assert_equal 1 (area (1, 1) (2, 2)) ~msg:"area (1)";
  assert_equal 2 (area (1, 1) (2, 3)) ~msg:"area (2)";
  assert_equal 2 (area (1, 1) (3, 2)) ~msg:"area (3)";
  assert_equal 4 (area (1, 1) (3, 3)) ~msg:"area (4)"

let test_equiv_frac _ =
  assert_equal true (equiv_frac (1, 2) (2, 4)) ~msg:"equiv_frac (1)";
  assert_equal true (equiv_frac (2, 4) (1, 2)) ~msg:"equiv_frac (2)";
  assert_equal true (equiv_frac (1, 2) (1, 2)) ~msg:"equiv_frac (3)";
  assert_equal true (equiv_frac (3, 6) (2, 4)) ~msg:"equiv_frac (4)";
  assert_equal false (equiv_frac (1, 3) (2, 5)) ~msg:"equiv_frac (5)";
  assert_equal false (equiv_frac (10, 30) (4, 6)) ~msg:"equiv_frac (6)";
  assert_equal false (equiv_frac (999999999, 1000000000) (999999998, 1000000000)) ~msg:"equiv_frac(7)"

let test_gcd _ =
  assert_equal 4 (gcd 8 12);
  assert_equal 6 (gcd 54 24);
  assert_equal 10 (gcd 110 200);
  assert_equal 2 (gcd 4 6)

let test_ack _ =
  assert_equal 61 (ack 3 3);
  assert_equal 4 (ack 1 2);
  assert_equal 7 (ack 2 2)

let test_pow _ =
  assert_equal 2 (pow 2 1) ~msg:"pow (1)";
  assert_equal 4 (pow 2 2) ~msg:"pow (2)";
  assert_equal 3 (pow 3 1) ~msg:"pow (3)";
  assert_equal 27 (pow 3 3) ~msg:"pow (4)";
  assert_equal 625 (pow 5 4) ~msg:"pow (5)";
  assert_equal (-27) (pow (-3) 3) ~msg:"pow (6)"

let test_log _ =
  assert_equal 1 (log 4 4) ~msg:"log (1)";
  assert_equal 2 (log 4 16) ~msg:"log (2)";
  assert_equal 1 (log 4 15) ~msg:"log (3)";
  assert_equal 3 (log 4 64) ~msg:"log (4)"

let test_len _ =
  assert_equal 1 (len 4) ~msg:"len (1)";
  assert_equal 3 (len 330) ~msg:"len (2)";
  assert_equal 4 (len 1000) ~msg:"len (3) ";
  assert_equal 6 (len 100000) ~msg:"len (4)"

let test_get _ =
  assert_equal 26 (get 0 [26; 11; 99]) ~msg:"get (1)";
  assert_equal 11 (get 1 [26; 11; 99]) ~msg:"get (2)";
  assert_equal 99 (get 2 [26; 11; 99]) ~msg:"get (3)";
  assert_raises (Failure ("Out of bounds")) (fun () -> get 3 [26; 11; 99]) ~msg:"get (4)"

let test_partial_sum _ =
  assert_equal 11 (partial_sum 1 [5;6;7;3]) ~msg:"partial_sum (1)";
  assert_equal 21 (partial_sum 3 [5;6;7;3]) ~msg:"partial_sum (2)"

let test_partial_sums _ =
  assert_equal [18;5] (partial_sums [2;0] [5;6;7;3]) ~msg:"partial_sums (1)";
  assert_equal [18;21] (partial_sums [2;3] [5;6;7;3]) ~msg:"partial_sums (2)"

let test_zip _ =
  assert_equal (zip [1;3] [2;4]) [(1,2); (3,4)] ~msg:"zip (1)";
  assert_equal (zip [1;3] [2]) [(1,2)] ~msg:"zip (2)";
  assert_equal (zip [] []) [] ~msg:"zip (3)"

let test_merge _ =
  assert_equal [1; 2] (merge [1] [2]) ~msg:"merge (1)";
  assert_equal [] (merge [] []) ~msg:"merge (2)";
  assert_equal [1; 2; 3; 4] (merge [1; 4] [2; 3]) ~msg:"merge (3)";
  assert_equal [0; 1] (merge [1] [0]) ~msg:"merge (4)"


let suite =
  "public" >::: [
    "abs" >:: test_abs;
    "is_odd" >:: test_is_odd;
    "divides" >:: test_divides;
    "area" >:: test_area;
    "equiv_frac" >:: test_equiv_frac;
    "gcd" >:: test_gcd; 
    "ack" >:: test_ack; 
    "pow" >:: test_pow;
    "log" >:: test_log;
    "len" >:: test_len;
    "get" >:: test_get;
    "partial_sum" >:: test_partial_sum;
    "partial_sums" >:: test_partial_sums;
    "zip" >:: test_zip; 
    "merge" >:: test_merge
  ]

let _ = run_test_tt_main suite
