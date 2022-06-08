#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

// TODO: rewrite memmove to not allocate anything

typedef unsigned char byte;

void *memcpy(void *restrict s1, const void *restrict s2, size_t n) {
    const byte *restrict c2 = s2;
    byte *restrict c1 = s1;

    while (n--) {
        *c1++ = *c2++;
    }
    return s1;
}

void *memmove(void *s1, const void *s2, size_t n) {
    void *buffer = malloc(n);
    memcpy(buffer, s2, n);
    memcpy(s1, buffer, n);
    free(buffer);
    return s1;
}

char *strcpy(char *restrict s1, const char *restrict s2) {
    while(*s2 != 0) {
        *s1++ = *s2++;
    }
    *s1 = 0;
    return s1;
}

char *strncpy(char *restrict s1, const char *restrict s2, size_t n) {
    size_t i = 0;
    for(; i < n && *s2 != 0; ++ i) {
        *s1++ = *s2++;
    }
    for(; i < n; ++i) {
        *s1++ = 0;
    }
    return s1;
}


char *strcat(char *restrict s1, const char *restrict s2) {
    size_t start = strlen(s1);
    return strcpy(s1+start, s2);
}

char *strncat(char *restrict s1, const char *restrict s2, size_t n) {
    size_t start = strlen(s1);
    strncpy(s1+start, s2, n);
    return s1;
}


int memcmp(const void *s1, const void *s2, size_t n) {
    const byte *u1 = s1;
    const byte *u2 = s2;
    for (; n--; u1++, u2++) {
        if (*u1 != *u2) return *u1 - *u2;
    }
    return 0;
}

void *memset(void *s, int c, size_t n) {
    byte *restrict buf = s;
    while (n--) {
        *buf++ = c;
    }
    return s;
}

int strcmp(const char *s1, const char *s2) {
    int diff;
    do {
        diff = *s1 - *s2;
    } while(diff != 0 && *s1 != 0 && *s2 != 0);
    return diff;
}

int strncmp(const char *s1, const char *s2, size_t n) {
    int diff = 0;
    size_t i = 0;
    if(n != 0) do {
        diff = *s1 - *s2;
    } while(++i < n && diff != 0 && *s1 != 0 && *s2 != 0);
    return diff;
}

int strcoll(const char *s1, const char *s2) {
    return strcmp(s1, s2);
}

// TODO: I don't quite understand the intent nor use behind this function
// so I'm just going to ignore locales for now.
size_t strxfrm(char *restrict s1, const char *restrict s2, size_t n) {
    size_t len = strlen(s2);
    if(s1 != NULL && n != 0) {
        for(size_t i = 0; i != n; ++i) {
            *s1 = *s2;
        }
    }
    return len;
}

void *memchr(const void *ptr, int c, size_t n) {
    const char *s = ptr;
    for(size_t i = 0; i != n; ++i) {
        if(s[i] == c) {
            // Casting away const because clang warnings
            return (void *)(s+i);
        }
    }
    return NULL;
}

char *strchr(const char *s, int c) {
    do {
        if(*s == c) return (char *)s;
    } while(*s++);
    return NULL;
}

size_t strspn(const char *s1, const char *s2) {
    size_t i = 0;
    for(; *s1; ++s1) {
        if(strchr(s2, *s1) == NULL) {
            break;
        }
        ++i;
    }
    return i;
}

size_t strcspn(const char *s1, const char *s2) {
    size_t i = 0;
    for(; *s1; ++s1) {
        if(strchr(s2, *s1) != NULL) {
            break;
        }
        ++i;
    }
    return i;
}

char *strpbrk(const char *s1, const char *s2) {
    while(*s1) {
        if(strchr(s2, *s1) == NULL) {
            break;
        }
        ++s1;
    }
    return (char *)s1;
}

char *strrchr(const char *s, int c) {
    char const *last = NULL;
    for(; *s != 0; ++s) {
        if(*s == c) last = s;
    }
    return (char *)last;
}

char *strstr(const char *s1, const char *s2) {
    if(*s2 == 0) return (char *)s1;
    size_t len = strlen(s2);
    for(; *s1 != 0; ++s1) {
        if(strncmp(s1, s2, len) == 0) return (char *)s1;
    }
    return NULL;
}

// TODO: there may be restrict-related UB
char *strtok(char *restrict s1, const char *restrict s2) {
    static char *restrict str;
    if(s1 != NULL) str = s1;
    if(str == NULL) return NULL;

    size_t junk_len = strspn(str, s2);
    char *tok_start = str+junk_len;
    if(*tok_start == 0) {
        str = NULL;
        return NULL;
    }

    size_t tok_len = strcspn(str, s2);

    char *tok_end = tok_start + tok_len;
    *tok_end = 0;
    str = tok_end+1;

    return tok_start;
}


char *strerror(int errnum) {
    switch(errnum) {
        case 0:      return "No errors";
        case EDOM:   return "Value is out of domain of the function";
        case EILSEQ: return "Illegal byte sequence";
        case ERANGE: return "Value is out of range";
    }
    return "Unkown error";
}

size_t strlen(const char *s) {
    size_t i = 0;
    while (s[i]) {
        i++;
    }
    return i;
}

size_t strnlen_s(const char *s, size_t maxsize) {
    if (s == NULL) return 0;
    size_t i = 0;
    while (s[i] && i < maxsize) {
        i++;
    }
    return i;
}
