#include <stdio.h>
void print(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}
int insertion_sort(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    int key = arr[i];
    int j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
  print(arr, size);
  return 0;
}
// Insertion Sort builds a sorted portion of the array one element at a time.
// Starting from the second element, each element is compared with the elements in the sorted portion and
// inserted into its correct position by shifting larger elements to the right.
// This process continues until all elements are correctly placed.
// Insertion Sort is efficient for small arrays or nearly sorted arrays and works in-place,
// maintaining stability. Its average and worst-case time complexity is
// O(n^2), but it performs well on partially sorted data.

int main() {
  int arr[] = {12, 87, 54, 21, 58, 45, 32, 90, 11, 67};
  int size = sizeof(arr) / sizeof(arr[0]);
  insertion_sort(arr, size);
  return 0;
}