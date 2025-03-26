#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef long long ll;

typedef struct {
    ll first;
    ll second;
} pair_ll;

int cmp(const void *a, const void *b) {
    pair_ll *pa = (pair_ll *)a;
    pair_ll *pb = (pair_ll *)b;
    if (pa->first == pb->first) 
        return pb->second - pa->second;
    return pa->first - pb->first;
}

int main() {
    char s[500001];
    scanf("%s", s);
    
    // PRE: The input string s is a non-empty balanced parentheses sequence
    assert(strlen(s) > 0);
    
    ll ct = 0;
    ll len = strlen(s);
    pair_ll *v = (pair_ll *)malloc(len * sizeof(pair_ll));
    
    for (ll i = 0; i < len; ++i) {
        v[i].first = ct;
        v[i].second = i;
        if (s[i] == '(') ct++;
        else ct--;
    }
    
    qsort(v, len, sizeof(pair_ll), cmp);
    
    for (ll i = 0; i < len; ++i) 
        printf("%c", s[v[i].second]);
    printf("\n");
    
    // POST: The output is the balanced shuffle of the input parentheses sequence
    assert(ct == 0); // Ensure the final balance is 0 for a balanced sequence

    free(v);
    return 0;
}