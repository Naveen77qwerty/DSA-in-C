#include <stdio.h>
void print(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}
int selection_sort(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    int min_index = i;
    for (int j = i + 1; j < size; j++) {
      if (arr[j] < arr[min_index]) {
        min_index = j;
      }
    }
    int temp = arr[i];
    arr[i] = arr[min_index];
    arr[min_index] = temp;
  }
  print(arr, size);
  return 0;
}
// Selection Sort repeatedly finds the minimum (or maximum) element from the unsorted portion of the array and swaps it with the first element of that portion.
// This gradually builds the sorted array from left to right.
// Unlike Bubble Sort, Selection Sort minimizes the number of swaps,
// but it still has to scan the entire unsorted portion for each element, giving it a time complexity of
// O(n^2).It is easy to understand and implement but generally less efficient than more advanced algorithms for large datasets.

int main() {
  int arr[] = {12, 87, 54, 21, 58, 45, 32, 90, 11, 67};
  int size = sizeof(arr) / sizeof(arr[0]);
  selection_sort(arr, size);
  return 0;
}