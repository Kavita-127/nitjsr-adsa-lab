/*SET-9
  Q31. Implement Rabin Karp string matching Algorithm.
*/

#include <stdio.h>
#include <string.h>

#define d 256

void search(char pat[], char txt[], int q) {
    int M = strlen(pat); 
    int N = strlen(txt);
    int i, j;
    int p = 0; // Hash value for the pattern
    int t = 0; // Hash value for the current window of text
    int h = 1; // Used for calculating the highest power of d (d^(M-1) % q)

    // Calculate h = pow(d, M-1) % q
    for (i = 0; i < M - 1; i++) {
        h = (h * d) % q;
    }

    for (i = 0; i < M; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    for (i = 0; i <= N - M; i++) {
        if (p == t) {
            for (j = 0; j < M; j++) {
                if (txt[i + j] != pat[j]) {
                    break; 
                }
            }

            if (j == M) {
                printf("Pattern found at index %d \n", i);
            }
        }

        if (i < N - M) {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;

            if (t < 0) {
                t = (t + q);
            }
        }
    }
}

int main() {
    char txt[] = "ABVERTKAVITAXYZ";
    char pat[] = "KAVITA";
    
    // A prime number, chosen to minimize collisions
    int q = 101; 
    
    search(pat, txt, q);

    return 0;

}
