;;number of nodes on level k

(defun p (n k s lev)
  (cond
    ((and (atom n) (= lev (1+ k))) 1)
    ((atom n) 0)
    (t (apply #'+ (mapcar #'(lambda(a) (p a k s (+ lev 1)))n)))
    )
  )

(defun pW (l k)
   (p l k 0 0)
   )
