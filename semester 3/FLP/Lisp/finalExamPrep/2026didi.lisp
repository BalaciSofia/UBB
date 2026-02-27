;;I
;;1
;;(defun F (L1 L2)
;;	((lambda(a)
;;        (
;;	    (append a
;;		(cond
;;		   ((null L1) (cdr L2))
;;		   (t (list a (car L2)))
;;	     	)
;;	    )
;;	   ))(F (car L1) L2)
;;	)
;;)
;;3(1 2 2 2)
;;maximum at any level

(defun p3 (n)
  (cond
    ((numberp n) n)
    ((null n) -9999999)
    ((atom n) -9999999)
    (t (apply #'max (mapcar #'p3 n)))))
