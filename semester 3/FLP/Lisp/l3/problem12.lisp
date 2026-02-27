;Write a function that substitutes a given element with another on all levels of a given list
;
;substlist(n,e1,e2)=e2,n is a number and n=e1
;                   n, n is an atom !=e1
;	            substlist(n(1)) U substlist(n(2)) U ... substlist(n(m)), otherwise (aka n is a list)
;
;(substlist '(1 A 3 (3 F (1) (D r 3 (3)) 6) 4 12 3 v) 3 5)
(defun substlist (n e1 e2)
  (cond 
    ((and (numberp n) (equal n e1)) e2)
    ((atom n) n)
    (t (mapcar #'(lambda(a) (substlist a e1 e2)) n))
 )
)
