#include <chrono> 
#include <iostream>
#include <vector>

using namespace std;

void makeChange(double amount, const vector<double> &coins) {
  double remainingAmount = amount;
  vector<int> coinCounts(coins.size(), 0);

  for (size_t i = 0; i < coins.size(); ++i) {
    if (remainingAmount <= 0) {
      break;
    }

    coinCounts[i] = static_cast<int>(remainingAmount / coins[i]);
    remainingAmount = remainingAmount - (coins[i] * coinCounts[i]);
  }

  cout << "Change for " << amount << " euros is:" << endl;
  for (size_t i = 0; i < coins.size(); ++i) {
    if (coinCounts[i] > 0) {
      cout << coins[i] << " euros: " << coinCounts[i] << endl;
    }
  }
}

int main() {
  // Measure execution time
  auto start = chrono::high_resolution_clock::now();

  vector<double> coins = {5, 2, 1, 0.5, 0.2, 0.1, 0.05};
  double amount = 12.35;

  makeChange(amount, coins);

  auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
  cout << "Time taken by function: " << duration.count() << " microseconds"
       << endl;

  return 0;
}
