#include <chrono>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

ostream& operator<<(ostream& os, const vector<int>& coins) {
    os << "{ ";
    for (int i = 0; i < coins.size(); ++i) {
        os << coins[i];
        if (i < coins.size() - 1) os << ", ";
    }
    os << " }";
    return os;
}

void findCombinations(double amount, const vector<double>& coins) {
    int totalCents = static_cast<int>(amount * 100);
    vector<int> maxCounts;
    for (const auto& coin : coins) {
        maxCounts.push_back(static_cast<int>(totalCents / (coin * 100)));
    }

    vector<int> counts(coins.size(), 0);
    while (true) {
        int sum = 0;
        for (int i = 0; i < coins.size(); ++i) {
            sum += static_cast<int>(counts[i] * coins[i] * 100);
        }

        if (sum == totalCents) {
            cout << counts << endl;
        }

        int index = coins.size() - 1;
        while (index >= 0) {
            if (++counts[index] > maxCounts[index]) {
                counts[index] = 0;
                --index;
            } else {
                break;
            }
        }

        if (index < 0) break;
    }
}

int main() {
  
  // Measure execution time
  auto start = chrono::high_resolution_clock::now();
  
    vector<double> coins = {5, 2, 1, 0.5, 0.2, 0.1, 0.05};
    double amount = 12.35;
    findCombinations(amount, coins);
    
  auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
  cout << "Time taken by function: " << duration.count() << " microseconds"
       << endl;
  
  return 0;
}
