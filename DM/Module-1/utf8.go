package main

func encode(utf32 []rune) []byte {
	enres := []byte {}
	var mask rune = 255
	for _, c := range utf32 {
		if c < 128 {
			enres = append(enres, byte(c))
		} else if c < 2048 {
			enres = append(enres, byte((c >> 6) + (mask << 6) & mask))
			enres = append(enres, byte(c & (mask >> 2) + (mask << 7) & mask))
		} else if c < 65536 {
			enres = append(enres, byte((c >> 12) + (mask << 5) & mask))
			enres = append(enres, byte((c >> 6) & (mask >> 2) + (mask << 7) & mask))
			enres = append(enres, byte(c & (mask >> 2) + (mask << 7) & mask))
		} else {
			enres = append(enres, byte((c >> 18) + (mask << 4) & mask))
			enres = append(enres, byte((c >> 12) & (mask >> 2) + (mask << 7) & mask))
			enres = append(enres, byte((c >> 6) & (mask >> 2) + (mask << 7) & mask))
			enres = append(enres, byte(c & (mask >> 2) + (mask << 7) & mask))
		}
	}
	return enres
}

func decode(utf8 []byte) []rune {
	deres := []rune {}
	var mask rune = 255
	i := 0
	for i < len(utf8) {
		if (utf8[i] >> 4) == 15 {
			deres = append(deres, ((rune(utf8[i]) & (mask >> 5)) << 18 + 
			(rune(utf8[i+1]) & (mask >> 2)) << 12 + 
			(rune(utf8[i+2]) & (mask >> 2)) << 6 + 
			(rune(utf8[i+3]) & (mask >> 2))))
			i += 4
		} else if (utf8[i] >> 5) == 7 {
			deres = append(deres, ((rune(utf8[i]) & (mask >> 4)) << 12 + 
			(rune(utf8[i+1]) & (mask >> 2)) << 6 + 
			(rune(utf8[i+2]) & (mask >> 2))))
			i += 3
		} else if (utf8[i] >> 6) == 3 {
			deres = append(deres, ((rune(utf8[i]) & (mask >> 3)) << 6 + 
			(rune(utf8[i+1]) & (mask >> 2))))
			i += 2
		} else {
			deres = append(deres, rune(utf8[i]))
			i += 1
		}
	}
	return deres
}

func main() {
	
}