open OUnit2
open Project2.Hof
open Project2.Tree


let test_len _ =
  let a = [0.1; 0.2; 0.3] in
  let b = ["a"; "b"; "b"; "c"] in
  let c = [1;2;3;4;5;6;7;8;9] in
  let d = [] in
  assert_equal 3 (len a) ~msg:"len (1)";
  assert_equal 4 (len b) ~msg:"len (2)";
  assert_equal 9 (len c) ~msg:"len (3)";
  assert_equal 0 (len d) ~msg:"len (4)"


let test_elem_count _ =
  let a = [1;2;3;4;5;6;7;8;9] in
  let b = ["a"; "a"; "b"; "a"] in
  let c = [true; false; false; true; false; false] in
  let d = [] in
  assert_equal 1 (elem_count a 3) ~msg:"elem_count (1)";
  assert_equal 1 (elem_count b "b") ~msg:"elem_count (2)";
  assert_equal 3 (elem_count b "a") ~msg:"elem_count (3)";
  assert_equal 4 (elem_count c false) ~msg:"elem_count (4)";
  assert_equal 0 (elem_count d 1) ~msg:"elem_count (5)"


let test_uniq _ =
  let a = ["a"; "a"; "b"; "a"] in
  let b = [1;3;3;1;2;5;3;3] in
  let c = [true; false; false; true; false; false] in
  let d = [] in
  let cmp x y = if x < y then (-1) else if x = y then 0 else 1 in
  assert_equal ["a"; "b"] (List.sort cmp (uniq a)) ~msg:"uniq (1)";
  assert_equal [1; 2; 3; 5] (List.sort cmp (uniq b)) ~msg:"uniq (2)";
  assert_equal [false; true] (List.sort cmp (uniq c)) ~msg:"uniq (3)";
  assert_equal [] (List.sort cmp (uniq d)) ~msg:"uniq (4)"


let test_occurrence_list _ =
  let a = ["a"; "a"; "b"; "a"] in
  let b = [1;3;3;1;2;5;3;3] in
  let c = [true; false; false; true; false; false] in
  let d = [] in
  let cmp x y = if x < y then (-1) else if x = y then 0 else 1 in
  assert_equal [("a",3);("b",1)] (List.sort cmp (occurrence_list a)) ~msg:"occurrence_list(1)";
  assert_equal [(1,2);(2,1);(3,4);(5,1)] (List.sort cmp (occurrence_list b)) ~msg:"occurrence_list(2)";
  assert_equal [(false,4);(true,2)] (List.sort cmp (occurrence_list c)) ~msg:"occurrence_list(3)";
  assert_equal [] (occurrence_list d) ~msg:"occurrence_list(4)"


let test_bind _ =
  let x = [5;6;7;3] in
  let y = [5;6;7] in
  let z = [7;5] in
  let a = [3;5;8;10;9] in
  let b = [3] in
  let c = [] in
  let f1 = (fun x -> [x-1; x+1]) in
  let f2 = (fun x -> [x * 2]) in
  assert_equal [4;6;5;7;6;8;2;4] (bind f1 x) ~msg:"bind (1)";
  assert_equal [4;6;5;7;6;8] (bind f1 y) ~msg:"bind (2)";
  assert_equal [6;8;4;6] (bind f1 z) ~msg:"bind (3)";
  assert_equal [2;4;4;6;7;9;9;11;8;10] (bind f1 a) ~msg:"bind (4)";
  assert_equal [2;4] (bind f1 b) ~msg:"bind (5)";
  assert_equal [] (bind f1 c) ~msg:"bind (6)";
  assert_equal (List.map (( * ) 2) x) (bind f2 x) ~msg:"bind (7)";
  assert_equal (List.map (( * ) 2) y) (bind f2 y) ~msg:"bind (8)";
  assert_equal (List.map (( * ) 2) z) (bind f2 z) ~msg:"bind (9)";
  assert_equal (List.map (( * ) 2) a) (bind f2 a) ~msg:"bind (10)";
  assert_equal (List.map (( * ) 2) b) (bind f2 b) ~msg:"bind (11)";
  assert_equal (List.map (( * ) 2) c) (bind f2 c) ~msg:"bind (12)"


let test_ap _ =
  let x = [5;6;7;3] in
  let y = [5;6;7] in
  let z = [7;5] in
  let a = [3;5;8;10;9] in
  let b = [3] in
  let c = [] in
  let fs1 = [((+) 2) ; (( * ) 7)] in
  let fs2 = [pred] in
  assert_equal [7;8;9;5;35;42;49;21] (ap fs1 x) ~msg:"ap (1)";
  assert_equal [7;8;9;35;42;49] (ap fs1 y) ~msg:"ap (2)";
  assert_equal [9;7;49;35] (ap fs1 z) ~msg:"ap (3)";
  assert_equal [5;7;10;12;11;21;35;56;70;63] (ap fs1 a) ~msg:"ap (4)";
  assert_equal [5;21] (ap fs1 b) ~msg:"ap (5)";
  assert_equal [] (ap fs1 c) ~msg:"ap (6)";
  assert_equal (List.map pred x) (ap fs2 x) ~msg:"ap (7)";
  assert_equal (List.map pred y) (ap fs2 y) ~msg:"ap (8)";
  assert_equal (List.map pred z) (ap fs2 z) ~msg:"ap (9)";
  assert_equal (List.map pred a) (ap fs2 a) ~msg:"ap (10)";
  assert_equal (List.map pred b) (ap fs2 b) ~msg:"ap (11)";
  assert_equal (List.map pred c) (ap fs2 c) ~msg:"ap (12)"


let test_tree_mem _ =
  let t1 = tree_insert 20 (tree_insert 10 empty_tree) in
  let t2 = tree_insert 9 (tree_insert 5 t1) in
  let t3 = tree_insert 15 (tree_insert 13 t2) in
  let t4 = tree_insert 29 (tree_insert 21 t3) in
  assert_equal true (tree_mem 10 t4) ~msg:"tree_mem (1)";
  assert_equal true (tree_mem 15 t4) ~msg:"tree_mem (2)";
  assert_equal true (tree_mem 20 t4) ~msg:"tree_mem (3)";
  assert_equal false (tree_mem 7 t4) ~msg:"tree_mem (4)"


let test_insert_all _ =
  let lst = [2;1;3] in
  let t = tree_insert 3 (tree_insert 1 (tree_insert 2 empty_tree)) in
  assert_equal t (tree_insert_all lst empty_tree) ~msg:"tree_insert_all (1)"


let test_tree_fold _ =
  let t = Node (7, Node (5, Leaf, Leaf), Node (11, Leaf, Leaf)) in
  assert_equal 11 (tree_fold (fun x l r -> max (max l x) r) 0 t) ~msg:"tree_fold (1)";
  assert_equal 23 (tree_fold (fun x l r -> x + l + r) 0 t) ~msg:"tree_fold (2)"


let test_tree_size _ =
  let t1 = tree_insert 20 (tree_insert 10 empty_tree) in
  let t2 = tree_insert 9 (tree_insert 5 t1) in
  let t3 = tree_insert 15 (tree_insert 13 t2) in
  let t4 = tree_insert 29 (tree_insert 21 t3) in
  assert_equal 8 (tree_size t4) ~msg:"tree_size (1)";
  assert_equal 6 (tree_size t3) ~msg:"tree_size (2)";
  assert_equal 4 (tree_size t2) ~msg:"tree_size (3)";
  assert_equal 2 (tree_size t1) ~msg:"tree_size (4)"


let test_tree_height _ =
  let t1 = tree_insert 20 (tree_insert 10 empty_tree) in
  let t2 = tree_insert 9 (tree_insert 5 t1) in
  let t3 = tree_insert 15 (tree_insert 13 t2) in
  let t4 = tree_insert 29 (tree_insert 21 t3) in
  assert_equal 3 (tree_height t4) ~msg:"tree_height (1)";
  assert_equal 3 (tree_height t3) ~msg:"tree_height (2)";
  assert_equal 2 (tree_height t2) ~msg:"tree_height (3)";
  assert_equal 1 (tree_height t1) ~msg:"tree_height (4)"


let test_tree_as_list _ =
  let lst = [1;2;3;4;5;6] in
  let t1 = tree_insert 3 (tree_insert 4 empty_tree) in
  let t2 = tree_insert 1 (tree_insert 2 t1) in
  let t3 = tree_insert 5 (tree_insert 6 t2) in
  assert_equal lst (tree_as_list t3) ~msg:"tree_as_list (1)"


let test_tree_map _ =
  let t1 = Node (7, Node (5, Leaf, Leaf), Node (11, Leaf, Leaf)) in
  let t2 = Node (8, Node (6, Leaf, Leaf), Node (12, Leaf, Leaf)) in
  let t3 = Node (6, Node (4, Leaf, Leaf), Node (10, Leaf, Leaf)) in
  assert_equal t2 (tree_map succ t1) ~msg:"tree_map (1)";
  assert_equal t3 (tree_map pred t1) ~msg:"tree_map (2)"


let suite =
  "public" >::: [
    "len" >:: test_len;
    "elem_count" >:: test_elem_count;
    "uniq" >:: test_uniq;
    "occurrence_list" >:: test_occurrence_list;
    "bind"  >:: test_bind;
    "ap"  >:: test_ap;
    "tree_mem" >:: test_tree_mem;
    "tree_insert_all" >:: test_insert_all;
    "tree_fold" >:: test_tree_fold;
    "tree_size" >:: test_tree_size;
    "tree_height" >:: test_tree_height;
    "tree_as_list" >:: test_tree_as_list;
    "tree_map" >:: test_tree_map
  ]

let _ = run_test_tt_main suite
