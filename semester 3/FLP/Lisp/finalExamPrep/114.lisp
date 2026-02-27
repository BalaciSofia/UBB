;;replace atoms with 0 on level k


(defun replaceA (n k)
  (cond
    ((and  (atom n) (= k 0)) 0)
    ((atom n) n)
    (T (mapcar #'(lambda (a) (replaceA a (- k 1))) n)) 
    )
  )
