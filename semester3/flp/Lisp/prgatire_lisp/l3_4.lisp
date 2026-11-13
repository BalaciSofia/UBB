;;product of numeric atoms of a nested list

(defun prod (n)
  (cond 
    ((numberp n) n)
    ((atom n) 1)
    (T (apply #'*(mapcar #'prod n)))
    )
  )
