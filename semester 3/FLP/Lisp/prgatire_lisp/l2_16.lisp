;;tree of type 2 is balanced?
;;diferenta intre depthurile subtriurilor este 1


;; a 2 b 0 c 2 d 0 e 0 --balanced
;; a 2 b 0 c 2 d 0 e 1 f --not balanced
;; a 2 b 1 x 1 k 0 c 2 d 0 e 1 f 0

;;how to calculate t=depth of a tree
(defun calculate_depth (l d)
  (cond 
    ((null l) d)
    ((not (zerop (cadr l))) (calculate_depth (cddr l) (1+ d)))
    (T (calculate_depth (cddr l) d))
    )
  )
(defun left (l)
  (cond
    ((equal (cadr l) 0) (list (car l) (cadr l)))
    ((equal (cadr l) 1) (append (list (car l) (cadr l)) (left (cddr l))))
    ((equal (cadr l) 2) (append (list (car l) (cadr l)) (left (cddr l))))
    )
  )

(defun right (l)
  (cond
    ((equal (cadr l) 0) (list (car l) (cadr l)))
    ((equal (cadr l) 1) (append (list (car l) (cadr l)) (right (cddr l))))
    ((equal (cadr l) 2) (append (list (car l) (cadr l)) (left (cddr l))))
    ) 
    )

;;(defun is_balanced (l)
  ;;(cond

