#ifndef _TRI_TYPE_DEFINE_H_
#define _TRI_TYPE_DEFINE_H_

#include <boost/cstdint.hpp>
#include <boost/cstdfloat.hpp>


/// some other types ///
typedef boost::int64_t      type_n;
typedef boost::int64_t      size_n;


/// long type pointer ///
typedef boost::intptr_t     ptr_n;


/// primitive data types ///
typedef boost::int8_t       bool_n;
typedef boost::int8_t       char_n;
typedef boost::uint8_t      byte_n;
typedef boost::int16_t      short_n;
typedef boost::uint16_t     ushort_n;
typedef boost::int32_t      int_n;
typedef boost::uint32_t     uint_n;
typedef boost::int64_t      long_n;
typedef boost::uint64_t     ulong_n;
typedef boost::float32_t    float_n;
typedef boost::float64_t    double_n;

/// const char type ///
typedef const char          char_c;

/// primitive type definitions ///
#define DATA_DEFAULT    0x00
#define DATA_BYTE       0X10
#define DATA_CHAR       0X11
#define DATA_INTEGER    0X12
#define DATA_UINTEGER   0X13
#define DATA_LONG       0X14
#define DATA_ULONG      0X15
#define DATA_FLOAT      0X16
#define DATA_DOUBLE     0X17

#define DATA_STRING     0X20


/// some other definitions ///
#ifndef elif
#define elif else if
#endif

#ifndef TRUE
#define TRUE    0x01
#endif

#ifndef FALSE
#define FALSE   0x00
#endif

#ifndef __cplusplus /// CPP DEFINITIONS ///

#ifndef or
#define or ||
#endif

#ifndef and
#define and &&
#endif

#ifndef not
#define not !
#endif

#ifndef xor
#define xor |
#endif

#ifndef xand
#define xand &
#endif

#endif /// CPP DEFINITIONS ///


/// MEMORY SAFE FREE ///

#ifndef SAFE_FREE
#define SAFE_FREE(x) {if(x!=NULL){free(x);x=NULL;}}
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(x) {if(x!=NULL){delete x;x=NULL;}}
#endif

/// MEMORY SAFE FREE ///

#ifndef DEBUG_MODE
#define DEBUG_MODE false
#endif

#endif
