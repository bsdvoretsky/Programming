(define (roots_of_equation a b c)
  (if (< (- (* b b) (* 4 a c)) 0)
      (list)
      (if (= (- (* b b) (* 4 a c)) 0)
          (list (/ (* -1 b) (* 2 a)))
<<<<<<< HEAD
          (list (/ (+ (* -1 b) (sqrt (- (* b b) (* 4 a c)))) (* 2 a)) (/ (- (* -1 b) (sqrt (- (* b b) (* 4 a c)))) (* 2 a))))))
=======
          (list (/ (+ (* -1 b) (sqrt (- (* b b) (* 4 a c)))) (* 2 a)) (/ (- (* -1 b) (sqrt (- (* b b) (* 4 a c)))) (* 2 a))))))
>>>>>>> 5e824dfd9b13da29c7b6183c76c141539b5f84b7
