;;n th element of the list or nill if not exists

(defun nthx (l n)
  (cond
    ((null l) nil)
    ((zerop (1- n)) (car l))
    (T (nthx (cdr l) (1- n)))
    )
  )


;;an atom as a member of a list wivh is non linear

(defun ismember (l e)
  (cond
    ((null l) nil)
    ((and (atom (car l)) (equal e (car l))) T)
    ((listp (car l)) (or (ismember (car l) e) (ismember (cdr l) e)))
    (T (ismember (cdr l) e))
    )
  )

;;determine the list of all sublists 
(defun sublists (l)
  (cond
    ((null l) nil)
    ((listp (car l)) (append (list (car l)) (sublists (car l)) (sublists (cdr l))))
    (t (sublists (cdr l)))
    )
  )
(defun sublistsaux (l)
  (cons l (sublists l)))


;;linear list into a set

(defun myset (l new)
  (cond
    ((null l) (reverse new))
    ((member (car l) new) (myset (cdr l) new))
    (T (myset (cdr l) (cons (car l) new)))
    )
  )
