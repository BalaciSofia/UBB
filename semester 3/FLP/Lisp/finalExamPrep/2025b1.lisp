

;;(defun F(L)
;;  (cond
;;    ((null L) nil)
;;    ((listp (car L))
;;     ((lambda(a)
;;	((append a (F (cdr l)) (car a)))
;;	)(F (car L))))
;;    (t (list (car  l)))
;;    )
;;  )

;;3.(2 3 5 6)


;;substitute element e1 with e2 at odd leveles of the list
;;superficial is 1

(defun myreplace (n e1 e2 lev)
  (cond
    ((and (atom n) (oddp lev) (equal n e1))e2)
    ((atom n) n)
    (t (mapcar #'(lambda (a) (myreplace a e1 e2 (+ 1 lev)))n))
    )
  )

(defun solve (l e1 e2)
  (myreplace l e1 e2 0)
  )

