;;path from root to node 

;;(A (B) (C (D)(E)))

;;root 

(defun mymember (e l)
  (cond
    ((null l) nil)
    ((and (atom  (car l)) (equal (car l) e))T)
    ((atom (car l)) (mymember e (cdr l)))
    (T (Or (mymember e (car l)) (mymember e (cdr l))))
  )
  )

(defun path (l e)
  (cond
    ((equal (car l) e) (list e))
    ((mymember e (cadr l)) (cons (car l) (path (cadr l) e)))
    ((mymember e (caddr l)) (cons (car l) (path (caddr l) e)))
    (T nil)
    )
  )

