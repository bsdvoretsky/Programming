(define-syntax delay
  (syntax-rules ()
    ((delay expr) (list #f (lambda () expr)))))

(define (make promise)
  (if (car promise)
      (caar promise)
      (begin
        (set-car! promise (list ((cadr promise))))
        (caar promise))))

(define-syntax my-if
  (syntax-rules ()
    ((my-if condition expr1 expr2) (let ((promise (delay condition)))
                                    (or (and (make promise) expr1) (and (not (make promise)) expr2))))))

(my-if #t 1 (/ 1 0))
(my-if #f (/ 1 0) 1)