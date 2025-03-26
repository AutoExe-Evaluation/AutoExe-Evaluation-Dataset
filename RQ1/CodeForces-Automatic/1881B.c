#include <stdio.h>
#include <set>
#include <assert.h>

int main() {
    int TC = 1;
    scanf("%d", &TC);
    assert(TC >= 1 && TC <= 10000); // PRE: Number of test cases in range

    while (TC--) {
        std::multiset<int> st;
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        assert(a >= 1 && a <= 1000000000); // PRE: Length a in range
        assert(b >= 1 && b <= 1000000000); // PRE: Length b in range
        assert(c >= 1 && c <= 1000000000); // PRE: Length c in range
        
        st.insert(a);
        st.insert(b);
        st.insert(c);

        for (int i = 0; i < 3 && *st.begin() != *st.rbegin(); ++i) {
            st.insert(*st.begin());
            st.insert(*--st.end() - *st.begin());
            st.erase(--st.end());
        }

        if (*st.begin() == *st.rbegin()) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }

        assert(*st.begin() == *st.rbegin() || TC == 0); // POST: All threadlets can be equal or test case exhausted
    }
    return 0;
}