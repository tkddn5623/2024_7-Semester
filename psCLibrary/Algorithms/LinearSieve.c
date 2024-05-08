int* linear_sieve(int Dest_factors[], const int max) {
	int len = 0, capacity = 16;
	int* Dest_primes = calloc(capacity, sizeof(int)); if (!Dest_primes) exit(1);
	Dest_factors[0] = 0;
	Dest_factors[1] = 0;
	for (int i = 2; i <= max; i++) {
		if (!Dest_factors[i]) {
			if (len + 1 >= capacity && !(Dest_primes = realloc(Dest_primes, (capacity *= 2) * sizeof(int)))) exit(1);
			Dest_primes[++len] = i;
		}
		for (int j = 1; j <= len; j++) {
			if (i * Dest_primes[j] > max) break;
			Dest_factors[i * Dest_primes[j]] = Dest_primes[j];
			if (i % Dest_primes[j] == 0) break;
		}
	}
	Dest_primes[0] = len;
	return Dest_primes;
}

/*
* 2024.2.6
* Linear sieve renewal
* (Reference: codeforces.com/blog/entry/54090)
*
* 2024.5.9 Thu
* Switch to dynamic array
/