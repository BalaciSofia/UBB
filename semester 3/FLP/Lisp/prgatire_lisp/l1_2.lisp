;;depth of a list

(defun depth (l)
  (cond
    ((null l) 1)
    ((listp (car l)) (max (+ 1 (depth (car l))) (depth (cdr l))))
    (T (depth (cdr l))
    )
  ))

;;sort without keepingdouble values


(defun insert (l e)
  (cond
    ((null l) (list e))
    ((> e (car l)) (cons (car l) (insert (cdr l) e)))
    ((= e (car l)) l)
    ((< e (car l)) (cons e l))
    )
  )
(defun mysort (l new)
  (cond
    ((null l) new)
    (T (mysort (cdr l) (insert new (car l))))
    )
  )
;;intersection of 2 sets

(defun inters (l1 l2)
  (cond
    ((null l1) nil)
    ((member (car l1) l2) (cons (car l1) (inters (cdr l1) l2)))
    (T (inters (cdr l1) l2))))
