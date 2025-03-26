#include <assert.h>
#include <klee/klee.h>

#define abs(x) ((x) < 0 ? -(x) : (x))

int maxProfit(int* prices, int pricesSize) {
    int i, d, k = 0;
    
    if (pricesSize < 2) return 0;
    
    // O(n)
    int cost = prices[0];
    for (i = 1; i < pricesSize; i ++) {
        if (prices[i] > cost) {
            d = prices[i] - cost;
            k = d > k ? d : k;
        } else {
            cost = prices[i];
        }
    }
    
    assert(k >= abs(prices[0] - prices[pricesSize - 1])); // POST
    return k;
}

#define SIZE 100

int main()
{
    int prices[SIZE];
    klee_make_symbolic(prices, sizeof(prices), "prices");
    maxProfit(prices, SIZE);
}
