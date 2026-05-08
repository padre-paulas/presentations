#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

bool isSorted(const std::vector<int> &vec) {
  return std::is_sorted(vec.begin(), vec.end());
}

void shuffleVector(std::vector<int> &vec) {
  static std::random_device rd;
  static std::mt19937 g(rd());
  std::shuffle(vec.begin(), vec.end(), g);
}

void bogoSort(std::vector<int> &vec) {
  while (!isSorted(vec)) {
    shuffleVector(vec);
  }
}

int main() {
  std::vector<int> data = {5, 2, 9, 1, 3};

  bogoSort(data);

  for (int num : data) {
    std::cout << num << " ";
  }
  std::cout << std::endl;

  return 0;
}

