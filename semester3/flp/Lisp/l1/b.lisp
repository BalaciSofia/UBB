;calculate maximum at any level

;collect-numbers(l(1)...l(n))=nil,n=0
;			      l(1) U collect-numbers(l(2)...l(n),l(1) is a number
;			      collect-numbers(l(1)) U collect-numbers(l(2)...l(n)),l(1) is a list
;			      collect-numbers(l(2)...l(n)), otherwise


(defun collect-numbers (lst)
  (cond
    ((null lst) nil)
    ((numberp (car lst))
     (cons (car lst) (collect-numbers (cdr lst))))
    ((listp (car lst))
     (append (collect-numbers (car lst))
             (collect-numbers (cdr lst))))
    (t (collect-numbers (cdr lst)))))

;maxim(l1...ln)=max(l1,l2...ln)
(defun maxim (lst)
  (let ((nums (collect-numbers lst)))
    (when nums(apply #'max nums))
  )
)

