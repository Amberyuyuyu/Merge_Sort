#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>


void MergeSortNonR(int* a, int n) {
	int* tmp = (int*)malloc(sizeof(int) * n);
	int gap = 1;
	while (gap < n) {
		for (int i = 0; i < n; i += 2 * gap) {
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2 = i + 2 * gap - 1;
			if (begin2 > n - 1) {
				break;
			}
			if (end2 > n - 1) {
				end2 = n - 1;
			}
			int index = i;
			while (begin1 <= end1 && begin2 <= end2) {
				if (a[begin1] <= a[begin2]) {
					tmp[index++] = a[begin1++];
				}
				else {
					tmp[index++] = a[begin2++];
				}
			}
			while (begin1 <= end1) {
				tmp[index++] = a[begin1++];
			}
			while (begin2 <= end2) {
				tmp[index++] = a[begin2++];
			}
			for (int j = i; j <= end2; j++) {
				a[j] = tmp[j];
			}
		}

		gap *= 2;
	}
}
void _MergeSort(int* a, int left, int right, int* tmp) {
	if (left >= right) {
		return;
	}
	int mid = (right + left) >> 1;
	_MergeSort(a, left, mid,tmp);
	_MergeSort(a, mid + 1, right, tmp);
	int begin1 = left, end1 = mid;
	int begin2 = mid + 1, end2 = right;
	int index = left;
	while (begin1 <= end1 && begin2 <= end2) {
		if (a[begin1] <= a[begin2]) {
			tmp[index++] = a[begin1++];
		}
		else {
			tmp[index++] = a[begin2++];
		}
	}
	while (begin1 <= end1) {
		tmp[index++] = a[begin1++];
	}
	while (begin2 <= end2) {
		tmp[index++] = a[begin2++];
	}
	for (int i = left; i <= right; i++) {
		a[i] = tmp[i];
	}

}

void MergeSort(int* a, int n) {
	int* tmp = (int*)malloc(sizeof(int) * n);
	_MergeSort(a, 0, n-1, tmp);
}

void PrintArray(int* a, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

void TestMergeSortNonR() {
	int a[] = { 3,5,2,7,8,6,1,9,4,0 };
	int size = sizeof(a) / sizeof(int);
	MergeSortNonR(a, size);
	PrintArray(a, size);
}
void TestMergeSort() {
	int a[] = { 3,5,2,7,8,6,1,9,4,0 };
	int size = sizeof(a) / sizeof(int);
	MergeSort(a, size);
	PrintArray(a, size);
}

int main() {
	//TestMergeSortNonR();
	TestMergeSort();
	return 0;
}