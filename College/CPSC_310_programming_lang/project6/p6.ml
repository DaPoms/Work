(*
* Author:         Daniel Tripoli                             
* Major:          Computer Science                           
* Creation Date:  May 2, 2026                             
* Due Date:       May 8, 2026                             
* Course: CPSC    310 010                                    
* Professor Name: Dr. Dylan Schwesinger                      
* Project:        #6                                         
* Filename:       p6.ml                                     
* Purpose:        Implements the solution to a graph traversal problem in ocaml                        
*)

(*
* Function name:  createGraphWithTaskList
* Description:    Uses a given structure of dependent (the node thats dependent)
*                 to prequisite (the node it's dependent on) to make an 
*                 association list of each node's prequisite nodes before it can  
*                 be 'popped'
* Parameters:     string list taskList - The list of dependent -> prequisite 
*                 relationships
* Return Value:   (string * string list) list The associations of nodes and
*                 The nodes that must be traversed before the node can be 
*                 accessed
*)
let createGraphWithTaskList (taskList : string list) : (string * string list) list = 
  let rec aux remainingTList graph = 
    match remainingTList with
    | (prequisite::dependent::t) -> ( 
      let valueprequisite = (List.assoc_opt prequisite graph) in
      let valuedependent = (List.assoc_opt dependent graph) in
      let updatedGraph = (
      match valueprequisite with
      | None -> (prequisite,[])::graph
      | _ -> graph 
    )
    in
      match valuedependent with
      | None -> aux t ((dependent,[prequisite])::updatedGraph)
      | Some prevPrequisites -> 
        let removedAssocGraph = 
          List.filter (fun (k,_) -> k <> dependent) updatedGraph in
          aux t ((dependent, prequisite :: prevPrequisites) :: removedAssocGraph)
    )
    | _ -> graph
    in
      aux taskList []

(*
* Function name:  getInputTaskList
* Description:    Collects user input (infering proper formatting) for the 
*                 creation of a task list from the input
* Parameters:     None
* Return Value:   string list - The task list. Every 2 are their own pair, with
*                 The first being the dependent, and the 2nd being the 
*                 prequisite node (must be evaluated first)
*)
let getInputTaskList _ : string list =  
  print_endline ("Enter your task list input (every 1st line of pair " ^ 
  "denotes the dependent, 2nd line denotes prequisite / what the dependent is" ^ 
  " prequisite to):");
  let rec aux strList =
    try
      let str = read_line () in
      aux (str :: strList)
    with 
    | End_of_file -> strList
  in
    aux []


(*
* Function name:  removeAllReferencesToNode
* Description:    Removes the target node and it's references from a graph
* Parameters:     string target - The node that is removed
*                 (string * string list) list graph - The graph that gets the  
*                 target node removed
* Return Value:   string list - A graph with all references to the given node 
*                 removed from the original graph
*)
let removeAllReferencesToNode (target : string) (graph : (string * string list) list) : (string * string list) list =
  let noTargetRefsGraph = 
    List.map (fun (k,v) -> k,(List.filter (fun e -> e <> target) v) ) graph in
    List.filter(fun (k,_) -> k <> target ) noTargetRefsGraph

(*
* Function name:  printGraphTraversal
* Description:    Traverses a graph and prints out the name of the nodes it 
*                 traverses
* Parameters:     (string * string list) list) graph The graph that gets 
*                 traversed
* Return Value:   unit
*)
let printGraphTraversal (graph: (string * string list) list) : unit = 
  let sortedGraph = List.sort (fun a b -> if a > b then 1 else if a < b then -1 else 0) graph in
    let rec aux currGraph =
        match List.find_opt (fun (_,v) -> v = []) currGraph with
        | Some (k,v) -> 
          print_endline k;
          aux (removeAllReferencesToNode k currGraph)
        | None -> 
          match currGraph with
          | [] -> ()
          | _ -> print_endline "Cycle" 
    in aux sortedGraph; 
    ()

let () =
  let taskList = getInputTaskList () in
  let graph = createGraphWithTaskList taskList in
  print_endline "\n";
  printGraphTraversal graph;
  
