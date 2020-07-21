#ifndef _TRI_SYSTEM_ENV_H_
#define _TRI_SYSTEM_ENV_H_

#include <stdio.h>

#define PT_MAKE_STR(x)                { #x, PT_MAKE_STR_ESC(x) }
#define PT_MAKE_STR_ESC(x)        #x


typedef struct
{
	char const *name;
	char const *value;
} MACRO_T;


/* Compilers */
const MACRO_T g_compilers[] =
{
#ifdef __INTEL_COMPILER        /* Interl C++ */
		PT_MAKE_STR(__INTEL_COMPILER),
#endif

#ifdef _MSC_VER                        /* Visual C++ */
		PT_MAKE_STR(_MSC_VER),
#endif

#ifdef __GNUC__                        /* GCC */
		PT_MAKE_STR(__GNUC__),
#endif

#ifdef __DMC__                        /* DMC++ */
		PT_MAKE_STR(__DMC__),
#endif

#ifdef __ARMCC_VERSION        /* ARM C/C++ */
		PT_MAKE_STR(__ARMCC_VERSION),
#endif
};


/* Operation system */
const MACRO_T g_platforms[] =
{
#ifdef _WIN32                        /* Windows 32 or Windows 64 */
		PT_MAKE_STR(_WIN32),
#endif

#ifdef _WIN64                        /* Windows 64 */
		PT_MAKE_STR(_WIN64),
#endif

#ifdef __MINGW32__                /* Windows32 by mingw compiler */
		PT_MAKE_STR(__MINGW32__),
#endif

#ifdef __CYGWIN__                /* Cygwin */
		PT_MAKE_STR(__CYGWIN__),
#endif

#ifdef __linux__                /* linux */
		PT_MAKE_STR(__linux__),
#endif

#ifdef __FreeBSD__                /* FreeBSD */
		PT_MAKE_STR(__FreeBSD__),
#endif

#ifdef __NetBSD__                /* NetBSD */
		PT_MAKE_STR(__NetBSD__),
#endif

#ifdef __OpenBSD__                /* OpenBSD */
		PT_MAKE_STR(__OpenBSD__),
#endif

#ifdef __sun__                /* Sun OS */
		PT_MAKE_STR(__sun__),
#endif

#ifdef __unix__                        /* unix */
		PT_MAKE_STR(__unix__),
#endif

#ifdef __APPLE__                /* Apple, MaxOSX may failed */
		PT_MAKE_STR(__APPLE__),
#endif
};


/* Other useful */
const MACRO_T g_others[] =
{
#ifdef __DATE__ 
		PT_MAKE_STR(__DATE__),
#endif

#ifdef __TIME__ 
		PT_MAKE_STR(__TIME__),
#endif

#ifdef _BSD_SOURCE
		PT_MAKE_STR(_BSD_SOURCE),
#endif

#ifdef _POSIX_SOURCE
		PT_MAKE_STR(_POSIX_SOURCE),
#endif

#ifdef _XOPEN_SOURCE
		PT_MAKE_STR(_XOPEN_SOURCE),
#endif

#ifdef _GNU_SOURCE
		PT_MAKE_STR(_GNU_SOURCE),
#endif

#ifdef __GNUC_MINOR__
		PT_MAKE_STR(__GNUC_MINOR__),
#endif

#ifdef __VERSION__
		PT_MAKE_STR(__VERSION__),
#endif

#ifdef __unix
		PT_MAKE_STR(__unix),
#endif
};

#endif