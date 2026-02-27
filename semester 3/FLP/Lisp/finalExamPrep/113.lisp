;creaza lista noua din alta lista de unded ia elementele din k in k indiferent de nivel
(defun niveleaza (l)
  (cond
    ((null l) nil)
    ((atom (car l)) (cons (car l) (niveleaza (cdr l))))
    ((listp (car l)) (append (niveleaza (car l)) (niveleaza (cdr l))))
    )
  )
(defun p1 (l k i)
  (cond
    ((null l) nil)
    ((= k 0) (cons (car l) (p1 (cdr l) i i)))
    (T (p1 (cdr l) (- k 1) i))
    )
  )

(defun p1W (l k)
  (reverse (p1 (niveleaza l) (- k 1) (- k 1)))
  )

;;all atoms on even levels are 0

(defun p2 (n lev)
  (cond
  ((and (atom n) (= (mod lev 2)0 )) 0)
  ((atom n) n)
  (t ( mapcar #'(lambda(a) (p2 a (+ lev 1))) n))
  )
  )
