;;hight of a node in a tree (root subtree1 subtree 2)
;;hight 

(defun depth (l d)
  (cond
    ((atom l) d)
    (t (apply #'max (mapcar #'(lambda (a) (depth a (+ d 1)))l)))
    )
  )

(defun hight (l li node curr)
  (cond
    ((and (atom l) (equal node l)) (- (depth li 0) curr))
    ((atom l) -1)
    (t (apply #'max (mapcar #'(lambda (a) (hight a li node (+ 1 curr)))l)))
    )
  )

(defun heightW (l node)
  (hight l l node 0)
  )
