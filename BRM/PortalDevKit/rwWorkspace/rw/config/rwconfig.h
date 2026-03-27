#ifndef __RW_CONFIG_H__
#define __RW_CONFIG_H__

#define _RWCAT2(a, b)    a ## b
#define _RWCAT(a, b)     _RWCAT2 (a, b)
#define _RWEXPAND2(s)    s
#define _RWEXPAND(tag)   _RWCAT (_RWTAG_, _RWEXPAND2 (tag))

#define _RWTAG_12d 1
#if _RWTAG_12d == _RWEXPAND (_RWCONFIG)
#  define _RWCONFIG_12d 1
#endif

#define _RWTAG_15d 2
#if _RWTAG_15d == _RWEXPAND (_RWCONFIG)
#  define _RWCONFIG_15d 1
#endif

#endif
