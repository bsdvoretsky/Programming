(define-syntax my-let*
  (syntax-rules ()
    ((my-let* () action ...)
     ((lambda () action ...)))
    ((my-let* ((v a) vs ...) action ...)
     ((lambda (v) (my-let* (vs ...)
                          action ...)) a))))

(define-syntax my-let
  (syntax-rules ()
    ((my-let ((v a) ...) action ...)
     ((lambda (v ...) action ...) a ...))))

(my-let ((x 1) (y 3) (z 3))
        (+ x y z))
(my-let* ((x 1) (y 3) (z x))
         (+ x y z))