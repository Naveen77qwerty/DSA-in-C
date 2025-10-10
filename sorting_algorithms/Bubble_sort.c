#include <stdbool.h>
#include <stdio.h>

void print(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}
int bubble_sort(int arr[], int size) {
  bool swapped;
  for (int i = 0; i < size - 1; i++) {
    swapped = false;
    for (int j = 0; j < size - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
        swapped = true;
      }
    }
    if (!swapped) {
      break;
    }
  }
  print(arr, size);
  return 0;
}
// Bubble Sort is a simple comparison-based algorithm where adjacent elements in the array are repeatedly compared and
// swapped if they are in the wrong order. This process continues for each element in the array, moving the largest unsorted
// element to its correct position at the end in each pass, much like bubbles rising to the surface.
// The algorithm repeats these passes until no more swaps are needed, indicating that the array is fully sorted.
// Although easy to implement, Bubble Sort is inefficient for large arrays due to its O(n^2) time complexity.

int main() {
  int arr[] = {12, 87, 54, 21, 58, 45, 32, 90, 11, 67};
  int size = sizeof(arr) / sizeof(arr[0]);
  bubble_sort(arr, size);
  return 0;
}