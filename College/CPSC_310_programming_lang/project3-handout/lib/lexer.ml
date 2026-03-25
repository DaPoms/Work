(*HUGE IMPORTANT NOTE:::::: WE NEED TO FOLLOW THE CS3110 OCAML STYLE GUIDE*)
open Token
(* 1. Remove spaces, tabs, newlines " ", "\t", "\n"  
   2. Tokens are case sensitive!!!
   3. Even empty string should return EOF, always end with EOF
   4. If the beginning of a string could be multiple things, the longest match should be preferred

*)
(*Note that this started with brackets??*)
(*rec guarantees functionality*)
(*let tokenize (input : string) : token list = *)
let tokenize (input : string) : string list = 
    Str.split (Str.regexp "[\\n\\t ]+") input  (*note that space does not use quotations to reference*)

    (*List.fold_left () [] *)
    (*                 ^ stores token list
                    ^ Tests regex on 
    
    *)
(*NOTE: Use ^ to ONLY regex the start of the string. Once satisfied, we move forward the amount of the string that has been tokenized*)
(* We don't expect values though yes? Like if theres the end of astatement, we dont need to check that next symbol is ";"? *)

    (*search_forward RETURNS THE STRING WHEREW*)

    (*OCaml are we allowed to use substrings*)


let () = Array.iter (fun s -> Printf.printf "%s" s) tokenize "a\n b          c\td"
