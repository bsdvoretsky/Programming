(define-syntax trace-ex
  (syntax-rules ()
    ((trace-ex value) (begin (display 'value) (display " => ") (display value) (newline) value))))