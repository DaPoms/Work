(* CPSC 310, Spring 2026, Project 2 *)
(*
/* Author:         Daniel Tripoli                                */
/* Major:          Computer Science                              */
/* Creation Date:  February 24, 2026                             */
/* Due Date:       March 2, 2026                                 */
/* Course: CPSC    310 010                                       */
/* Professor Name: Dr. Dylan Schwesinger                         */
/* Project:        #2                                            */
/* Filename:       tree.ml                                       */
/* Purpose:        Impliment functions pertaining to trees       */
/*                 to demonstrate knowledge of trees + recursion */
*)

(* Type definition for a tree. A tree is either a leaf or
   a node containing a element, a left subtree, and a right subtree *)
type 'a tree =
  | Leaf
  | Node of 'a * 'a tree * 'a tree

let empty_tree = Leaf

(* Description: Given a binary search tree, return a new binary search
   tree that with the new element inserted while preserve the property
   that all elements less than the element in a given node are in the
   left subtree and all elements greater than the element are in the
   right subtree. If the element already exists in the tree, then it
   is not inserted.

   Precondition: the argument t satisfies the binary tree properties

   Parameters: x : 'a - the element to insert
               t : 'a tree - the original binary search tree

   Return: a new binary search tree with the new element inserted
   properly
*)
let rec tree_insert (x : 'a) (t : 'a tree) : 'a tree =
  match t with
  | Leaf -> Node(x, Leaf, Leaf)
  | Node (y, l, r) when x > y -> Node (y, l, tree_insert x r)
  | Node (y, l, r) when x = y -> t
  | Node (y, l, r) -> Node (y, tree_insert x l, r)


(****************************************************************************)
(* Implement the functions below. *)
(****************************************************************************)

(* Description: return true if x is an element in the tree t. *)
let rec tree_mem (x : 'a) (t : 'a tree) : bool =
  match t with 
  | Leaf -> false
  | Node (v, l, r) when x < v -> tree_mem x l
  | Node (v, l, r) when x > v -> tree_mem x r
  | Node (v, l, r) -> true
    
(* Description: return a tree that is the same as tree t, but with all
   the elements in list lst added to it. The elements should be added
   in the order they appear in the list with the tree_insert function.
   *)
let rec tree_insert_all (lst : 'a list) (t : 'a tree) : 'a tree = 
  match lst with
  | [] -> t
  | (x::xs) -> tree_insert_all xs (tree_insert x t)

(* Description: given the function f that takes three parameters: the
   value of the current node, the value of the accumulator returned by
   the left subtree, and and the value of the accumulator returned by
   the right subtree and an initial value init, iterate over the tree
   t using f to return the accumulated value.
*)
let rec tree_fold (f : 'b -> 'a -> 'a -> 'a) (init : 'a) (t : 'b tree) : 'a = 
  match t with
  | Leaf -> init (*we need to use init to allow the user to specify the accumulator*)
  | Node (v, l, r) ->
    f v (tree_fold f init l) (tree_fold f init r) 

(* Description: return the number of elements in the tree t. You must
   use tree_fold to implement your solution. *)
let rec tree_size (t : 'a tree) : int =
  tree_fold (fun _ l r -> 1 + l + r ) 0 t 

(* Description: return the height of the tree t. The empty tree has a
   height of zero. You must use tree_fold to implement your
   solution.*)
let rec tree_height (t : 'a tree) : int = 
  if t = Leaf then 0
  else
    tree_fold (fun _ l r -> 1 + (max l r) ) (-1) t (*we need -1 as the head itself does not count as height, but our function DOES consider the head, so we need to cancel it out*) 

(* Description: return a list that corresponds to an in-order
   traversal of the tree t. You must use tree_fold to implement your
   solution. *)
let rec tree_as_list (t : 'a tree) : 'a list = 
   tree_fold (fun v l r -> l @ [v] @ r ) [] t  (*Note that v is the parent node, l and r are the results from everything below that*)
  


(* Description: return a tree where the function f is applied to all
   the elements of the tree t. You must use tree_fold to implement
   your solution.
   *)
let rec tree_map (f : 'a -> 'b) (t : 'a tree) : 'b tree =
   tree_fold (fun v l r -> Node(f v, l, r)) empty_tree t
 (*We remake the tree with the passed function applied to each element from the bottom up. The bottom nodes have l and r of leaf, the next set of nodes point to these nodes as their left/right, and so on till the root node is pointing to the nodes that hold the left and right subtrees*)

