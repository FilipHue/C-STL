#ifndef MEMORY_UTILS_H
#define MEMORY_UTILS_H

#include <stdio.h>
#include <stdlib.h>

static void* safe_calloc(size_t nmemb, size_t size, unsigned int line) {
    void* ptr = calloc(nmemb, size);
    if (ptr == NULL) {
        fprintf(stderr, "[%s:%ul]Out of memory(%ld bytes)\n",
                __FILE__, line, nmemb * size);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

#define SAFE_CALLOC(nmemb, size) safe_calloc(nmemb, size, __LINE__);

#endif // MEMORY_UTILS_H
