#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

long long score(long long* path, long long pathSize, long long k) {
    long long sum = 0, mx = 0, cur;
    for(long long i = 0; i < pathSize; ++i) {
        if(k < i + 1) break;
        cur = sum + path[i] * (k - i);
        if(cur > mx) mx = cur;
        sum += path[i];
    }
    return mx;
}

void find(long long* p, long long* a, long long** path, long long* pathSize, long long pos) {
    bool* vis = (bool*)calloc(*pathSize, sizeof(bool));
    *path = (long long*)malloc((*pathSize) * sizeof(long long));
    long long size = 0;

    while(!vis[pos - 1]) {
        vis[pos - 1] = 1;
        (*path)[size++] = a[pos - 1];
        pos = p[pos - 1];
    }
    *pathSize = size;
    free(vis);
}

int main() {
    int TCS;
    scanf("%d", &TCS);
    assert(TCS >= 1 && TCS <= 10000); // PRE: Number of test cases is within bounds

    for(int TC = 1; TC <= TCS; ++TC) {
        long long n, k, pb, ps;
        scanf("%lld %lld %lld %lld", &n, &k, &pb, &ps);
        assert(n >= 1 && n <= 200000); // PRE: n is within bounds
        assert(k >= 1 && k <= 1000000000); // PRE: k is within bounds
        assert(pb >= 1 && pb <= n); // PRE: PB is a valid position
        assert(ps >= 1 && ps <= n); // PRE: PS is a valid position

        long long* p = (long long*)malloc(n * sizeof(long long));
        long long* a = (long long*)malloc(n * sizeof(long long));

        for(long long i = 0; i < n; i++) scanf("%lld", &p[i]);
        for(long long i = 0; i < n; i++) scanf("%lld", &a[i]);
        
        long long* pathB;
        long long* pathS;
        long long pathBSize = n;
        long long pathSSize = n;

        find(p, a, &pathB, &pathBSize, pb);
        find(p, a, &pathS, &pathSSize, ps);
        
        long long bs = score(pathB, pathBSize, k);
        long long ss = score(pathS, pathSSize, k);
        
        if(bs == ss) printf("Draw\n");
        else if(bs > ss) printf("Bodya\n");
        else printf("Sasha\n");

        free(p);
        free(a);
        free(pathB);
        free(pathS);
    }
    
    return 0;
} // POST: The outputs are correct based on the calculated scores of Bodya and Sasha.