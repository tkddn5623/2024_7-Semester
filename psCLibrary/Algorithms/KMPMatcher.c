#define MAXLEN (1000000)

int* KMP_Matcher(const char text[], const char pattern[]) {
	static int prefix[MAXLEN + 1];
	const int len_text = strlen(text);
	const int len_ptrn = strlen(pattern);
	int idx_size = 0, idx_capacity = 16;
	int* idx_list = calloc(idx_capacity, sizeof(int)); if (!idx_list) exit(1);

	if (len_text < len_ptrn) return idx_list;

	// Compute-Prefix-Function
	prefix[1] = 0;
	for (int k = 0, i = 1; i < len_ptrn; i++) {
		while (k > 0 && pattern[i] != pattern[k])
			k = prefix[k];
		if (pattern[i] == pattern[k])
			k = k + 1;
		prefix[i + 1] = k;
	}

	// KMP-Matcher
	for (int q = 0, i = 0; i < len_text; i++) {
		while (q > 0 && text[i] != pattern[q])
			q = prefix[q];
		if (text[i] == pattern[q])
			q = q + 1;
		if (q == len_ptrn) {
			q = prefix[q];
			if (idx_size + 1 >= idx_capacity && !(idx_list = realloc(idx_list, (idx_capacity *= 2) * sizeof(int)))) exit(1);
			idx_list[++idx_size] = i - len_ptrn + 1;
		}
	}

	idx_list[0] = idx_size;
	return idx_list;
}


/*
* 2024.5.9 Thu
* Switch to dynamic array
*
* 2024.8.21 Wed
* Array index bound error fixed.
*/