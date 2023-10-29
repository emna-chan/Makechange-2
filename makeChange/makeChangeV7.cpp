#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <unordered_map>

using namespace std;

int minCoins(int coins[], int m, int V, unordered_map<int, int> &memo,
             int &best_cost) {
  if (V == 0)
    return 0;

  if (memo.find(V) != memo.end())
    return memo[V];

  int res = INT_MAX;

  for (int i = 0; i < m; i++) {
    if (coins[i] <= V) {
      int sub_res = minCoins(coins, m, V - coins[i], memo, best_cost);

      if (sub_res != INT_MAX && sub_res + 1 < res) {
        res = sub_res + 1;
      }

      // Cut implementation
      if (res < best_cost) {
        best_cost = res;
      } else if (res >= best_cost) {
        break;
      }
    }
  }

  return memo[V] = res;
}

int main() {
  int coins[] = {9, 6, 5, 1};
  int m = sizeof(coins) / sizeof(coins[0]);
  int V = 11;
  unordered_map<int, int> memo;
  int best_cost = INT_MAX;

  int result = minCoins(coins, m, V, memo, best_cost);
  cout << "Minimum coins required is " << result << endl;

  // Write result to a txt file
  ofstream outputFile("result.txt");
  outputFile << "Minimum coins required is " << result;
  outputFile.close();

  return 0;
}
