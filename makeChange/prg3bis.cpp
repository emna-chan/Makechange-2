#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

ostream &operator<<(ostream &os, const vector<int> &coins) {
  os << "{ ";
  for (int i = 0; i < coins.size(); ++i) {
    os << coins[i];
    if (i < coins.size() - 1)
      os << ", ";
  }
  os << " }";
  return os;
}

void findCombinations(double amount, const vector<double> &coins,
                      ofstream &outfile) {
  int totalCents = static_cast<int>(amount * 100);
  vector<int> maxCounts;
  for (const auto &coin : coins) {
    maxCounts.push_back(static_cast<int>(totalCents / (coin * 100)));
  }

  // Initialize counts with maxCounts to start with the maximum units.
  vector<int> counts = maxCounts;

  while (true) {
    int sum = 0;
    for (int i = 0; i < coins.size(); ++i) {
      sum += static_cast<int>(counts[i] * coins[i] * 100);
    }

    if (sum == totalCents) {
      outfile << counts << endl;
    }

    int index = coins.size() - 1;
    while (index >= 0) {
      // Decrement the counts this time instead of incrementing.
      if (--counts[index] < 0) {
        counts[index] = maxCounts[index];
        --index;
      } else {
        break;
      }
    }

    if (index < 0)
      break;
  }
}

int main() {
  vector<double> coins = {5, 2, 1, 0.5, 0.2, 0.1, 0.05};
  double amount = 12.35;
  ofstream outfile("AllSolutionsTest1_Reversed.txt");
  findCombinations(amount, coins, outfile);
  outfile.close();
  return 0;
}
