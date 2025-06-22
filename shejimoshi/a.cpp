//
// Created by 86188 on 2025/2/21.
//

#include "a.h"
#include <cstdio>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quicksort(int *array, int left, int right) {
    int pivot_index;
    int pivot;

    // 选择基准值（这里选第一个元素）
    pivot = array[left];
    pivot_index = left;

    // 分割数组
    while (left < right && array[left] <= pivot) {
        left++;
    }

    // 将基准插入到正确位置（右指针位置）
    swap(&array[pivot], &array[right]);
    pivot = array[right];
    right--;

    // 递归排序子数组和剩余部分
    quicksort(array, left, pivot_index);
    quicksort(array, pivot_index + 1, right);
}

int main() {
    int array[] = {3, 6, 8, 4, 9, 1, 10};
    int n = sizeof(array) / sizeof(array[0]);

    printf("原数组：");
    for (int i = 0; i < n; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");

    quicksort(array, 0, n - 1);

    printf("排序后数组为：");
    for (int i = 0; i < n; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
    printf("aaaaa\n");

    return 0;
}