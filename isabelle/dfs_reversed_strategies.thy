theory dfs_reversed_strategies
  imports Main 
begin

(* Node label_of_node list_of_children_nodes (empty for leaves) *)
datatype 'a tree =  Node "'a" "'a tree list"

(* 
join (list1,list2,listn) a ⟹ [a] @ list1 @ [a] @list2 ... [a] @listn [a]
to insert all visits of current node into list 
*)

fun join:: "'a list list ⇒ 'a ⇒ 'a list" where
"join Nil a = [a]" | 
"join (Cons x xs) a = Cons a x @ (join xs a)"

(* 
main functions 
for both node is added to list on each visit 
*)
fun left_dfs :: "'a tree ⇒ 'a list" where 
  "left_dfs (Node a li) = join (map left_dfs li) a"  

fun right_dfs :: "'a tree ⇒ 'a list" where
  "right_dfs (Node a li) = join (map right_dfs (rev li)) a"

(* simple reverse function to simplify the goal *)
fun rev_right_dfs :: "'a tree ⇒ 'a list" where
 "rev_right_dfs a = rev (right_dfs a)"

(* basically need to prove left_dfs ≡ rev_right_dfs *)

(* 
sample_tree depth_of_generation label_of_cur_node ⟹ generated ternary tree
just to test dfs functions 
*)

fun sample_tree:: "nat ⇒ nat ⇒ nat tree" where
"sample_tree 0 label = (Node label [])" |
"sample_tree (Suc depth) label = (Node label [(sample_tree depth (3*label) ),(sample_tree depth (3*label+1)),(sample_tree depth (3*label+2))])"

value "sample_tree 2 1"
value "right_dfs(sample_tree 2 1)"
value "left_dfs (sample_tree 2 1)"
value "rev_right_dfs(sample_tree 2 1)"

lemma open_join: "join (xs@[x]) a = (join xs a) @ x @ [a]"
  apply(induct xs)
  apply(auto)
  done

lemma rev_join : " rev (join x a) = join (rev (map rev x)) a"
  apply (induct x)
  apply (simp)
  apply (simp add: open_join)
  done

lemma rev_combine_right_dfs: "rev (map right_dfs (rev li)) = map rev (map rev_right_dfs li)"
  apply(induct li)
  apply auto
  done

lemma rev_right_dfs_simp: "rev_right_dfs (Node label children) = join(map rev_right_dfs children) label"
  apply(auto)
  apply(metis rev_combine_right_dfs rev_join rev_rev_ident)
  done

theorem left_dfs_is_rev_right_dfs: "left_dfs x = rev_right_dfs x"
  apply(induct x)
  apply(metis left_dfs.simps map_eq_conv rev_right_dfs_simp)
  done

theorem result: "left_dfs x = rev(right_dfs x)"
  apply(simp add: left_dfs_is_rev_right_dfs)
  done

