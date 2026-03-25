(* CPSC 310, Spring 2026, Project 2 *)
(*
/* Author:         Daniel Tripoli                             */
/* Major:          Computer Science                           */
/* Creation Date:  February 24, 2026                          */
/* Due Date:       March 2, 2026                              */
/* Course: CPSC    310 010                                    */
/* Professor Name: Dr. Dylan Schwesinger                      */
/* Project:        #2                                         */
/* Filename:       hof.ml                                     */
/* Purpose:        Impliment functions for lists only through */
/*                 List.fold and List.map                     */
*)

(* Instructions: You must use List.map, List.fold_left, or
   List.fold_right to complete these functions. You may not use any
   other functions in the List module. If the rec keyword is added to
   a function, it will be considered incorrect. Note: Some of these
   functions may require a combination of mapping and folding. *)



(* Description: return the length of lst *)   (*TEST EDGE CASES (LIKE EMPTY OR 1 ETC...)*)

let inc acc _ = acc + 1 
let len (lst : 'a list) : int = List.fold_left inc 0 lst

(* Description: return the number of elements in lst that are equal to
   target
 *)
(* let targetCount target acc x = if (x = target) then acc + 1 else acc *)
(* let elem_count (lst : 'a list) (target : 'a) : int = List.fold_left (targetCount target) 0 lst *)
(* Here is my alternative "lamba" approach (anonymous function) *)

let elem_count (lst : 'a list) (target : 'a) : int = 
  List.fold_left (fun acc x -> if (x = target) then acc + 1 else acc) 0 lst 


(* Description: return a list with all duplicate elements removed. The
   order of the resulting list does not matter. *)   
 let uniq (lst : 'a list) : 'a list = 
  List.fold_left (fun accList x -> if (elem_count accList x) = 0 then x :: accList else accList ) [] lst  


(* Description: return a list of tuples where the first member is an
   element of lst and the second member is the number of occurrences
   of first tuple element in lst. The result should contain no
   duplicates. *)

  (* 
  function: isInTupleList
  Description: is required to prevent duplicates, just checks if the tuple list already has the target element added to it
  *)
let isInTupleList (lst : ('a * int) list) (target : 'a) : int = 
  List.fold_left (fun acc x ->
    match x with
    | (first, _) ->
      if (first = target) then 1 else acc) 0 lst (*1 means item is already is in list, 0 means its not*)

let occurrence_list (lst : 'a list) : ('a * int) list = 
  List.fold_left (fun accList x -> if (isInTupleList accList x) = 0 then (x, (elem_count lst x)) :: accList else accList) [] lst

(* Description: Apply the function f to all elements in lst and then
   concatenate the results into a single list. *)

(* let bind (f : 'a -> 'b list) (lst : 'a list) : 'b list = List.fold_left (fun accList lList -> 
  accList @ lList   
  ) [] (List.map f lst) *)

  (*Can also use (@) instead of fun*)

(* Description: apply each function in fs to each argument in args in
   order *)
let ap (fs : ('a -> 'b) list) (args : 'a list) : 'b list = List.fold_left (fun accList f -> accList @ (List.map f args) ) [] fs 

(*this function below was made with the goal of making "ap" as UGLY as possible, I learned a lot from it so its still very valuable 
let ap (fs : ('a -> 'b) list) (args : 'a list) : 'b list = List.fold_left (fun accAns listFromListOfLists -> (List.fold_left (fun acc elementOflist -> acc @ [elementOflist] ) accAns listFromListOfLists) ) [] (List.fold_left (fun accList f -> accList @ [(List.map f args)]  ) [] fs)  
*)


