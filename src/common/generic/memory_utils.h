#ifndef MEMORY_UTILS_H
#define MEMORY_UTILS_H

#include <stdio.h>
#include <stdlib.h>

void* safe_calloc(size_t nmemb, size_t size, unsigned int line);

#define SAFE_CALLOC(nmemb, size) safe_calloc(nmemb, size, __LINE__);

#endif // MEMORY_UTILS_H
