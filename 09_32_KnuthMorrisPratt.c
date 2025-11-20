/* SET-9
   Q32. Implement Knuth-Morris-Pratt string matching Algorithm.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Build LPS (Longest Prefix Suffix) array
void buildLPS(const char *pat, int m, int *lps) {
    int len = 0;   // length of previous longest prefix suffix
    lps[0] = 0;

    int i = 1;
    while (i < m) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1]; // reduce length of prefix
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP search
void KMP(const char *text, const char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);

    if (m > n) return;

    int *lps = (int *)malloc(m * sizeof(int));
    buildLPS(pattern, m, lps);

    int i = 0; // index for text
    int j = 0; // index for pattern

    while (i < n) {

        if (text[i] == pattern[j]) {
            i++;
            j++;
        }

        if (j == m) {
            printf("Pattern found at index %d\n", i - j);
            j = lps[j - 1];
        }

        else if (i < n && text[i] != pattern[j]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    free(lps);
}

int main() {
    const char *text = "ABABABCABABABCABABABC";
    const char *pattern = "ABABABC";

    KMP(text, pattern);

    return 0;
}

