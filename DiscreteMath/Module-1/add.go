package main

func add(a, b []int32, p int) []int32 {
	res := []int32 {}
	if len(a) < len(b) {
		for i := len(a); i < len(b); i++ {
			a = append(a, 0)
		}
	} else if len(b) < len(a) {
		for i := len(b); i < len(a); i++ {
			b = append(b, 0)
		}
	}
	var t int32 = 0
	for i := range(a) {
		res = append(res, (a[i] + b[i] + t) % int32(p))
		t = (a[i] + b[i] + t) / int32(p)
	}
	for t > 0 {
		res = append(res, t % int32(p))
		t /= int32(p)
	}
	return res
}