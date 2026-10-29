#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include"euler-func.h"
long long phi_efficient(long long n) {
    if (n <= 0) return 0;
    long long result = n;
    for (long long p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            result = result / p * (p - 1);
            while (n % p == 0) {
                n /= p;
            }
        }
    }
    if (n > 1) {
        result = result / n * (n - 1);
    }
    return result;
}
