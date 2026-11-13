
;;all nodes on level k replaced with given value e

(defun repl (n k e curr)
  (cond
    ((and (atom n) (equal (1+ k) curr)) e)
    ((atom n) n)
    (T (mapcar #'(lambda(a) (repl a k e (+ curr 1)))n))
    )
  )

(defun p1 (l e k)
  (repl l k e 0)
  )
