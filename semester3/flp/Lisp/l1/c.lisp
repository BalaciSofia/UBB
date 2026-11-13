;evaluates arithmetic expr

(defun operator (op a b)
	(cond
		((string= op "+") (+ a b))
		((string= op "-") (- a b))
		((string= op "*") (* a b))
		((string= op "/") (floor a b))
	)
)

;expression(l1...ln)=nil,n=0
;		     operator (l1 l2 l3) U expression(l4...ln),l1 is atom, l2 and l3 are numbers 		    
;		     l1 U expression(l2...ln),otherwise

(defun expression (l)
    (cond
        ((null l) nil)
        ((and (and (numberp (cadr l)) (numberp (caddr l))) 
	      (atom (car l))) (cons (operator (car l) (cadr l) (caddr l)) (expression (cdddr l))))
        (T (cons (car l) (expression (cdr l))))
    )
)

;solve(l1...ln)=l1,n=1
;		solve(expression(l1...ln)),otherwise

(defun solve (l)
    (cond
        ((null (cdr l)) (car l))
        (T (solve (expression l)))
    )
)
