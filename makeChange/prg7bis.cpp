#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <chrono>

static int recursive_calls = 0;

int makeChange(std::vector<int>& coins, int amount, std::vector<int>& memo, int best_cost) {
    recursive_calls++;

    if (amount == 0) return 0;

    if (memo[amount] != -1) return memo[amount];

    int min_coins = INT_MAX;

    for (int coin : coins) {
        if (amount - coin < 0) continue;

        int res = makeChange(coins, amount - coin, memo, best_cost);

        if (res < best_cost) {
            min_coins = std::min(min_coins, res + 1);
            best_cost = std::min(best_cost, min_coins);
        }
    }

    memo[amount] = (min_coins == INT_MAX) ? -1 : min_coins;

    return memo[amount];
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> coins = {1, 2, 5};
    int amount = 11;
    std::vector<int> memo(amount + 1, -1);

    int best_cost = INT_MAX;
    int result = makeChange(coins, amount, memo, best_cost);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Minimum coins required is " << result << std::endl;

    std::ofstream outputFile("results.txt");
    outputFile << "Minimum coins required is " << result << "\n";
    outputFile << "Time taken by function: " << duration.count() << " microseconds\n";
    outputFile << "Number of recursive calls: " << recursive_calls << "\n";
    outputFile.close();

    return 0;
}
