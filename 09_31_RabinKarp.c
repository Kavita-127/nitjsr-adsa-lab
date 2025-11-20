#include <stdio.h>
#include <string.h>

#define d 256

void search(char pat[], char txt[], int q) {
    int M = strlen(pat); // Length of the pattern
    int N = strlen(txt); // Length of the text
    int i, j;
    int p = 0; // Hash value for the pattern
    int t = 0; // Hash value for the current window of text
    int h = 1; // Used for calculating the highest power of d (d^(M-1) % q)

    // Calculate h = pow(d, M-1) % q
    for (i = 0; i < M - 1; i++) {
        h = (h * d) % q;
    }

    // Calculate the hash value of the pattern and the first window of text
    for (i = 0; i < M; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    // Slide the pattern over the text one by one
    for (i = 0; i <= N - M; i++) {
        // If the hash values match, then there's a potential match.
        // We then perform a character-by-character check to confirm (to handle hash collisions).
        if (p == t) {
            /* Check for characters one by one */
            for (j = 0; j < M; j++) {
                if (txt[i + j] != pat[j]) {
                    break; // Mismatch found, not a true match
                }
            }

            // If all characters matched, then the pattern is found
            if (j == M) {
                printf("Pattern found at index %d \n", i);
            }
        }

        // Calculate hash value for the next window of text:
        // Remove the leading digit, add the trailing digit using a rolling hash
        if (i < N - M) {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;

            // Ensure t remains positive (modulo results can be negative in C for negative dividends)
            if (t < 0) {
                t = (t + q);
            }
        }
    }
}

/* Driver Code */
int main() {
    char txt[] = "ABVERTKAVITAXYZ";
    char pat[] = "KAVITA";
    
    // A prime number, chosen to minimize collisions
    int q = 101; 

    // Function call to search for the pattern
    search(pat, txt, q);

    return 0;
}