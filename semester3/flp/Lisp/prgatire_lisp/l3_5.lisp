;; sum of even numb - sum of odd numb

(defun even (n)
  (zerop (mod n 2))
  )
(defun p5 (n)
  (cond
    ((and (numberp n) (even n)) n)
    ((and (numberp n) (not (even n))) (- n (* 2 n)))
    ((atom n) 0)
    (T (apply #'+(mapcar #'p5 n)))
    )
  )
