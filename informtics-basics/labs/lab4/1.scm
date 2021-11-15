(define call-cc
  call-with-current-continuation)

(define-syntax assert
  (syntax-rules ()
    ((assert e)
     (call-cc
      (lambda (exit)
           (if (not e)
               (exit (begin (display "FAILED: ") (write 'e)))))))))

(define (1/x x)
  (assert (not (zero? x)))
  (/ 1 x))

(map 1/x '(1 2 3 4 5))

(map 1/x '(-2 -1 0 1 2))
