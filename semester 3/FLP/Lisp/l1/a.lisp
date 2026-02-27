;computes the dot product of two linear vectors
;dot-product(v(1)...v(n),l(1)...l(m))=0,n=0 or m=0
;				      l1*v1+dot-product(v(2)...v(n),l(2)...l(n))

(defun dot-product (v l)
  (cond
    ((or (null v) (null l)) 0)
    (T (+ (* (car v) (car l))
         (dot-product (cdr l) (cdr l))))
  )
)

