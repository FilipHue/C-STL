#include "memory_utils.h"

void* safe_calloc(size_t nmemb, size_t size, unsigned int line) {
    void* ptr = calloc(nmemb, size);
    if (ptr == NULL) {
        fprintf(stderr, "[%s:%u] Out of memory (%ld bytes)\n", __FILE__, line, nmemb * size);
        exit(EXIT_FAILURE);
    }
    return ptr;
}