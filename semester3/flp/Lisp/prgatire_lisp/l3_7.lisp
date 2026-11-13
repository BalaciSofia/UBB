;;substitute an element e with a list l

(defun mysubst (e l1 n)
  (cond 
    ((equal e n) l1)
    ((atom n) n)
    (T (mapcar #'(lambda(s) (mysubst e l1 s)) n))
    )
  )
