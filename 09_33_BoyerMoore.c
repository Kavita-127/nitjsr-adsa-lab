/* SET-9
   Q33. Implement Boyer-Moore string matching Algorithm.
*/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define ALPHABET 256

void buildBadChar(const char *pat, int m, int badChar[]) {
    for (int i = 0; i < ALPHABET; i++)
        badChar[i] = -1;

    for (int i = 0; i < m; i++)
        badChar[(unsigned char)pat[i]] = i;
}

void buildGoodSuffix(const char *pat, int m, int *suffix, int *goodSuffix) {
    int i = m - 1, j = m;

    suffix[m - 1] = m;
    
    for (int i = m - 2; i >= 0; i--) {
        j = i;
        while (j >= 0 && pat[j] == pat[m - 1 - (i - j)])
            j--;
        suffix[i] = i - j;
    }

    for (int i = 0; i < m; i++)
        goodSuffix[i] = m;

    int t = m - 1;
    for (int i = m - 1; i >= 0; i--)
        if (suffix[i] == i + 1)
            for (; t < m - 1 - i; t++)
                if (goodSuffix[t] == m)
                    goodSuffix[t] = m - 1 - i;

    for (int i = 0; i <= m - 2; i++)
        goodSuffix[m - 1 - suffix[i]] = m - 1 - i;
}

// Boyer–Moore search
void boyerMoore(const char *text, const char *pat) {
    int n = strlen(text);
    int m = strlen(pat);

    if (m == 0 || m > n)
        return;

    int badChar[ALPHABET];
    int *suffix = (int *)malloc(m * sizeof(int));
    int *goodSuffix = (int *)malloc(m * sizeof(int));

    buildBadChar(pat, m, badChar);
    buildGoodSuffix(pat, m, suffix, goodSuffix);

    int s = 0; // shift of the pattern

    while (s <= n - m) {
        int j = m - 1;

        // Match from right to left
        while (j >= 0 && pat[j] == text[s + j])
            j--;

        if (j < 0) {
            printf("Pattern found at index %d\n", s);
            s += goodSuffix[0];
        } else {
            int badCharShift = j - badChar[(unsigned char)text[s + j]];
            int goodSuffixShift = goodSuffix[j];
            s += (badCharShift > goodSuffixShift ? badCharShift : goodSuffixShift);
        }
    }

    free(suffix);
    free(goodSuffix);
}

int main() {
    const char *text = "ABAAABCDBBABCDDEBCABC";
    const char *pattern = "ABC";

    boyerMoore(text, pattern);
    return 0;
}

