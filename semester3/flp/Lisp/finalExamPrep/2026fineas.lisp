;;I
;;1.
;;(defun F (L)
;;  (cond
;;      ((null L) 0)
;;      (t ((lambda (a)
;;              (cond
;;                ((> a 2)(+ (car L) (F (crd L)) ) )
;;                (t a)
;;               )
;;              )(F (car L))
;;          ))
;;   )
;;)
;;2.
;;(1 2) U (3 4)U(5)U(6)=(1 2 3 4 5 6)
;;
;;atomii la nivel k is replaced by 0

(defun p3 (n k lev)
  (cond
  ((and (= lev k) (atom n)) 0)
  ((atom n) n)
  (t (mapcar #'(lambda(a)(p3 a k (+ 1 lev) ))n))
  )
  )
