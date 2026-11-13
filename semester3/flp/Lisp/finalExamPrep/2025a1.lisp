;;I
;;1
;;(defun Fct (F L)
;;  (cond
;;    ((null l) nil)
;;   (t ((lambda (a)
;;	  ((cond
;;	    (a (cons a (Fct F (cdr L))))
;;	    (T nil)
;;	    )
;;	  ))(funcall F (car L))
;;	)
;;     )
;;    )
;;  )
;;3 (A A)
;;
;;II replace all nodes on odd levels with given value e

(defun repl (n e lev)
  (cond
    ((and (atom n) (= (mod lev 2) 1)) e)
    ((atom n) n)
    (t (mapcar #'(lambda(a) (repl a e (+ 1 lev)))n))
    )
  )
(defun wrapper (l e)
  (repl l e -1)
  )
