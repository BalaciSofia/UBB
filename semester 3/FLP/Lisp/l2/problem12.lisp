;(A (B (C) (D)) (E))
;   A
;  / \
; B   E
;/ \
;C  D
;
;prorder(l1...ln)=[], n=0
;                 list(l1), atom(l1)
;		  list(l1) U preorder(l2) U preorder(l3), otherwise
(defun preorder(tree)
  (cond
    ((null tree) nil)
    ((atom tree) (list tree))
    (t (append (list (car tree)) (preorder(cadr tree)) (preorder (caddr tree))))
    )
  )
;              A
;             / \
;            B   H
;           / \ / \
;          D  C G  I
;            / \
;           F   E
;
;
;

