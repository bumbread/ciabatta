
// Standard Headers
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fenv.h>
#include <inttypes.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#include <time.h>
#include <uchar.h>
#include <wchar.h>
#include <wctype.h>

// Intrinsics
#if !defined(__FMA__)
    #error "Get a better CPU (the kind that supports FMA) or enable -mfma"
#endif
// xmmintrin.h depends on mm_malloc.h, which itself includes other CRT headers
// Which introduces compiler errors. Actually does it really matter? I would
// need to check again
#undef __STDC_HOSTED__
#include <immintrin.h>
#include <xmmintrin.h>

#include "intrin.h"

// Dependencies
#include "fdec64/fdec64.h"
#include "unicope/inc/unicope.h"

// Platform-independent stuff
#include "fmt/gen_fmt.c"
#include "math/basic.c"
#include "math/division.c"
#include "math/gen_math.c"
#include "math/ieee754.c"
#include "math/round.c"
#include "stdlib/algorithm.c"
#include "stdlib/conversion.c"
#include "stdlib/multibyte.c"
#include "stdlib/random.c"
#include "ctype.c"
#include "errno.c"
#include "fenv.c"
#include "locale.c"
#include "string.c"
#include "uchar.c"
#include "wctype.c"

// Windows stuff
#if defined(CIABATTA_WIN)
    #include "_win/win.h"
    #include "_win/assert.c"
    #include "_win/environment.c"
    #include "_win/heap.c"
    #include "_win/signal.c"
    #include "_win/stdio.c"
    #include "_win/threads.c"
    #include "_win/time.c"
#endif
