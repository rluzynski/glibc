#ifndef _LANGINFO_H

#include <locale/langinfo.h>

#ifndef _ISOMAC
libc_hidden_proto (nl_langinfo)

extern __typeof (nl_langinfo_l) __nl_langinfo_l;
libc_hidden_proto (__nl_langinfo_l)
extern __typeof (nl_langinfo_l) __nl_langinfo_noaltmon_l;
libc_hidden_proto (__nl_langinfo_noaltmon_l)
#endif

#endif
