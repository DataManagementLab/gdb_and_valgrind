#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 128 MB working set
#define NUM_NODES (128 * 1024 * 1024 / sizeof(struct Node))
#define TRAVERSAL_STEPS 50000000 

struct Node {
    struct Node *next;
    // Padding to 64 bytes to match cache line size
    long long pad[7]; 
};

int main() {
    printf("Allocating nodes...\n");
    struct Node *pool = (struct Node *)malloc(NUM_NODES * sizeof(struct Node));
    int *indices = (int *)malloc(NUM_NODES * sizeof(int));
    
    if (!pool || !indices) return 1;

    // 1. Initialize indices
    for (int i = 0; i < NUM_NODES; i++) {
        indices[i] = i;
    }

    // 2. Shuffle
    printf("Shuffling memory pattern...\n");
    srand(time(NULL));
    for (int i = NUM_NODES - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    // 3. Link nodes
    for (int i = 0; i < NUM_NODES - 1; i++) {
        pool[indices[i]].next = &pool[indices[i+1]];
    }
    pool[indices[NUM_NODES - 1]].next = &pool[indices[0]];

    // --- FIX IS HERE ---
    // Capture the starting node BEFORE freeing the indices array
    struct Node *current = &pool[indices[0]];
    
    // Now it is safe to free indices
    free(indices);
    // -------------------

    printf("Starting traversal...\n");
    
    // THE HOT LOOP
    for (int i = 0; i < TRAVERSAL_STEPS; i++) {
        current = current->next;
        __asm__ volatile("" : "+r" (current));
    }

    printf("Done. Final node address: %p\n", (void*)current);
    free(pool);
    return 0;
}
