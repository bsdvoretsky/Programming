function generate_srings(n, l) {
	for (let i = 0; i < n; i++) {
		t = "";
		for (let j = 0; j < l; j++)
			t += String.fromCharCode(Math.floor(Math.random() * 95) + 32);
		console.log(t);
	}
}

function make_memo_fun(f) {
	return function memofun (...args) {
		if (typeof (memofun.memargs) == 'undefined') {
			memofun.memargs = new Map();
		}
		let res = false;
		memofun.memargs.forEach((value, key) => {
			if (JSON.stringify(args)==JSON.stringify(key)) res = value;
		});
		if (res) {
			console.log("Этот вызов уже мемоизирован ;)");
			return res;
		}
		res = f(...args);
		memofun.memargs.set(args, res);
		return res;
	};
}

function factorial(num) {
	if (num == 0) {
		return 1;
	} else {
		return num * factorial(num - 1);
	}
}

function fib(num) {
	if (num == 0) {
		return 0;
	} 
	else if (num == 1) {
		return 1;
	}
	else {
		return fib(num - 1) + fib(num - 2);
	}
}

function concat(word1, word2) {
	return word1 + word2;
}

