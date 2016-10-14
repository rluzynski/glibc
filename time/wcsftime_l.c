/* Copyright (C) 2002-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <wchar.h>
#include <wctype.h>

#define USE_IN_EXTENDED_LOCALE_MODEL 1
#define COMPILE_WIDE	1
#include "strftime_l.c"

size_t
__wcsftime_l_internal (wchar_t *s, size_t maxsize, const wchar_t *format,
		       const struct tm *tp, locale_t loc)
{
  return my_strftime (s, maxsize, format, tp, 1, loc);
}
strong_alias (__wcsftime_l_internal, __wcsftime_l_internal_alias)
versioned_symbol (libc, __wcsftime_l_internal_alias,
		  __wcsftime_l, GLIBC_2_27);
libc_hidden_ver (__wcsftime_l_internal_alias, __wcsftime_l)
versioned_symbol (libc, __wcsftime_l_internal, wcsftime_l, GLIBC_2_27);
libc_hidden_ver (__wcsftime_l_internal, wcsftime_l)

#if SHLIB_COMPAT (libc, GLIBC_2_3, GLIBC_2_27)
size_t
attribute_compat_text_section
__wcsftime_l_compat (wchar_t *s, size_t maxsize, const wchar_t *format,
		     const struct tm *tp, locale_t loc)
{
  return my_strftime (s, maxsize, format, tp, 0, loc);
}
strong_alias (__wcsftime_l_compat, __wcsftime_l_compat_alias)
compat_symbol (libc, __wcsftime_l_compat_alias, __wcsftime_l, GLIBC_2_3);
compat_symbol (libc, __wcsftime_l_compat, wcsftime_l, GLIBC_2_3);
#endif
