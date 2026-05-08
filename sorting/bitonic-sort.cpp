#include <algorithm>
#include <iostream>
#include <vector>

void compAndSwap(std::vector<int>& arr, int i, int j, bool ascending) {
  if (ascending == (arr[i] > arr[j])) {
    std::swap(arr[i], arr[j]);
  }
}

void bitonicMerge(std::vector<int>& arr, int lo, int cnt, bool ascending) {
  if (cnt > 1) {
    int k = cnt / 2;
    for (int i = lo; i < lo + k; i++) {
      compAndSwap(arr, i, i + k, ascending);
    }
    bitonicMerge(arr, lo, k, ascending);
    bitonicMerge(arr, lo + k, k, ascending);
  }
}

void bitonicSort(std::vector<int>& arr, int lo, int cnt, bool ascending) {
  if (cnt > 1) {
    int k = cnt / 2;
    bitonicSort(arr, lo, k, true);
    bitonicSort(arr, lo + k, k, false);
    bitonicMerge(arr, lo, cnt, ascending);
  }
}

void bitonicSort(std::vector<int>& arr, bool ascending = true) {
  int n = arr.size();
  if (n == 0 || (n & (n - 1)) != 0) {
    throw std::invalid_argument("Array size must be a power of 2 (got " +
                                std::to_string(n) + ")");
  }
  bitonicSort(arr, 0, n, ascending);
}

void printArray(const std::vector<int>& arr, const std::string& label = "") {
  if (!label.empty()) std::cout << label << ": ";
  std::cout << "[ ";
  for (int x : arr) std::cout << x << " ";
  std::cout << "]\n";
}

int main() {
  std::vector<int> a = {3, 7, 4, 8, 6, 2, 1, 5};
  printArray(a, "Input     ");
  bitonicSort(a, true);
  printArray(a, "Ascending ");

  std::vector<int> b = {10, 30, 11, 20, 4, 330, 21, 110};
  printArray(b, "\nInput     ");
  bitonicSort(b, false);
  printArray(b, "Descending");

  std::vector<int> c = {1, 2, 3, 4, 5, 6, 7, 8};
  printArray(c, "\nInput     ");
  bitonicSort(c, true);
  printArray(c, "Ascending ");

  return 0;
}

