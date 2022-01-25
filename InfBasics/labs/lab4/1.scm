(define call-cc
  call-with-current-continuation)

(define return 0)

(define (use-assertions)
  (call-cc (lambda (c) (set! return c))))

(define-syntax assert
  (syntax-rules ()
    ((assert e)
     (if (not e)
         (begin (display "FAILED: ") (write 'e) (return))))))

(use-assertions)

(define (1/x x)
  (assert (not (zero? x)))
  (/ 1 x))

(map 1/x '(1 2 3 4 5))

(map 1/x '(-2 -1 0 1 2))
