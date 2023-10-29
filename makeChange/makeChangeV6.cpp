#include <chrono>
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
using namespace std::chrono;

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

int evaluateCost(const vector<int> &counts) {
  int cost = 0;
  for (auto count : counts) {
    cost += count;
  }
  return cost;
}

int main() {
  vector<double> coins = {5, 2, 1, 0.5, 0.2, 0.1, 0.05};
  double amount = 12.35;
  ofstream outfile("CORRECT_SolutionsWhichImproveIncrementally.txt");
  int totalCents = static_cast<int>(amount * 100);

  vector<int> bestSolution;
  int bestCost = INT_MAX;

  auto start = high_resolution_clock::now();

  vector<int> maxCounts;
  for (const auto &coin : coins) {
    maxCounts.push_back(static_cast<int>(totalCents / (coin * 100)));
  }

  vector<int> counts(coins.size(), 0);
  while (true) {
    int sum = 0;
    for (int i = 0; i < coins.size(); ++i) {
      sum += static_cast<int>(counts[i] * coins[i] * 100);
    }

    if (sum == totalCents) {
      int currentCost = evaluateCost(counts);
      if (currentCost < bestCost) {
        bestCost = currentCost;
        bestSolution = counts;
        outfile << bestSolution << " with cost: " << bestCost << endl;
      }
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

    if (index < 0)
      break;
  }

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "Time taken: " << duration.count() << " microseconds" << endl;

  // Display the best solution on the console
  cout << "Best Solution: " << bestSolution << " with cost: " << bestCost << endl;

  outfile.close();
  return 0;
}
