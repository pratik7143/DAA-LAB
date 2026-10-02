#include <stdio.h>
// Compact struct definition
struct Node {
    char ch;
    int freq, left, right, parent, active;
} t[11]; // Global array (automatically initializes integers to 0)
int main() {
    char chars[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freqs[] = {45, 13, 12, 16, 9, 5};
    // 1. Setup the array (Leaves 0-5 get data, all get parent/left/right = -1)
    for (int i = 0; i < 11; i++) {
        t[i].left = t[i].right = t[i].parent = -1;
        if (i < 6) {
            t[i].ch = chars[i];
            t[i].freq = freqs[i];
            t[i].active = 1; 
        }
    }
    // 2. Build the Tree (Merge 6 leaves into 1 root -> 5 merges needed)
    for (int i = 6; i < 11; i++) {
        int m1 = -1, m2 = -1;
        // Find the two smallest active frequencies
        for (int j = 0; j < i; j++) {
            if (t[j].active) {
                if (m1 == -1 || t[j].freq < t[m1].freq) {
                    m2 = m1; m1 = j;
                } else if (m2 == -1 || t[j].freq < t[m2].freq) {
                    m2 = j;
                }
            }
        }
        // Merge the two smallest into the new node 'i'
        t[i].freq = t[m1].freq + t[m2].freq;
        t[i].left = m1;
        t[i].right = m2;
        t[i].active = 1;

        // Link children to parent and deactivate them
        t[m1].parent = t[m2].parent = i;
        t[m1].active = t[m2].active = 0;
    }
    // 3. Print the Codes
    printf("Char | Freq | Code\n------------------\n");
    for (int i = 0; i < 6; i++) {
        int code[20], len = 0, curr = i;
        // Trace from leaf up to the root
        while (t[curr].parent != -1) {
            int p = t[curr].parent;
            // If current is left child, bit is 0. Else 1.
            code[len++] = (t[p].left == curr) ? 0 : 1; 
            curr = p;
        }
        printf("  %c  |  %2d  | ", t[i].ch, t[i].freq);
        // Print the path in reverse (root to leaf)
        for (int j = len - 1; j >= 0; j--) {
            printf("%d", code[j]);
        }
        printf("\n");
    }
    return 0;
}