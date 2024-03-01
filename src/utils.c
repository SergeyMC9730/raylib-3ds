#include <raylib.h>

#include <stdlib.h>

RLAPI void TraceLog(int logLevel, const char *text, ...) {
    return;
}
RLAPI void SetTraceLogLevel(int logLevel) {
    return;
}

RLAPI void *MemAlloc(unsigned int size) {
    return RL_MALLOC(size);
}
RLAPI void *MemRealloc(void *ptr, unsigned int size) {
    return RL_REALLOC(ptr, size);
}
RLAPI void MemFree(void *ptr) {
    return RL_FREE(ptr);
}