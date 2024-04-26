#include <iostream>
#include <vector>

using namespace std;

class IntegersReader {
 private:
  std::vector<int> numbers;

 public:
  // Constructor that takes the number of integers (n) as an argument
  IntegersReader(int n) : numbers(n) {
    std::cout << "Enter " << n << " integers:" << std::endl;
    for (int i = 0; i < n; ++i) {
      std::cin >> numbers[i];
    }
  }

  // Function to display the integers
  void displayIntegers() {
    std::cout << "Integers read: ";
    for (int num : numbers) {
      std::cout << num << " ";
    }
    std::cout << numbers.size() << std::endl;
  }
};

int main() {
  int n;
  vector<int> nums;
  nums.reserve(5);
  cout << nums.size() << nums.empty();
}
