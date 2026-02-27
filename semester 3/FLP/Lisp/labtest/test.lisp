;;numar reprezentat in lista 
;;determina successor fara a converi numarul


;;rev(l)= nil,n=0
;;        rev(l2...ln) U l1,otherwise

(defun rev (l)
  (cond
    ((null l)nil)
    (t (append (rev (cdr l)) (list (car l))))
  )
  )

;;primeste numarul invers
;;det(l) = 1,n=0
;;         0 U det(l2...ln), l1+1=10
;;         (l1+1) U l2...ln,otherwise

(defun det (l)
  (cond
    ((null l) (list 1))
    ( (= (+ (car l) 1) 10) (cons 0 (det (cdr l))))
    ( t ( cons ( + (car l) 1) (cdr l)))
    )
  )

(defun solve (l)
  (rev (det (rev l)))
  )
