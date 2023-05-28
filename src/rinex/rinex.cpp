#include "rinex.h"

namespace rinex {


    void setstr(char *dst, const char *src, int n) {
        char *p = dst;
        const char *q = src;
        while (*q && q < src + n) *p++ = *q++;
        *p-- = '\0';
        while (p >= dst && *p == ' ') *p-- = '\0';
    }
}

namespace rinex {}