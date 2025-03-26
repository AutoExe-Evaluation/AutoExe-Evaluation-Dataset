#include <stdio.h>
#include <assert.h>

int main() {
    int t;
    scanf("%d", &t);
    assert(t >= 1 && t <= 1439); // PRE: 1 ≤ t ≤ 1439
    
    for (int i = 0; i < t; ++i) {
        int h, m;
        scanf("%d %d", &h, &m);
        assert(h >= 0 && h < 24); // PRE: 0 ≤ h < 24
        assert(m >= 0 && m < 60); // PRE: 0 ≤ m < 60
        
        long long minutes_before_new_year = (23 - h) * 60 + (60 - m);
        printf("%lld\n", minutes_before_new_year);
        assert(minutes_before_new_year >= 1 && minutes_before_new_year <= 1439); // POST: 1 ≤ minutes_before_new_year ≤ 1439
    }
    
    return 0;
}