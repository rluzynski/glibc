/* Copyright (C) 1991-2018 Free Software Foundation, Inc.
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
#include <locale/localeinfo.h>
#include <shlib-compat.h>


size_t
__wcsftime (wchar_t *s, size_t maxsize, const wchar_t *format,
	    const struct tm *tp)
{
  return __wcsftime_l_common (s, maxsize, format, tp, 1, _NL_CURRENT_LOCALE);
}
versioned_symbol (libc, __wcsftime, wcsftime, GLIBC_2_27);
libc_hidden_ver (__wcsftime, wcsftime)


#if SHLIB_COMPAT (libc, GLIBC_2_2, GLIBC_2_27)
size_t
attribute_compat_text_section
__wcsftime_compat (wchar_t *s, size_t maxsize, const wchar_t *format,
		   const struct tm *tp)
{
  return __wcsftime_l_common (s, maxsize, format, tp, 0, _NL_CURRENT_LOCALE);
}
compat_symbol (libc, __wcsftime_compat, wcsftime, GLIBC_2_2);
#endif
