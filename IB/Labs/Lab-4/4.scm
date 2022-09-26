(define-syntax my-if
  (syntax-rules ()
    ((my-if condition expr1 expr2) (let ((promise (delay condition)))
                                    (or (and (force promise) expr1) (and (not (force promise)) expr2))))))

(my-if #t 1 (/ 1 0))
(my-if #f (/ 1 0) 1)