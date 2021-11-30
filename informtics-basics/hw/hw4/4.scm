(define-syntax define-struct
  (syntax-rules ()
    ((define-struct type (v1 ...))
     (let ((ie (interaction-environment)))
       (eval `(define ,(string->symbol (string-append "make-" (symbol->string 'type)))
                ,(lambda (v1 ...) (append (list 'type) (list (list 'v1 v1) ...)))) ie)
       (eval `(define ,(string->symbol (string-append (symbol->string 'type) "?"))
                ,(lambda (p) (and (list? p) (equal? (car p) 'type)))) ie)
       (eval `(define ,(string->symbol (string-append (symbol->string 'type) "-" (symbol->string 'v1)))
                ,(lambda (p) (cadr (assoc 'v1 (cdr p))))) ie) ...
       (eval `(define ,(string->symbol (string-append "set-" (symbol->string 'type) "-" (symbol->string 'v1) "!"))
                ,(lambda (p v) (set-car! (cdr (assoc 'v1 (cdr p))) v))) ie) ...))))