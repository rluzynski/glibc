/* User interface for extracting locale-dependent parameters.
   Copyright (C) 1995-2018 Free Software Foundation, Inc.
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

#include <langinfo.h>
#include <locale.h>
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include "localeinfo.h"
#include <shlib-compat.h>


/* Return a string with the data for locale-dependent parameter ITEM.  */

char *
__nl_langinfo_l_internal (nl_item item, locale_t l)
{
  int category = _NL_ITEM_CATEGORY (item);
  unsigned int index = _NL_ITEM_INDEX (item);
  const struct __locale_data *data;

  if (category < 0 || category == LC_ALL || category >= __LC_LAST)
    /* Bogus category: bogus item.  */
    return (char *) "";

  /* Special case value for NL_LOCALE_NAME (category).
     This is not a real item index in the string table.  */
  if (index == _NL_ITEM_INDEX (_NL_LOCALE_NAME (category)))
    return (char *) l->__names[category];

#if defined NL_CURRENT_INDIRECT
  /* Make direct reference to every _nl_current_CATEGORY symbol,
     since we know only at runtime which categories are used.  */
  switch (category)
    {
# define DEFINE_CATEGORY(category, category_name, items, a) \
      case category: data = *_nl_current_##category; break;
# include "categories.def"
# undef DEFINE_CATEGORY
    default:                   /* Should be impossible.  */
      abort();
    }
#else
  data = l->__locales[category];
#endif

  if (index >= data->nstrings)
    /* Bogus index for this category: bogus item.  */
    return (char *) "";

  /* Return the string for the specified item.  */
  return (char *) data->values[index].string;
}
strong_alias (__nl_langinfo_l_internal, __nl_langinfo_l_internal_alias)
versioned_symbol (libc, __nl_langinfo_l_internal,
		  __nl_langinfo_l, GLIBC_2_27);
libc_hidden_ver (__nl_langinfo_l_internal, __nl_langinfo_l)
versioned_symbol (libc, __nl_langinfo_l_internal_alias,
		  nl_langinfo_l, GLIBC_2_27);
libc_hidden_ver (__nl_langinfo_l_internal_alias, nl_langinfo_l)


#if SHLIB_COMPAT (libc, GLIBC_2_0, GLIBC_2_27)
char *
attribute_compat_text_section
__nl_langinfo_noaltmon_l (nl_item item, locale_t l)
{
  if ((item >= ALTMON_1 && item <= ALTMON_12)
      || (item >= _NL_WALTMON_1 && item <= _NL_WALTMON_12)
      || (item >= _NL_ABALTMON_1 && item <= _NL_ABALTMON_12)
      || (item >= _NL_WABALTMON_1 && item <= _NL_WABALTMON_12))
    /* Pretend it's a bogus index for this category: bogus item.  */
    return (char *) "";
  else if (item >= MON_1 && item <= MON_12)
    {
      /* ALTMON_... item contains what MON_... item contained before.  */
      return __nl_langinfo_l (item + ALTMON_1 - MON_1, l);
    }
  else if (item >= _NL_WMON_1 && item <= _NL_WMON_12)
    {
      /* The same for _NL_WALTMON_... and _NL_WMON_...  */
      return __nl_langinfo_l (item + _NL_WALTMON_1 - _NL_WMON_1, l);
    }
  else if (item >= ABMON_1 && item <= ABMON_12)
    {
      /* _NL_ABALTMON... item contains what ABMON_... item contained before.  */
      return __nl_langinfo_l (item + _NL_ABALTMON_1 - ABMON_1, l);
    }
  else if (item >= _NL_WABMON_1 && item <= _NL_WABMON_12)
    {
      /* The same for _NL_WABALTMON_... and _NL_WABMON_...  */
      return __nl_langinfo_l (item + _NL_WABALTMON_1 - _NL_WABMON_1, l);
    }

  /* Default result if it is not a month.  */
  return __nl_langinfo_l (item, l);
}
libc_hidden_def (__nl_langinfo_noaltmon_l)
#endif

#if SHLIB_COMPAT (libc, GLIBC_2_2, GLIBC_2_27)
strong_alias (__nl_langinfo_noaltmon_l, __nl_langinfo_noaltmon_l_alias)
compat_symbol (libc, __nl_langinfo_noaltmon_l_alias,
	       __nl_langinfo_l, GLIBC_2_2);
#endif

#if SHLIB_COMPAT (libc, GLIBC_2_3, GLIBC_2_27)
compat_symbol (libc, __nl_langinfo_noaltmon_l, nl_langinfo_l, GLIBC_2_3);
#endif
