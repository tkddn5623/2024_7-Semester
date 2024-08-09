int MergeSort_compare_$$$$(const @@@@ _A, const @@@@ _B) {
	return _A - _B;
}
void MergeSort_impl_$$$$(@@@@ list[], @@@@ sorted[], const int left, const int right) {
	if (left >= right) return;
	const int mid = left + (right - left) / 2;
	MergeSort_impl_$$$$(list, sorted, left, mid);
	MergeSort_impl_$$$$(list, sorted, mid + 1, right);
	int idx = left, first = left, second = mid + 1;
	while (first <= mid && second <= right) {
		if (MergeSort_compare_$$$$(list[first], list[second]) <= 0) sorted[idx++] = list[first++];
		else sorted[idx++] = list[second++];
	}
	while (first <= mid)    sorted[idx++] = list[first++];
	while (second <= right) sorted[idx++] = list[second++];
	for (int i = left; i <= right; i++) list[i] = sorted[i];
}
void MergeSort_$$$$(@@@@ list[], const int size) {
	@@@@* sorted = calloc(size, sizeof(@@@@)); if (!sorted) exit(1);
	MergeSort_impl_$$$$(list, sorted, 0, size - 1);
	free(sorted);
}


/*
* 2022.10.9 Sun
* 2023.1.30 Mon : Improved read
* 2024.1.20 Sat : Improved readability
* 2024.1.28 Sun : Non recursive example added
* 2024.2.21 Wed : trivial change
* 2024.5.8  Wed : C++ style template added, non recursive removed
*/