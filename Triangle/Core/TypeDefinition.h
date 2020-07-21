#ifndef _TRI_TYPE_DEFINE_H_
#define _TRI_TYPE_DEFINE_H_

namespace sge {

	/// some other types ///
	typedef unsigned long		type_n;
	typedef long long			size_n;

	/// long type pointer ///
	typedef long long			ptr_n;

	/// primitive data types ///
	typedef bool				bool_n;
	typedef char				char_n;
	typedef unsigned char		byte_n;
	typedef short				short_n;
	typedef unsigned short	    ushort_n;
	typedef int					int_n;
	typedef unsigned int	    uint_n;
	typedef long			    long_n;
	typedef unsigned long	    ulong_n;
	typedef float			    float_n;
	typedef double			    double_n;

	/// const char type ///
	typedef const char          char_c;
	typedef const byte_n		byte_c;
	typedef const int			int_c;
	typedef const int_n			uint_c;
	typedef const long			long_c;
	typedef const ulong_n		ulong_c;
	typedef const float			float_c;
	typedef const double		double_c;

/// some other definitions ///
#ifndef elif
#define elif else if
#endif

#ifndef TRUE
#define TRUE    true
#endif

#ifndef FALSE
#define FALSE   false
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
};

#endif
