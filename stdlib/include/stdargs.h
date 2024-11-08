/**
 * stdargs.h
 * Basic Operating System, Standard Argument Management
 */

#ifndef _STDARGS_H
#define _STDARGS_H

#include "stddef.h"

typedef char* va_list;

#define va_start(p, last) (p = (va_list)&last + sizeof(last))
#define va_arg(p, type) (*(type*)((p += sizeof(type)) - sizeof(type)))
#define va_end(p) (p = NULL)

#endif