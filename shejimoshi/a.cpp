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

    // ѡ���׼ֵ������ѡ��һ��Ԫ�أ�
    pivot = array[left];
    pivot_index = left;

    // �ָ�����
    while (left < right && array[left] <= pivot) {
        left++;
    }

    // ����׼���뵽��ȷλ�ã���ָ��λ�ã�
    swap(&array[pivot], &array[right]);
    pivot = array[right];
    right--;

    // �ݹ������������ʣ�ಿ��
    quicksort(array, left, pivot_index);
    quicksort(array, pivot_index + 1, right);
}

int main() {
    int array[] = {3, 6, 8, 4, 9, 1, 10};
    int n = sizeof(array) / sizeof(array[0]);

    printf("ԭ���飺");
    for (int i = 0; i < n; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");

    quicksort(array, 0, n - 1);

    printf("���������Ϊ��");
    for (int i = 0; i < n; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
    printf("aaaaa\n");

    return 0;
}