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
}
