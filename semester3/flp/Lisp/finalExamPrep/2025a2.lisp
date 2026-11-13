;;atoms on level k are 0

(defun sol (n k lev)
  (cond
    ((and (atom n) (= lev k))0)
    ((atom n) n)
    (t (mapcar #'(lambda(a) (sol a k (1+ lev)))n))
    )
  )
(defun solve(l k)
  (sol l k 0)
  )
