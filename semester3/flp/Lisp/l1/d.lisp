;T-even numbers of elements
;Nil otherwise

;even-length(l1...ln)=T,n=0
;		      nil, n=1
;		      even-length(l3...ln),otherwise

(defun even-length (lst)
  (cond
    ((null lst) t)                  ; 0 elements → even
    ((null (cdr lst)) nil)          ; 1 element left → odd
    (t (even-length (cddr lst))))) ; remove 2 elements and continue

