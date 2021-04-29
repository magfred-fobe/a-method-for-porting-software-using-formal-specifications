# 1 "queue_impl_nonexpanded.cpp"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4

# 1 "/usr/include/stdc-predef.h" 3 4
/* Copyright (C) 1991-2020 Free Software Foundation, Inc.
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
   <https://www.gnu.org/licenses/>.  */




/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */

/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
# 52 "/usr/include/stdc-predef.h" 3 4
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
# 1 "<command-line>" 2
# 1 "queue_impl_nonexpanded.cpp"
# 1 "queue_impl.h" 1

# 1 "queue_impl.h"
//
// Created by Magnus on 3/31/21.
//
       

# 1 "queue.h" 1
/*Source from
 *  sys/sys/queue.h
 *  gcc -E queue.h
 *  */

/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)queue.h	8.5 (Berkeley) 8/20/94
 * $FreeBSD$
 */




# 1 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 1 3 4

# 1 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
/* Copyright (C) 1992-2020 Free Software Foundation, Inc.
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
   <https://www.gnu.org/licenses/>.  */




/* We are almost always included from features.h. */

# 1 "/usr/include/features.h" 1 3 4
/* Copyright (C) 1991-2020 Free Software Foundation, Inc.
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
   <https://www.gnu.org/licenses/>.  */




/* These are defined by the user (or the compiler)
   to specify the desired environment:

   __STRICT_ANSI__	ISO Standard C.
   _ISOC99_SOURCE	Extensions to ISO C89 from ISO C99.
   _ISOC11_SOURCE	Extensions to ISO C99 from ISO C11.
   _ISOC2X_SOURCE	Extensions to ISO C99 from ISO C2X.
   __STDC_WANT_LIB_EXT2__
			Extensions to ISO C99 from TR 27431-2:2010.
   __STDC_WANT_IEC_60559_BFP_EXT__
			Extensions to ISO C11 from TS 18661-1:2014.
   __STDC_WANT_IEC_60559_FUNCS_EXT__
			Extensions to ISO C11 from TS 18661-4:2015.
   __STDC_WANT_IEC_60559_TYPES_EXT__
			Extensions to ISO C11 from TS 18661-3:2015.

   _POSIX_SOURCE	IEEE Std 1003.1.
   _POSIX_C_SOURCE	If ==1, like _POSIX_SOURCE; if >=2 add IEEE Std 1003.2;
			if >=199309L, add IEEE Std 1003.1b-1993;
			if >=199506L, add IEEE Std 1003.1c-1995;
			if >=200112L, all of IEEE 1003.1-2004
			if >=200809L, all of IEEE 1003.1-2008
   _XOPEN_SOURCE	Includes POSIX and XPG things.  Set to 500 if
			Single Unix conformance is wanted, to 600 for the
			sixth revision, to 700 for the seventh revision.
   _XOPEN_SOURCE_EXTENDED XPG things and X/Open Unix extensions.
   _LARGEFILE_SOURCE	Some more functions for correct standard I/O.
   _LARGEFILE64_SOURCE	Additional functionality from LFS for large files.
   _FILE_OFFSET_BITS=N	Select default filesystem interface.
   _ATFILE_SOURCE	Additional *at interfaces.
   _GNU_SOURCE		All of the above, plus GNU extensions.
   _DEFAULT_SOURCE	The default set of features (taking precedence over
			__STRICT_ANSI__).

   _FORTIFY_SOURCE	Add security hardening to many library functions.
			Set to 1 or 2; 2 performs stricter checks than 1.

   _REENTRANT, _THREAD_SAFE
			Obsolete; equivalent to _POSIX_C_SOURCE=199506L.

   The `-ansi' switch to the GNU C compiler, and standards conformance
   options such as `-std=c99', define __STRICT_ANSI__.  If none of
   these are defined, or if _DEFAULT_SOURCE is defined, the default is
   to have _POSIX_SOURCE set to one and _POSIX_C_SOURCE set to
   200809L, as well as enabling miscellaneous functions from BSD and
   SVID.  If more than one of these are defined, they accumulate.  For
   example __STRICT_ANSI__, _POSIX_SOURCE and _POSIX_C_SOURCE together
   give you ISO C, 1003.1, and 1003.2, but nothing else.

   These are defined by this file and are used by the
   header files to decide what to declare or define:

   __GLIBC_USE (F)	Define things from feature set F.  This is defined
			to 1 or 0; the subsequent macros are either defined
			or undefined, and those tests should be moved to
			__GLIBC_USE.
   __USE_ISOC11		Define ISO C11 things.
   __USE_ISOC99		Define ISO C99 things.
   __USE_ISOC95		Define ISO C90 AMD1 (C95) things.
   __USE_ISOCXX11	Define ISO C++11 things.
   __USE_POSIX		Define IEEE Std 1003.1 things.
   __USE_POSIX2		Define IEEE Std 1003.2 things.
   __USE_POSIX199309	Define IEEE Std 1003.1, and .1b things.
   __USE_POSIX199506	Define IEEE Std 1003.1, .1b, .1c and .1i things.
   __USE_XOPEN		Define XPG things.
   __USE_XOPEN_EXTENDED	Define X/Open Unix things.
   __USE_UNIX98		Define Single Unix V2 things.
   __USE_XOPEN2K        Define XPG6 things.
   __USE_XOPEN2KXSI     Define XPG6 XSI things.
   __USE_XOPEN2K8       Define XPG7 things.
   __USE_XOPEN2K8XSI    Define XPG7 XSI things.
   __USE_LARGEFILE	Define correct standard I/O things.
   __USE_LARGEFILE64	Define LFS things with separate names.
   __USE_FILE_OFFSET64	Define 64bit interface as default.
   __USE_MISC		Define things from 4.3BSD or System V Unix.
   __USE_ATFILE		Define *at interfaces and AT_* constants for them.
   __USE_GNU		Define GNU extensions.
   __USE_FORTIFY_LEVEL	Additional security measures used, according to level.

   The macros `__GNU_LIBRARY__', `__GLIBC__', and `__GLIBC_MINOR__' are
   defined by this file unconditionally.  `__GNU_LIBRARY__' is provided
   only for compatibility.  All new code should use the other symbols
   to test for features.

   All macros listed above as possibly being defined by this file are
   explicitly undefined if they are not explicitly defined.
   Feature-test macros that are not defined by the user or compiler
   but are implied by the other feature-test macros defined (or by the
   lack of any definitions) are defined by the file.

   ISO C feature test macros depend on the definition of the macro
   when an affected header is included, not when the first system
   header is included, and so they are handled in
   <bits/libc-header-start.h>, which does not have a multiple include
   guard.  Feature test macros that can be handled from the first
   system header included are handled here.  */


/* Undefine everything, so we get a clean slate.  */
# 147 "/usr/include/features.h" 3 4
/* Suppress kernel-name space pollution unless user expressedly asks
   for it.  */




/* Convenience macro to test the version of gcc.
   Use like this:
   #if __GNUC_PREREQ (2,8)
   ... code requiring gcc 2.8 or later ...
   #endif
   Note: only works for GCC 2.0 and later, because __GNUC_MINOR__ was
   added in 2.0.  */







/* Similarly for clang.  Features added to GCC after version 4.2 may
   or may not also be available in clang, and clang's definitions of
   __GNUC(_MINOR)__ are fixed at 4 and 2 respectively.  Not all such
   features can be queried via __has_extension/__has_feature.  */







/* Whether to use feature set F.  */


/* _BSD_SOURCE and _SVID_SOURCE are deprecated aliases for
   _DEFAULT_SOURCE.  If _DEFAULT_SOURCE is present we do not
   issue a warning; the expectation is that the source is being
   transitioned to use the new macro.  */







/* If _GNU_SOURCE was defined by the user, turn on all the other features.  */
# 218 "/usr/include/features.h" 3 4
/* If nothing (other than _GNU_SOURCE and _DEFAULT_SOURCE) is defined,
   define _DEFAULT_SOURCE.  */
# 230 "/usr/include/features.h" 3 4
/* This is to enable the ISO C2X extension.  */







/* This is to enable the ISO C11 extension.  */





/* This is to enable the ISO C99 extension.  */






/* This is to enable the ISO C90 Amendment 1:1995 extension.  */







/* This is to enable compatibility for ISO C++17.  */



/* This is to enable compatibility for ISO C++11.
   Check the temporary macro for now, too.  */






/* If none of the ANSI/POSIX macros are defined, or if _DEFAULT_SOURCE
   is defined, use POSIX.1-2008 (or another version depending on
   _XOPEN_SOURCE).  */
# 300 "/usr/include/features.h" 3 4
/* Some C libraries once required _REENTRANT and/or _THREAD_SAFE to be
   defined in all multithreaded code.  GNU libc has not required this
   for many years.  We now treat them as compatibility synonyms for
   _POSIX_C_SOURCE=199506L, which is the earliest level of POSIX with
   comprehensive support for multithreaded code.  Using them never
   lowers the selected level of POSIX conformance, only raises it.  */
# 406 "/usr/include/features.h" 3 4
/* The function 'gets' existed in C89, but is impossible to use
   safely.  It has been removed from ISO C11 and ISO C++14.  Note: for
   compatibility with various implementations of <cstdio>, this test
   must consider only the value of __cplusplus when compiling C++.  */






/* GNU formerly extended the scanf functions with modified format
   specifiers %as, %aS, and %a[...] that allocate a buffer for the
   input using malloc.  This extension conflicts with ISO C99, which
   defines %a as a standalone format specifier that reads a floating-
   point number; moreover, POSIX.1-2008 provides the same feature
   using the modifier letter 'm' instead (%ms, %mS, %m[...]).

   We now follow C99 unless GNU extensions are active and the compiler
   is specifically in C89 or C++98 mode (strict or not).  For
   instance, with GCC, -std=gnu11 will have C99-compliant scanf with
   or without -D_GNU_SOURCE, but -std=c89 -D_GNU_SOURCE will have the
   old extension.  */
# 437 "/usr/include/features.h" 3 4
/* Get definitions of __STDC_* predefined macros, if the compiler has
   not preincluded this header automatically.  */
# 1 "/usr/include/stdc-predef.h" 1 3 4
/* Copyright (C) 1991-2020 Free Software Foundation, Inc.
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
   <https://www.gnu.org/licenses/>.  */
# 440 "/usr/include/features.h" 2 3 4

/* This macro indicates that the installed library is the GNU C Library.
   For historic reasons the value now is 6 and this will stay from now
   on.  The use of this variable is deprecated.  Use __GLIBC__ and
   __GLIBC_MINOR__ now (see below) when you want to test for a specific
   GNU C library version and use the values in <gnu/lib-names.h> to get
   the sonames of the shared libraries.  */



/* Major and minor version number of the GNU C library package.  Use
   these macros to test for features in specific releases.  */






/* This is here only because every header file already includes this one.  */





/* If we don't have __REDIRECT, prototypes will be missing if
   __USE_FILE_OFFSET64 but not __USE_LARGEFILE[64]. */







/* Decide whether we can define 'extern inline' functions in headers.  */







/* This is here only because every header file already includes this one.
   Get the definitions of all the appropriate `__stub_FUNCTION' symbols.
   <gnu/stubs.h> contains `#define __stub_FUNCTION' when FUNCTION is a stub
   that will always return failure (and set errno to ENOSYS).  */
# 1 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 1 3 4
/* This file is automatically generated.
   This file selects the right generated file of `__stub_FUNCTION' macros
   based on the architecture being compiled for.  */






# 1 "/usr/include/x86_64-linux-gnu/gnu/stubs-64.h" 1 3 4
/* This file is automatically generated.
   It defines a symbol `__stub_FUNCTION' for each function
   in the C library which is a stub, meaning it will fail
   every time called, usually setting errno to ENOSYS.  */
# 11 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 2 3 4
# 486 "/usr/include/features.h" 2 3 4
# 24 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 2 3 4


/* The GNU libc does not support any K&R compilers or the traditional mode
   of ISO C compilers anymore.  Check for some of the combinations not
   anymore supported.  */




/* Some user header file might have defined this before.  */





/* All functions, except those with callbacks or those that
   synchronize memory, are leaf functions.  */
# 49 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
/* GCC can always grok prototypes.  For C++ programs we add throw()
   to help it optimize the function calls.  But this works only with
   gcc 2.8.x and egcs.  For gcc 3.2 and up we even mark C functions
   as non-throwing using a function attribute since programs can use
   the -fexceptions options for C code as well.  */
# 88 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
/* Compilers that are not clang may object to
       #if defined __clang__ && __has_extension(...)
   even though they do not need to evaluate the right-hand side of the &&.  */






/* These two macros are not used in glibc anymore.  They are kept here
   only because some other projects expect the macros to be defined.  */



/* For these things, GCC behaves the ANSI way normally,
   and the non-ANSI way under -traditional.  */




/* This is not a typedef so `const __ptr_t' does the right thing.  */



/* C++ needs to know that types and declarations are C, not C++.  */
# 122 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
/* Fortify support.  */
# 138 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
/* Support for flexible arrays.
   Headers that should use flexible arrays only if they're "real"
   (e.g. only if they won't affect sizeof()) should test
   #if __glibc_c99_flexarr_available.  */




/* GCC 2.97 supports C99 flexible array members as an extension,
   even when in C89 mode or compiling C++ (any version).  */
# 162 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
/* __asm__ ("xyz") is used throughout the headers to rename functions
   at the assembly language level.  This is wrapped by the __REDIRECT
   macro, in order to support compilers that can do this some other
   way.  When compilers don't support asm-names at all, we have to do
   preprocessor tricks instead (which don't have exactly the right
   semantics, but it's the best we can do).

   Example:
   int __REDIRECT(setpgrp, (__pid_t pid, __pid_t pgrp), setpgid); */
# 189 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
/*
#elif __SOME_OTHER_COMPILER__

# define __REDIRECT(name, proto, alias) name proto; 	_Pragma("let " #name " = " #alias)
)
*/


/* GCC has various useful declarations that can be made with the
   `__attribute__' syntax.  All of the ways we use this do fine if
   they are omitted for compilers that don't understand it. */




/* At some point during the gcc 2.96 development the `malloc' attribute
   for functions was introduced.  We don't want to use it unconditionally
   (although this would be possible) since it generates warnings.  */






/* Tell the compiler which arguments to an allocation function
   indicate the size of the allocation.  */







/* At some point during the gcc 2.96 development the `pure' attribute
   for functions was introduced.  We don't want to use it unconditionally
   (although this would be possible) since it generates warnings.  */






/* This declaration tells the compiler that the value is constant.  */






/* At some point during the gcc 3.1 development the `used' attribute
   for functions was introduced.  We don't want to use it unconditionally
   (although this would be possible) since it generates warnings.  */
# 249 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
/* Since version 3.2, gcc allows marking deprecated functions.  */






/* Since version 4.5, gcc also allows one to specify the message printed
   when a deprecated function is used.  clang claims to be gcc 4.2, but
   may also support this feature.  */
# 267 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
/* At some point during the gcc 2.8 development the `format_arg' attribute
   for functions was introduced.  We don't want to use it unconditionally
   (although this would be possible) since it generates warnings.
   If several `format_arg' attributes are given for the same function, in
   gcc-3.0 and older, all but the last one are ignored.  In newer gccs,
   all designated arguments are considered.  */






/* At some point during the gcc 2.97 development the `strfmon' format
   attribute for functions was introduced.  We don't want to use it
   unconditionally (although this would be possible) since it
   generates warnings.  */







/* The nonull function attribute allows to mark pointer parameters which
   must not be NULL.  */






/* If fortification mode, we warn about unused results of certain
   function calls which can lead to problems.  */
# 313 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
/* Forces a function to be always inlined.  */

/* The Linux kernel defines __always_inline in stddef.h (283d7573), and
   it conflicts with this definition.  Therefore undefine it first to
   allow either header to be included first.  */







/* Associate error messages with the source location of the call site rather
   than with the source location inside the function.  */






/* GCC 4.3 and above with -std=c99 or -std=gnu99 implements ISO C99
   inline semantics, unless -fgnu89-inline is used.  Using __GNUC_STDC_INLINE__
   or __GNUC_GNU_INLINE is not a good enough check for gcc because gcc versions
   older than 4.3 may define these macros and still not guarantee GNU inlining
   semantics.

   clang++ identifies itself as gcc-4.2, but has support for GNU inlining
   semantics, that can be checked for by using the __GNUC_STDC_INLINE_ and
   __GNUC_GNU_INLINE__ macro definitions.  */
# 359 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
/* GCC 4.3 and above allow passing all anonymous arguments of an
   __extern_always_inline function to some other vararg function.  */





/* It is possible to compile containing GCC extensions even if GCC is
   run in pedantic mode if the uses are carefully marked using the
   `__extension__' keyword.  But this is not generally available before
   version 2.8.  */




/* __restrict is known in EGCS 1.2 and above. */
# 383 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
/* ISO C99 also allows to declare arrays as non-overlapping.  The syntax is
     array_name[restrict]
   GCC 3.1 supports this.  */
# 426 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
/* Describes a char array whose address can safely be passed as the first
   argument to strncpy and strncat, as the char array is not necessarily
   a NUL-terminated string.  */





/* Undefine (also defined in libc-symbols.h).  */


/* Copies attributes from the declaration or type referenced by
   the argument.  */
# 452 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
/* Determine the wordsize from the preprocessor defines.  */
# 13 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 3 4
/* Both x86-64 and x32 use the 64-bit system call interface.  */
# 453 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/long-double.h" 1 3 4
/* Properties of long double type.  ldbl-96 version.
   Copyright (C) 2016-2020 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License  published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

/* long double is distinct from double, so there is nothing to
   define here.  */
# 454 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 2 3 4
# 487 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
/* __glibc_macro_warning (MESSAGE) issues warning MESSAGE.  This is
   intended for use in preprocessor macros.

   Note: MESSAGE must be a _single_ string; concatenation of string
   literals is not supported.  */
# 500 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
/* Generic selection (ISO C11) is a C-only feature, available in GCC
   since version 4.9.  Previous versions do not provide generic
   selection, even though they might set __STDC_VERSION__ to 201112L,
   when in -std=c11 mode.  Thus, we must check for !defined __GNUC__
   when testing __STDC_VERSION__ for generic selection support.
   On the other hand, Clang also defines __GNUC__, so a clang-specific
   check is required to enable the use of generic selection.  */
# 44 "queue.h" 2
# 1 "/usr/include/c++/10/cstdint" 1 3
// <cstdint> -*- C++ -*-

// Copyright (C) 2007-2020 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file include/cstdint
 *  This is a Standard C++ Library header.
 */




       
# 33 "/usr/include/c++/10/cstdint" 3





# 1 "/usr/include/x86_64-linux-gnu/c++/10/bits/c++config.h" 1 3
// Predefined symbols and macros -*- C++ -*-

// Copyright (C) 1997-2020 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file bits/c++config.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{version}
 */




// The major release number for the GCC release the C++ library belongs to.


// The datestamp of the C++ library in compressed ISO date format.


// Macros for various attributes.
//   _GLIBCXX_PURE
//   _GLIBCXX_CONST
//   _GLIBCXX_NORETURN
//   _GLIBCXX_NOTHROW
//   _GLIBCXX_VISIBILITY
# 57 "/usr/include/x86_64-linux-gnu/c++/10/bits/c++config.h" 3
// See below for C++






// Macros for visibility attributes.
//   _GLIBCXX_HAVE_ATTRIBUTE_VISIBILITY
//   _GLIBCXX_VISIBILITY
# 77 "/usr/include/x86_64-linux-gnu/c++/10/bits/c++config.h" 3
// Macros for deprecated attributes.
//   _GLIBCXX_USE_DEPRECATED
//   _GLIBCXX_DEPRECATED
//   _GLIBCXX_DEPRECATED_SUGGEST
//   _GLIBCXX17_DEPRECATED
//   _GLIBCXX20_DEPRECATED( string-literal )
# 108 "/usr/include/x86_64-linux-gnu/c++/10/bits/c++config.h" 3
// Macros for ABI tag attributes.




// Macro to warn about unused results.
# 124 "/usr/include/x86_64-linux-gnu/c++/10/bits/c++config.h" 3
// Macro for constexpr, to support in mixed 03/0x mode.
# 167 "/usr/include/x86_64-linux-gnu/c++/10/bits/c++config.h" 3
// Macro for noexcept, to support in mixed 03/0x mode.
# 202 "/usr/include/x86_64-linux-gnu/c++/10/bits/c++config.h" 3
// Macro for extern template, ie controlling template linkage via use
// of extern keyword on template declaration. As documented in the g++
// manual, it inhibits all implicit instantiations and is used
// throughout the library to avoid multiple weak definitions for
// required types that are already explicitly instantiated in the
// library binary. This substantially reduces the binary size of
// resulting executables.
// Special case: _GLIBCXX_EXTERN_TEMPLATE == -1 disallows extern
// templates only in basic_string, thus activating its debug-mode
// checks even at -O0.


/*
  Outline of libstdc++ namespaces.

  namespace std
  {
    namespace __debug { }
    namespace __parallel { }
    namespace __cxx1998 { }

    namespace __detail {
      namespace __variant { }				// C++17
    }

    namespace rel_ops { }

    namespace tr1
    {
      namespace placeholders { }
      namespace regex_constants { }
      namespace __detail { }
    }

    namespace tr2 { }
    
    namespace decimal { }

    namespace chrono { }				// C++11
    namespace placeholders { }				// C++11
    namespace regex_constants { }			// C++11
    namespace this_thread { }				// C++11
    inline namespace literals {				// C++14
      inline namespace chrono_literals { }		// C++14
      inline namespace complex_literals { }		// C++14
      inline namespace string_literals { }		// C++14
      inline namespace string_view_literals { }		// C++17
    }
  }

  namespace abi { }

  namespace __gnu_cxx
  {
    namespace __detail { }
  }

  For full details see:
  http://gcc.gnu.org/onlinedocs/libstdc++/latest-doxygen/namespaces.html
*/
namespace std
{
  typedef long unsigned int size_t;
  typedef long int ptrdiff_t;


  typedef decltype(nullptr) nullptr_t;

}
# 284 "/usr/include/x86_64-linux-gnu/c++/10/bits/c++config.h" 3
namespace std
{
  inline namespace __cxx11 __attribute__((__abi_tag__ ("cxx11"))) { }
}
namespace __gnu_cxx
{
  inline namespace __cxx11 __attribute__((__abi_tag__ ("cxx11"))) { }
}
# 303 "/usr/include/x86_64-linux-gnu/c++/10/bits/c++config.h" 3
// Defined if inline namespaces are used for versioning.


// Inline namespace for symbol versioning.
# 338 "/usr/include/x86_64-linux-gnu/c++/10/bits/c++config.h" 3
// Inline namespaces for special modes: debug, parallel.
# 377 "/usr/include/x86_64-linux-gnu/c++/10/bits/c++config.h" 3
// Macros for namespace scope. Either namespace std:: or the name
// of some nested namespace within it corresponding to the active mode.
// _GLIBCXX_STD_A
// _GLIBCXX_STD_C
//
// Macros for opening/closing conditional namespaces.
// _GLIBCXX_BEGIN_NAMESPACE_ALGO
// _GLIBCXX_END_NAMESPACE_ALGO
// _GLIBCXX_BEGIN_NAMESPACE_CONTAINER
// _GLIBCXX_END_NAMESPACE_CONTAINER
# 409 "/usr/include/x86_64-linux-gnu/c++/10/bits/c++config.h" 3
// GLIBCXX_ABI Deprecated
// Define if compatibility should be provided for -mlong-double-64.


// Inline namespace for long double 128 mode.
# 437 "/usr/include/x86_64-linux-gnu/c++/10/bits/c++config.h" 3
// Debug Mode implies checking assertions.




// Disable std::string explicit instantiation declarations in order to assert.





// Assert.
# 479 "/usr/include/x86_64-linux-gnu/c++/10/bits/c++config.h" 3
// Macros for race detectors.
// _GLIBCXX_SYNCHRONIZATION_HAPPENS_BEFORE(A) and
// _GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER(A) should be used to explain
// atomic (lock-free) synchronization to race detectors:
// the race detector will infer a happens-before arc from the former to the
// latter when they share the same argument pointer.
//
// The most frequent use case for these macros (and the only case in the
// current implementation of the library) is atomic reference counting:
//   void _M_remove_reference()
//   {
//     _GLIBCXX_SYNCHRONIZATION_HAPPENS_BEFORE(&this->_M_refcount);
//     if (__gnu_cxx::__exchange_and_add_dispatch(&this->_M_refcount, -1) <= 0)
//       {
//         _GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER(&this->_M_refcount);
//         _M_destroy(__a);
//       }
//   }
// The annotations in this example tell the race detector that all memory
// accesses occurred when the refcount was positive do not race with
// memory accesses which occurred after the refcount became zero.







// Macros for C linkage: define extern "C" linkage only when using C++.
# 519 "/usr/include/x86_64-linux-gnu/c++/10/bits/c++config.h" 3
// First includes.

// Pick up any OS-specific definitions.
# 1 "/usr/include/x86_64-linux-gnu/c++/10/bits/os_defines.h" 1 3
// Specific definitions for GNU/Linux  -*- C++ -*-

// Copyright (C) 2000-2020 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file bits/os_defines.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{iosfwd}
 */




// System-specific #define, typedefs, corrections, etc, go here.  This
// file will come before all others.

// This keeps isanum, et al from being propagated as macros.


# 1 "/usr/include/features.h" 1 3 4
/* Copyright (C) 1991-2020 Free Software Foundation, Inc.
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
   <https://www.gnu.org/licenses/>.  */
# 40 "/usr/include/x86_64-linux-gnu/c++/10/bits/os_defines.h" 2 3

// Provide a declaration for the possibly deprecated gets function, as
// glibc 2.15 and later does not declare gets for ISO C11 when
// __GNU_SOURCE is defined.




// Glibc 2.23 removed the obsolete isinf and isnan declarations. Check the
// version dynamically in case it has changed since libstdc++ was configured.



// Since glibc 2.27 pthread_self() is usable without linking to libpthread.
# 523 "/usr/include/x86_64-linux-gnu/c++/10/bits/c++config.h" 2 3

// Pick up any CPU-specific definitions.
# 1 "/usr/include/x86_64-linux-gnu/c++/10/bits/cpu_defines.h" 1 3
// Specific definitions for generic platforms  -*- C++ -*-

// Copyright (C) 2005-2020 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file bits/cpu_defines.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{iosfwd}
 */
# 526 "/usr/include/x86_64-linux-gnu/c++/10/bits/c++config.h" 2 3

// If platform uses neither visibility nor psuedo-visibility,
// specify empty default for namespace annotation macros.




// Certain function definitions that are meant to be overridable from
// user code are decorated with this macro.  For some targets, this
// macro causes these definitions to be weak.




// By default, we assume that __GXX_WEAK__ also means that there is support
// for declaring functions as weak while not defining such functions.  This
// allows for referring to functions provided by other libraries (e.g.,
// libitm) without depending on them if the respective features are not used.




// Conditionally enable annotations for the Transactional Memory TS on C++11.
// Most of the following conditions are due to limitations in the current
// implementation.
# 570 "/usr/include/x86_64-linux-gnu/c++/10/bits/c++config.h" 3
// The remainder of the prewritten config is automatic; all the
// user hooks are listed above.

// Create a boolean flag to be used to determine if --fast-math is set.






// This marks string literals in header files to be extracted for eventual
// translation.  It is primarily used for messages in thrown exceptions; see
// src/functexcept.cc.  We use __N because the more traditional _N is used
// for something else under certain OSes (see BADNAMES).


// For example, <windows.h> is known to #define min and max as macros...



// N.B. these _GLIBCXX_USE_C99_XXX macros are defined unconditionally
// so they should be tested with #if not with #ifdef.
# 626 "/usr/include/x86_64-linux-gnu/c++/10/bits/c++config.h" 3
// Unless explicitly specified, enable char8_t extensions only if the core
// language char8_t feature macro is defined.
# 637 "/usr/include/x86_64-linux-gnu/c++/10/bits/c++config.h" 3
/* Define if __float128 is supported on this host. */





// Assume these are available if the compiler claims to be a recent GCC:
# 670 "/usr/include/x86_64-linux-gnu/c++/10/bits/c++config.h" 3
// PSTL configuration
# 696 "/usr/include/x86_64-linux-gnu/c++/10/bits/c++config.h" 3
// End of prewritten config; the settings discovered at configure time follow.
/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define to 1 if you have the `acosf' function. */


/* Define to 1 if you have the `acosl' function. */


/* Define to 1 if you have the `aligned_alloc' function. */


/* Define to 1 if you have the <arpa/inet.h> header file. */


/* Define to 1 if you have the `asinf' function. */


/* Define to 1 if you have the `asinl' function. */


/* Define to 1 if the target assembler supports .symver directive. */


/* Define to 1 if you have the `atan2f' function. */


/* Define to 1 if you have the `atan2l' function. */


/* Define to 1 if you have the `atanf' function. */


/* Define to 1 if you have the `atanl' function. */


/* Defined if shared_ptr reference counting should use atomic operations. */


/* Define to 1 if you have the `at_quick_exit' function. */


/* Define to 1 if the target assembler supports thread-local storage. */
/* #undef _GLIBCXX_HAVE_CC_TLS */

/* Define to 1 if you have the `ceilf' function. */


/* Define to 1 if you have the `ceill' function. */


/* Define to 1 if you have the <complex.h> header file. */


/* Define to 1 if you have the `cosf' function. */


/* Define to 1 if you have the `coshf' function. */


/* Define to 1 if you have the `coshl' function. */


/* Define to 1 if you have the `cosl' function. */


/* Define to 1 if you have the <dirent.h> header file. */


/* Define to 1 if you have the <dlfcn.h> header file. */


/* Define if EBADMSG exists. */


/* Define if ECANCELED exists. */


/* Define if ECHILD exists. */


/* Define if EIDRM exists. */


/* Define to 1 if you have the <endian.h> header file. */


/* Define if ENODATA exists. */


/* Define if ENOLINK exists. */


/* Define if ENOSPC exists. */


/* Define if ENOSR exists. */


/* Define if ENOSTR exists. */


/* Define if ENOTRECOVERABLE exists. */


/* Define if ENOTSUP exists. */


/* Define if EOVERFLOW exists. */


/* Define if EOWNERDEAD exists. */


/* Define if EPERM exists. */


/* Define if EPROTO exists. */


/* Define if ETIME exists. */


/* Define if ETIMEDOUT exists. */


/* Define if ETXTBSY exists. */


/* Define if EWOULDBLOCK exists. */


/* Define to 1 if GCC 4.6 supported std::exception_ptr for the target */


/* Define to 1 if you have the <execinfo.h> header file. */


/* Define to 1 if you have the `expf' function. */


/* Define to 1 if you have the `expl' function. */


/* Define to 1 if you have the `fabsf' function. */


/* Define to 1 if you have the `fabsl' function. */


/* Define to 1 if you have the <fcntl.h> header file. */


/* Define to 1 if you have the <fenv.h> header file. */


/* Define to 1 if you have the `finite' function. */


/* Define to 1 if you have the `finitef' function. */


/* Define to 1 if you have the `finitel' function. */


/* Define to 1 if you have the <float.h> header file. */


/* Define to 1 if you have the `floorf' function. */


/* Define to 1 if you have the `floorl' function. */


/* Define to 1 if you have the `fmodf' function. */


/* Define to 1 if you have the `fmodl' function. */


/* Define to 1 if you have the `fpclass' function. */
/* #undef _GLIBCXX_HAVE_FPCLASS */

/* Define to 1 if you have the <fp.h> header file. */
/* #undef _GLIBCXX_HAVE_FP_H */

/* Define to 1 if you have the `frexpf' function. */


/* Define to 1 if you have the `frexpl' function. */


/* Define if _Unwind_GetIPInfo is available. */


/* Define if gets is available in <stdio.h> before C++14. */


/* Define to 1 if you have the `hypot' function. */


/* Define to 1 if you have the `hypotf' function. */


/* Define to 1 if you have the `hypotl' function. */


/* Define if you have the iconv() function. */


/* Define to 1 if you have the <ieeefp.h> header file. */
/* #undef _GLIBCXX_HAVE_IEEEFP_H */

/* Define if int64_t is available in <stdint.h>. */


/* Define if int64_t is a long. */


/* Define if int64_t is a long long. */
/* #undef _GLIBCXX_HAVE_INT64_T_LONG_LONG */

/* Define to 1 if you have the <inttypes.h> header file. */


/* Define to 1 if you have the `isinf' function. */
/* #undef _GLIBCXX_HAVE_ISINF */

/* Define to 1 if you have the `isinff' function. */


/* Define to 1 if you have the `isinfl' function. */


/* Define to 1 if you have the `isnan' function. */
/* #undef _GLIBCXX_HAVE_ISNAN */

/* Define to 1 if you have the `isnanf' function. */


/* Define to 1 if you have the `isnanl' function. */


/* Defined if iswblank exists. */


/* Define if LC_MESSAGES is available in <locale.h>. */


/* Define to 1 if you have the `ldexpf' function. */


/* Define to 1 if you have the `ldexpl' function. */


/* Define to 1 if you have the <libintl.h> header file. */


/* Only used in build directory testsuite_hooks.h. */


/* Only used in build directory testsuite_hooks.h. */


/* Only used in build directory testsuite_hooks.h. */


/* Only used in build directory testsuite_hooks.h. */


/* Only used in build directory testsuite_hooks.h. */


/* Define if link is available in <unistd.h>. */


/* Define if futex syscall is available. */


/* Define to 1 if you have the <linux/random.h> header file. */


/* Define to 1 if you have the <linux/types.h> header file. */


/* Define to 1 if you have the <locale.h> header file. */


/* Define to 1 if you have the `log10f' function. */


/* Define to 1 if you have the `log10l' function. */


/* Define to 1 if you have the `logf' function. */


/* Define to 1 if you have the `logl' function. */


/* Define to 1 if you have the <machine/endian.h> header file. */
/* #undef _GLIBCXX_HAVE_MACHINE_ENDIAN_H */

/* Define to 1 if you have the <machine/param.h> header file. */
/* #undef _GLIBCXX_HAVE_MACHINE_PARAM_H */

/* Define if mbstate_t exists in wchar.h. */


/* Define to 1 if you have the `memalign' function. */


/* Define to 1 if you have the <memory.h> header file. */


/* Define to 1 if you have the `modf' function. */


/* Define to 1 if you have the `modff' function. */


/* Define to 1 if you have the `modfl' function. */


/* Define to 1 if you have the <nan.h> header file. */
/* #undef _GLIBCXX_HAVE_NAN_H */

/* Define to 1 if you have the <netdb.h> header file. */


/* Define to 1 if you have the <netinet/in.h> header file. */


/* Define to 1 if you have the <netinet/tcp.h> header file. */


/* Define if <math.h> defines obsolete isinf function. */
/* #undef _GLIBCXX_HAVE_OBSOLETE_ISINF */

/* Define if <math.h> defines obsolete isnan function. */
/* #undef _GLIBCXX_HAVE_OBSOLETE_ISNAN */

/* Define if poll is available in <poll.h>. */


/* Define to 1 if you have the <poll.h> header file. */


/* Define to 1 if you have the `posix_memalign' function. */


/* Define to 1 if you have the `powf' function. */


/* Define to 1 if you have the `powl' function. */


/* Define to 1 if you have the `qfpclass' function. */
/* #undef _GLIBCXX_HAVE_QFPCLASS */

/* Define to 1 if you have the `quick_exit' function. */


/* Define if readlink is available in <unistd.h>. */


/* Define to 1 if you have the `setenv' function. */


/* Define to 1 if you have the `sincos' function. */


/* Define to 1 if you have the `sincosf' function. */


/* Define to 1 if you have the `sincosl' function. */


/* Define to 1 if you have the `sinf' function. */


/* Define to 1 if you have the `sinhf' function. */


/* Define to 1 if you have the `sinhl' function. */


/* Define to 1 if you have the `sinl' function. */


/* Defined if sleep exists. */
/* #undef _GLIBCXX_HAVE_SLEEP */

/* Define to 1 if you have the `sockatmark' function. */


/* Define to 1 if you have the `sqrtf' function. */


/* Define to 1 if you have the `sqrtl' function. */


/* Define to 1 if you have the <stdalign.h> header file. */


/* Define to 1 if you have the <stdbool.h> header file. */


/* Define to 1 if you have the <stdint.h> header file. */


/* Define to 1 if you have the <stdlib.h> header file. */


/* Define if strerror_l is available in <string.h>. */


/* Define if strerror_r is available in <string.h>. */


/* Define to 1 if you have the <strings.h> header file. */


/* Define to 1 if you have the <string.h> header file. */


/* Define to 1 if you have the `strtof' function. */


/* Define to 1 if you have the `strtold' function. */


/* Define to 1 if `d_type' is a member of `struct dirent'. */


/* Define if strxfrm_l is available in <string.h>. */


/* Define if symlink is available in <unistd.h>. */


/* Define to 1 if the target runtime linker supports binding the same symbol
   to different versions. */


/* Define to 1 if you have the <sys/filio.h> header file. */
/* #undef _GLIBCXX_HAVE_SYS_FILIO_H */

/* Define to 1 if you have the <sys/ioctl.h> header file. */


/* Define to 1 if you have the <sys/ipc.h> header file. */


/* Define to 1 if you have the <sys/isa_defs.h> header file. */
/* #undef _GLIBCXX_HAVE_SYS_ISA_DEFS_H */

/* Define to 1 if you have the <sys/machine.h> header file. */
/* #undef _GLIBCXX_HAVE_SYS_MACHINE_H */

/* Define to 1 if you have the <sys/param.h> header file. */


/* Define to 1 if you have the <sys/resource.h> header file. */


/* Define to 1 if you have a suitable <sys/sdt.h> header file */


/* Define to 1 if you have the <sys/sem.h> header file. */


/* Define to 1 if you have the <sys/socket.h> header file. */


/* Define to 1 if you have the <sys/statvfs.h> header file. */


/* Define to 1 if you have the <sys/stat.h> header file. */


/* Define to 1 if you have the <sys/sysinfo.h> header file. */


/* Define to 1 if you have the <sys/time.h> header file. */


/* Define to 1 if you have the <sys/types.h> header file. */


/* Define to 1 if you have the <sys/uio.h> header file. */


/* Define if S_IFREG is available in <sys/stat.h>. */
/* #undef _GLIBCXX_HAVE_S_IFREG */

/* Define if S_ISREG is available in <sys/stat.h>. */


/* Define to 1 if you have the `tanf' function. */


/* Define to 1 if you have the `tanhf' function. */


/* Define to 1 if you have the `tanhl' function. */


/* Define to 1 if you have the `tanl' function. */


/* Define to 1 if you have the <tgmath.h> header file. */


/* Define to 1 if you have the `timespec_get' function. */


/* Define to 1 if the target supports thread-local storage. */


/* Define if truncate is available in <unistd.h>. */


/* Define to 1 if you have the <uchar.h> header file. */


/* Define to 1 if you have the <unistd.h> header file. */


/* Defined if usleep exists. */
/* #undef _GLIBCXX_HAVE_USLEEP */

/* Define to 1 if you have the <utime.h> header file. */


/* Defined if vfwscanf exists. */


/* Defined if vswscanf exists. */


/* Defined if vwscanf exists. */


/* Define to 1 if you have the <wchar.h> header file. */


/* Defined if wcstof exists. */


/* Define to 1 if you have the <wctype.h> header file. */


/* Defined if Sleep exists. */
/* #undef _GLIBCXX_HAVE_WIN32_SLEEP */

/* Define if writev is available in <sys/uio.h>. */


/* Define to 1 if you have the `_acosf' function. */
/* #undef _GLIBCXX_HAVE__ACOSF */

/* Define to 1 if you have the `_acosl' function. */
/* #undef _GLIBCXX_HAVE__ACOSL */

/* Define to 1 if you have the `_aligned_malloc' function. */
/* #undef _GLIBCXX_HAVE__ALIGNED_MALLOC */

/* Define to 1 if you have the `_asinf' function. */
/* #undef _GLIBCXX_HAVE__ASINF */

/* Define to 1 if you have the `_asinl' function. */
/* #undef _GLIBCXX_HAVE__ASINL */

/* Define to 1 if you have the `_atan2f' function. */
/* #undef _GLIBCXX_HAVE__ATAN2F */

/* Define to 1 if you have the `_atan2l' function. */
/* #undef _GLIBCXX_HAVE__ATAN2L */

/* Define to 1 if you have the `_atanf' function. */
/* #undef _GLIBCXX_HAVE__ATANF */

/* Define to 1 if you have the `_atanl' function. */
/* #undef _GLIBCXX_HAVE__ATANL */

/* Define to 1 if you have the `_ceilf' function. */
/* #undef _GLIBCXX_HAVE__CEILF */

/* Define to 1 if you have the `_ceill' function. */
/* #undef _GLIBCXX_HAVE__CEILL */

/* Define to 1 if you have the `_cosf' function. */
/* #undef _GLIBCXX_HAVE__COSF */

/* Define to 1 if you have the `_coshf' function. */
/* #undef _GLIBCXX_HAVE__COSHF */

/* Define to 1 if you have the `_coshl' function. */
/* #undef _GLIBCXX_HAVE__COSHL */

/* Define to 1 if you have the `_cosl' function. */
/* #undef _GLIBCXX_HAVE__COSL */

/* Define to 1 if you have the `_expf' function. */
/* #undef _GLIBCXX_HAVE__EXPF */

/* Define to 1 if you have the `_expl' function. */
/* #undef _GLIBCXX_HAVE__EXPL */

/* Define to 1 if you have the `_fabsf' function. */
/* #undef _GLIBCXX_HAVE__FABSF */

/* Define to 1 if you have the `_fabsl' function. */
/* #undef _GLIBCXX_HAVE__FABSL */

/* Define to 1 if you have the `_finite' function. */
/* #undef _GLIBCXX_HAVE__FINITE */

/* Define to 1 if you have the `_finitef' function. */
/* #undef _GLIBCXX_HAVE__FINITEF */

/* Define to 1 if you have the `_finitel' function. */
/* #undef _GLIBCXX_HAVE__FINITEL */

/* Define to 1 if you have the `_floorf' function. */
/* #undef _GLIBCXX_HAVE__FLOORF */

/* Define to 1 if you have the `_floorl' function. */
/* #undef _GLIBCXX_HAVE__FLOORL */

/* Define to 1 if you have the `_fmodf' function. */
/* #undef _GLIBCXX_HAVE__FMODF */

/* Define to 1 if you have the `_fmodl' function. */
/* #undef _GLIBCXX_HAVE__FMODL */

/* Define to 1 if you have the `_fpclass' function. */
/* #undef _GLIBCXX_HAVE__FPCLASS */

/* Define to 1 if you have the `_frexpf' function. */
/* #undef _GLIBCXX_HAVE__FREXPF */

/* Define to 1 if you have the `_frexpl' function. */
/* #undef _GLIBCXX_HAVE__FREXPL */

/* Define to 1 if you have the `_hypot' function. */
/* #undef _GLIBCXX_HAVE__HYPOT */

/* Define to 1 if you have the `_hypotf' function. */
/* #undef _GLIBCXX_HAVE__HYPOTF */

/* Define to 1 if you have the `_hypotl' function. */
/* #undef _GLIBCXX_HAVE__HYPOTL */

/* Define to 1 if you have the `_isinf' function. */
/* #undef _GLIBCXX_HAVE__ISINF */

/* Define to 1 if you have the `_isinff' function. */
/* #undef _GLIBCXX_HAVE__ISINFF */

/* Define to 1 if you have the `_isinfl' function. */
/* #undef _GLIBCXX_HAVE__ISINFL */

/* Define to 1 if you have the `_isnan' function. */
/* #undef _GLIBCXX_HAVE__ISNAN */

/* Define to 1 if you have the `_isnanf' function. */
/* #undef _GLIBCXX_HAVE__ISNANF */

/* Define to 1 if you have the `_isnanl' function. */
/* #undef _GLIBCXX_HAVE__ISNANL */

/* Define to 1 if you have the `_ldexpf' function. */
/* #undef _GLIBCXX_HAVE__LDEXPF */

/* Define to 1 if you have the `_ldexpl' function. */
/* #undef _GLIBCXX_HAVE__LDEXPL */

/* Define to 1 if you have the `_log10f' function. */
/* #undef _GLIBCXX_HAVE__LOG10F */

/* Define to 1 if you have the `_log10l' function. */
/* #undef _GLIBCXX_HAVE__LOG10L */

/* Define to 1 if you have the `_logf' function. */
/* #undef _GLIBCXX_HAVE__LOGF */

/* Define to 1 if you have the `_logl' function. */
/* #undef _GLIBCXX_HAVE__LOGL */

/* Define to 1 if you have the `_modf' function. */
/* #undef _GLIBCXX_HAVE__MODF */

/* Define to 1 if you have the `_modff' function. */
/* #undef _GLIBCXX_HAVE__MODFF */

/* Define to 1 if you have the `_modfl' function. */
/* #undef _GLIBCXX_HAVE__MODFL */

/* Define to 1 if you have the `_powf' function. */
/* #undef _GLIBCXX_HAVE__POWF */

/* Define to 1 if you have the `_powl' function. */
/* #undef _GLIBCXX_HAVE__POWL */

/* Define to 1 if you have the `_qfpclass' function. */
/* #undef _GLIBCXX_HAVE__QFPCLASS */

/* Define to 1 if you have the `_sincos' function. */
/* #undef _GLIBCXX_HAVE__SINCOS */

/* Define to 1 if you have the `_sincosf' function. */
/* #undef _GLIBCXX_HAVE__SINCOSF */

/* Define to 1 if you have the `_sincosl' function. */
/* #undef _GLIBCXX_HAVE__SINCOSL */

/* Define to 1 if you have the `_sinf' function. */
/* #undef _GLIBCXX_HAVE__SINF */

/* Define to 1 if you have the `_sinhf' function. */
/* #undef _GLIBCXX_HAVE__SINHF */

/* Define to 1 if you have the `_sinhl' function. */
/* #undef _GLIBCXX_HAVE__SINHL */

/* Define to 1 if you have the `_sinl' function. */
/* #undef _GLIBCXX_HAVE__SINL */

/* Define to 1 if you have the `_sqrtf' function. */
/* #undef _GLIBCXX_HAVE__SQRTF */

/* Define to 1 if you have the `_sqrtl' function. */
/* #undef _GLIBCXX_HAVE__SQRTL */

/* Define to 1 if you have the `_tanf' function. */
/* #undef _GLIBCXX_HAVE__TANF */

/* Define to 1 if you have the `_tanhf' function. */
/* #undef _GLIBCXX_HAVE__TANHF */

/* Define to 1 if you have the `_tanhl' function. */
/* #undef _GLIBCXX_HAVE__TANHL */

/* Define to 1 if you have the `_tanl' function. */
/* #undef _GLIBCXX_HAVE__TANL */

/* Define to 1 if you have the `_wfopen' function. */
/* #undef _GLIBCXX_HAVE__WFOPEN */

/* Define to 1 if you have the `__cxa_thread_atexit' function. */
/* #undef _GLIBCXX_HAVE___CXA_THREAD_ATEXIT */

/* Define to 1 if you have the `__cxa_thread_atexit_impl' function. */


/* Define as const if the declaration of iconv() needs const. */


/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */


/* Name of package */
/* #undef _GLIBCXX_PACKAGE */

/* Define to the address where bug reports for this package should be sent. */


/* Define to the full name of this package. */


/* Define to the full name and version of this package. */


/* Define to the one symbol short name of this package. */


/* Define to the home page for this package. */


/* Define to the version of this package. */


/* The size of `char', as computed by sizeof. */
/* #undef SIZEOF_CHAR */

/* The size of `int', as computed by sizeof. */
/* #undef SIZEOF_INT */

/* The size of `long', as computed by sizeof. */
/* #undef SIZEOF_LONG */

/* The size of `short', as computed by sizeof. */
/* #undef SIZEOF_SHORT */

/* The size of `void *', as computed by sizeof. */
/* #undef SIZEOF_VOID_P */

/* Define to 1 if you have the ANSI C header files. */


/* Version number of package */
/* #undef _GLIBCXX_VERSION */

/* Enable large inode numbers on Mac OS X 10.5.  */




/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _GLIBCXX_FILE_OFFSET_BITS */

/* Define if C99 functions in <complex.h> should be used in <complex> for
   C++11. Using compiler builtins for these functions requires corresponding
   C99 library functions to be present. */


/* Define if C99 functions or macros in <math.h> should be imported in <cmath>
   in namespace std for C++11. */


/* Define if C99 functions or macros in <stdio.h> should be imported in
   <cstdio> in namespace std for C++11. */


/* Define if C99 functions or macros in <stdlib.h> should be imported in
   <cstdlib> in namespace std for C++11. */


/* Define if C99 functions or macros in <wchar.h> should be imported in
   <cwchar> in namespace std for C++11. */


/* Define if C99 functions in <complex.h> should be used in <complex> for
   C++98. Using compiler builtins for these functions requires corresponding
   C99 library functions to be present. */


/* Define if C99 functions or macros in <math.h> should be imported in <cmath>
   in namespace std for C++98. */


/* Define if C99 functions or macros in <stdio.h> should be imported in
   <cstdio> in namespace std for C++98. */


/* Define if C99 functions or macros in <stdlib.h> should be imported in
   <cstdlib> in namespace std for C++98. */


/* Define if C99 functions or macros in <wchar.h> should be imported in
   <cwchar> in namespace std for C++98. */


/* Define if the compiler supports C++11 atomics. */


/* Define to use concept checking code from the boost libraries. */
/* #undef _GLIBCXX_CONCEPT_CHECKS */

/* Define to 1 if a fully dynamic basic_string is wanted, 0 to disable,
   undefined for platform defaults */


/* Define if gthreads library is available. */


/* Define to 1 if a full hosted library is built, or 0 if freestanding. */


/* Define if compatibility should be provided for -mlong-double-64. */

/* Define to the letter to which size_t is mangled. */


/* Define if C99 llrint and llround functions are missing from <math.h>. */
/* #undef _GLIBCXX_NO_C99_ROUNDING_FUNCS */

/* Define if ptrdiff_t is int. */
/* #undef _GLIBCXX_PTRDIFF_T_IS_INT */

/* Define if using setrlimit to set resource limits during "make check" */


/* Define if size_t is unsigned int. */
/* #undef _GLIBCXX_SIZE_T_IS_UINT */

/* Define to the value of the EOF integer constant. */


/* Define to the value of the SEEK_CUR integer constant. */


/* Define to the value of the SEEK_END integer constant. */


/* Define to use symbol versioning in the shared library. */


/* Define to use darwin versioning in the shared library. */
/* #undef _GLIBCXX_SYMVER_DARWIN */

/* Define to use GNU versioning in the shared library. */


/* Define to use GNU namespace versioning in the shared library. */
/* #undef _GLIBCXX_SYMVER_GNU_NAMESPACE */

/* Define to use Sun versioning in the shared library. */
/* #undef _GLIBCXX_SYMVER_SUN */

/* Define if C11 functions in <uchar.h> should be imported into namespace std
   in <cuchar>. */


/* Define if C99 functions or macros from <wchar.h>, <math.h>, <complex.h>,
   <stdio.h>, and <stdlib.h> can be used or exposed. */


/* Define if C99 functions in <complex.h> should be used in <tr1/complex>.
   Using compiler builtins for these functions requires corresponding C99
   library functions to be present. */


/* Define if C99 functions in <ctype.h> should be imported in <tr1/cctype> in
   namespace std::tr1. */


/* Define if C99 functions in <fenv.h> should be imported in <tr1/cfenv> in
   namespace std::tr1. */


/* Define if C99 functions in <inttypes.h> should be imported in
   <tr1/cinttypes> in namespace std::tr1. */


/* Define if wchar_t C99 functions in <inttypes.h> should be imported in
   <tr1/cinttypes> in namespace std::tr1. */


/* Define if C99 functions or macros in <math.h> should be imported in
   <tr1/cmath> in namespace std::tr1. */


/* Define if C99 types in <stdint.h> should be imported in <tr1/cstdint> in
   namespace std::tr1. */


/* Defined if clock_gettime syscall has monotonic and realtime clock support.
   */
/* #undef _GLIBCXX_USE_CLOCK_GETTIME_SYSCALL */

/* Defined if clock_gettime has monotonic clock support. */


/* Defined if clock_gettime has realtime clock support. */


/* Define if ISO/IEC TR 24733 decimal floating point types are supported on
   this host. */


/* Define if /dev/random and /dev/urandom are available for
   std::random_device. */


/* Define if fchmod is available in <sys/stat.h>. */


/* Define if fchmodat is available in <sys/stat.h>. */


/* Defined if gettimeofday is available. */


/* Define if get_nprocs is available in <sys/sysinfo.h>. */


/* Define if __int128 is supported on this host. */


/* Define if LFS support is available. */


/* Define if code specialized for long long should be used. */


/* Define if lstat is available in <sys/stat.h>. */


/* Defined if nanosleep is available. */


/* Define if NLS translations are to be used. */


/* Define if pthreads_num_processors_np is available in <pthread.h>. */
/* #undef _GLIBCXX_USE_PTHREADS_NUM_PROCESSORS_NP */

/* Define if pthread_cond_clockwait is available in <pthread.h>. */


/* Define if pthread_mutex_clocklock is available in <pthread.h>. */


/* Define if pthread_rwlock_clockrdlock and pthread_rwlock_clockwrlock are
   available in <pthread.h>. */


/* Define if POSIX read/write locks are available in <gthr.h>. */


/* Define if /dev/random and /dev/urandom are available for the random_device
   of TR1 (Chapter 5.1). */


/* Define if usable realpath is available in <stdlib.h>. */


/* Defined if sched_yield is available. */


/* Define if _SC_NPROCESSORS_ONLN is available in <unistd.h>. */


/* Define if _SC_NPROC_ONLN is available in <unistd.h>. */
/* #undef _GLIBCXX_USE_SC_NPROC_ONLN */

/* Define if sendfile is available in <sys/sendfile.h>. */


/* Define if struct stat has timespec members. */


/* Define if sysctl(), CTL_HW and HW_NCPU are available in <sys/sysctl.h>. */
/* #undef _GLIBCXX_USE_SYSCTL_HW_NCPU */

/* Define if obsolescent tmpnam is available in <stdio.h>. */


/* Define if utime is available in <utime.h>. */


/* Define if utimensat and UTIME_OMIT are available in <sys/stat.h> and
   AT_FDCWD in <fcntl.h>. */


/* Define if code specialized for wchar_t should be used. */


/* Define to 1 if a verbose library is built, or 0 otherwise. */


/* Defined if as can handle rdrand. */


/* Defined if as can handle rdseed. */


/* Define to 1 if mutex_timedlock is available. */


/* Define for large files, on AIX-style hosts. */
/* #undef _GLIBCXX_LARGE_FILES */

/* Define if all C++11 floating point overloads are available in <math.h>.  */

/* #undef __CORRECT_ISO_CPP11_MATH_H_PROTO_FP */


/* Define if all C++11 integral type overloads are available in <math.h>.  */

/* #undef __CORRECT_ISO_CPP11_MATH_H_PROTO_INT */
# 39 "/usr/include/c++/10/cstdint" 2 3


# 1 "/usr/lib/gcc/x86_64-linux-gnu/10/include/stdint.h" 1 3 4
# 9 "/usr/lib/gcc/x86_64-linux-gnu/10/include/stdint.h" 3 4
# 1 "/usr/include/stdint.h" 1 3 4
/* Copyright (C) 1997-2020 Free Software Foundation, Inc.
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
   <https://www.gnu.org/licenses/>.  */

/*
 *	ISO C99: 7.18 Integer types <stdint.h>
 */





# 1 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 1 3 4
/* Handle feature test macros at the start of a header.
   Copyright (C) 2016-2020 Free Software Foundation, Inc.
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
   <https://www.gnu.org/licenses/>.  */

/* This header is internal to glibc and should not be included outside
   of glibc headers.  Headers including it must define
   __GLIBC_INTERNAL_STARTING_HEADER_IMPLEMENTATION first.  This header
   cannot have multiple include guards because ISO C feature test
   macros depend on the definition of the macro when an affected
   header is included, not when the first system header is
   included.  */







# 1 "/usr/include/features.h" 1 3 4
/* Copyright (C) 1991-2020 Free Software Foundation, Inc.
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
   <https://www.gnu.org/licenses/>.  */
# 34 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 2 3 4

/* ISO/IEC TR 24731-2:2010 defines the __STDC_WANT_LIB_EXT2__
   macro.  */
# 45 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 3 4
/* ISO/IEC TS 18661-1:2014 defines the __STDC_WANT_IEC_60559_BFP_EXT__
   macro.  Most but not all symbols enabled by that macro in TS
   18661-1 are enabled unconditionally in C2X; the symbols in Annex F
   still require that macro in C2X.  */
# 62 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 3 4
/* ISO/IEC TS 18661-4:2015 defines the
   __STDC_WANT_IEC_60559_FUNCS_EXT__ macro.  Other than the reduction
   functions, the symbols from this TS are enabled unconditionally in
   C2X.  */
# 79 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 3 4
/* ISO/IEC TS 18661-3:2015 defines the
   __STDC_WANT_IEC_60559_TYPES_EXT__ macro.  */
# 27 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types.h" 1 3 4
/* bits/types.h -- definitions of __*_t types underlying *_t types.
   Copyright (C) 2002-2020 Free Software Foundation, Inc.
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
   <https://www.gnu.org/licenses/>.  */

/*
 * Never include this file directly; use <sys/types.h> instead.
 */




# 1 "/usr/include/features.h" 1 3 4
/* Copyright (C) 1991-2020 Free Software Foundation, Inc.
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
   <https://www.gnu.org/licenses/>.  */
# 27 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
/* Determine the wordsize from the preprocessor defines.  */
# 13 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 3 4
/* Both x86-64 and x32 use the 64-bit system call interface.  */
# 28 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/timesize.h" 1 3 4
/* Bit size of the time_t type at glibc build time, x86-64 and x32 case.
   Copyright (C) 2018-2020 Free Software Foundation, Inc.
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
   <https://www.gnu.org/licenses/>.  */





/* For others, time size is word size.  */
# 29 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4

/* Convenience types.  */
typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;

/* Fixed-size types, underlying types depend on word size and compiler.  */
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;





/* Smallest types with at least a given width.  */
typedef __int8_t __int_least8_t;
typedef __uint8_t __uint_least8_t;
typedef __int16_t __int_least16_t;
typedef __uint16_t __uint_least16_t;
typedef __int32_t __int_least32_t;
typedef __uint32_t __uint_least32_t;
typedef __int64_t __int_least64_t;
typedef __uint64_t __uint_least64_t;

/* quad_t is also 64 bits.  */

typedef long int __quad_t;
typedef unsigned long int __u_quad_t;





/* Largest integral types.  */

typedef long int __intmax_t;
typedef unsigned long int __uintmax_t;






/* The machine-dependent file <bits/typesizes.h> defines __*_T_TYPE
   macros for each of the OS types we define below.  The definitions
   of those macros must use the following macros for underlying types.
   We define __S<SIZE>_TYPE and __U<SIZE>_TYPE for the signed and unsigned
   variants of each of the following integer types on this machine.

	16		-- "natural" 16-bit type (always short)
	32		-- "natural" 32-bit type (always int)
	64		-- "natural" 64-bit type (long or long long)
	LONG32		-- 32-bit type, traditionally long
	QUAD		-- 64-bit type, traditionally long long
	WORD		-- natural type of __WORDSIZE bits (int or long)
	LONGWORD	-- type of __WORDSIZE bits, traditionally long

   We distinguish WORD/LONGWORD, 32/LONG32, and 64/QUAD so that the
   conventional uses of `long' or `long long' type modifiers match the
   types we define, even when a less-adorned type would be the same size.
   This matters for (somewhat) portably writing printf/scanf formats for
   these types, where using the appropriate l or ll format modifiers can
   make the typedefs and the formats match up across all GNU platforms.  If
   we used `long' when it's 64 bits where `long long' is expected, then the
   compiler would warn about the formats not matching the argument types,
   and the programmer changing them to shut up the compiler would break the
   program's portability.

   Here we assume what is presently the case in all the GCC configurations
   we support: long long is always 64 bits, long is always word/address size,
   and int is always 32 bits.  */
# 136 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4
/* No need to mark the typedef with __extension__.   */




# 1 "/usr/include/x86_64-linux-gnu/bits/typesizes.h" 1 3 4
/* bits/typesizes.h -- underlying types for *_t.  Linux/x86-64 version.
   Copyright (C) 2012-2020 Free Software Foundation, Inc.
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
   <https://www.gnu.org/licenses/>.  */
# 26 "/usr/include/x86_64-linux-gnu/bits/typesizes.h" 3 4
/* See <bits/types.h> for the meaning of these macros.  This file exists so
   that <bits/types.h> need not vary across different GNU platforms.  */

/* X32 kernel interface is 64-bit.  */
# 77 "/usr/include/x86_64-linux-gnu/bits/typesizes.h" 3 4
/* Tell the libc code that off_t and off64_t are actually the same type
   for all ABI purposes, even if possibly expressed as different base types
   for C type-checking purposes.  */


/* Same for ino_t and ino64_t.  */


/* And for __rlim_t and __rlim64_t.  */


/* And for fsblkcnt_t, fsblkcnt64_t, fsfilcnt_t and fsfilcnt64_t.  */







/* Number of descriptors that can fit in an `fd_set'.  */
# 142 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/time64.h" 1 3 4
/* bits/time64.h -- underlying types for __time64_t.  Generic version.
   Copyright (C) 2018-2020 Free Software Foundation, Inc.
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
   <https://www.gnu.org/licenses/>.  */
# 26 "/usr/include/x86_64-linux-gnu/bits/time64.h" 3 4
/* Define __TIME64_T_TYPE so that it is always a 64-bit type.  */


/* If we already have 64-bit time type then use it.  */
# 143 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4


typedef unsigned long int __dev_t; /* Type of device numbers.  */
typedef unsigned int __uid_t; /* Type of user identifications.  */
typedef unsigned int __gid_t; /* Type of group identifications.  */
typedef unsigned long int __ino_t; /* Type of file serial numbers.  */
typedef unsigned long int __ino64_t; /* Type of file serial numbers (LFS).*/
typedef unsigned int __mode_t; /* Type of file attribute bitmasks.  */
typedef unsigned long int __nlink_t; /* Type of file link counts.  */
typedef long int __off_t; /* Type of file sizes and offsets.  */
typedef long int __off64_t; /* Type of file sizes and offsets (LFS).  */
typedef int __pid_t; /* Type of process identifications.  */
typedef struct { int __val[2]; } __fsid_t; /* Type of file system IDs.  */
typedef long int __clock_t; /* Type of CPU usage counts.  */
typedef unsigned long int __rlim_t; /* Type for resource measurement.  */
typedef unsigned long int __rlim64_t; /* Type for resource measurement (LFS).  */
typedef unsigned int __id_t; /* General type for IDs.  */
typedef long int __time_t; /* Seconds since the Epoch.  */
typedef unsigned int __useconds_t; /* Count of microseconds.  */
typedef long int __suseconds_t; /* Signed count of microseconds.  */

typedef int __daddr_t; /* The type of a disk address.  */
typedef int __key_t; /* Type of an IPC key.  */

/* Clock ID used in clock and timer functions.  */
typedef int __clockid_t;

/* Timer ID returned by `timer_create'.  */
typedef void * __timer_t;

/* Type to represent block size.  */
typedef long int __blksize_t;

/* Types from the Large File Support interface.  */

/* Type to count number of disk blocks.  */
typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;

/* Type to count file system blocks.  */
typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;

/* Type to count file system nodes.  */
typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;

/* Type of miscellaneous file system fields.  */
typedef long int __fsword_t;

typedef long int __ssize_t; /* Type of a byte count, or error.  */

/* Signed long type used in system calls.  */
typedef long int __syscall_slong_t;
/* Unsigned long type used in system calls.  */
typedef unsigned long int __syscall_ulong_t;

/* These few don't really vary by system, they always correspond
   to one of the other defined types.  */
typedef __off64_t __loff_t; /* Type of file sizes and offsets (LFS).  */
typedef char *__caddr_t;

/* Duplicates info from stdint.h but this is used in unistd.h.  */
typedef long int __intptr_t;

/* Duplicate info from sys/socket.h.  */
typedef unsigned int __socklen_t;

/* C99: An integer type that can be accessed as an atomic entity,
   even in the presence of asynchronous interrupts.
   It is not currently necessary for this to be machine-specific.  */
typedef int __sig_atomic_t;

/* Seconds since the Epoch, visible to user code when time_t is too
   narrow only for consistency with the old way of widening too-narrow
   types.  User code should never use __time64_t.  */
# 28 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wchar.h" 1 3 4
/* wchar_t type related definitions.
   Copyright (C) 2000-2020 Free Software Foundation, Inc.
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
   <https://www.gnu.org/licenses/>.  */




/* The fallback definitions, for when __WCHAR_MAX__ or __WCHAR_MIN__
   are not defined, give the right value and type as long as both int
   and wchar_t are 32-bit types.  Adding L'\0' to a constant value
   ensures that the type is correct; it is necessary to use (L'\0' +
   0) rather than just L'\0' so that the type in C++ is the promoted
   version of wchar_t rather than the distinct wchar_t type itself.
   Because wchar_t in preprocessor #if expressions is treated as
   intmax_t or uintmax_t, the expression (L'\0' - 1) would have the
   wrong value for WCHAR_MAX in such expressions and so cannot be used
   to define __WCHAR_MAX in the unsigned case.  */
# 29 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
/* Determine the wordsize from the preprocessor defines.  */
# 13 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 3 4
/* Both x86-64 and x32 use the 64-bit system call interface.  */
# 30 "/usr/include/stdint.h" 2 3 4

/* Exact integral types.  */

/* Signed.  */
# 1 "/usr/include/x86_64-linux-gnu/bits/stdint-intn.h" 1 3 4
/* Define intN_t types.
   Copyright (C) 2017-2020 Free Software Foundation, Inc.
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
   <https://www.gnu.org/licenses/>.  */




# 1 "/usr/include/x86_64-linux-gnu/bits/types.h" 1 3 4
/* bits/types.h -- definitions of __*_t types underlying *_t types.
   Copyright (C) 2002-2020 Free Software Foundation, Inc.
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
   <https://www.gnu.org/licenses/>.  */

/*
 * Never include this file directly; use <sys/types.h> instead.
 */
# 23 "/usr/include/x86_64-linux-gnu/bits/stdint-intn.h" 2 3 4

typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
typedef __int64_t int64_t;
# 35 "/usr/include/stdint.h" 2 3 4

/* Unsigned.  */
# 1 "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h" 1 3 4
/* Define uintN_t types.
   Copyright (C) 2017-2020 Free Software Foundation, Inc.
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
   <https://www.gnu.org/licenses/>.  */




# 1 "/usr/include/x86_64-linux-gnu/bits/types.h" 1 3 4
/* bits/types.h -- definitions of __*_t types underlying *_t types.
   Copyright (C) 2002-2020 Free Software Foundation, Inc.
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
   <https://www.gnu.org/licenses/>.  */

/*
 * Never include this file directly; use <sys/types.h> instead.
 */
# 23 "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h" 2 3 4

typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __uint64_t uint64_t;
# 38 "/usr/include/stdint.h" 2 3 4


/* Small types.  */

/* Signed.  */
typedef __int_least8_t int_least8_t;
typedef __int_least16_t int_least16_t;
typedef __int_least32_t int_least32_t;
typedef __int_least64_t int_least64_t;

/* Unsigned.  */
typedef __uint_least8_t uint_least8_t;
typedef __uint_least16_t uint_least16_t;
typedef __uint_least32_t uint_least32_t;
typedef __uint_least64_t uint_least64_t;


/* Fast types.  */

/* Signed.  */
typedef signed char int_fast8_t;

typedef long int int_fast16_t;
typedef long int int_fast32_t;
typedef long int int_fast64_t;







/* Unsigned.  */
typedef unsigned char uint_fast8_t;

typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long int uint_fast64_t;
# 84 "/usr/include/stdint.h" 3 4
/* Types for `void *' pointers.  */


typedef long int intptr_t;


typedef unsigned long int uintptr_t;
# 100 "/usr/include/stdint.h" 3 4
/* Largest integral types.  */
typedef __intmax_t intmax_t;
typedef __uintmax_t uintmax_t;
# 113 "/usr/include/stdint.h" 3 4
/* Limits of integral types.  */

/* Minimum of signed integral types.  */




/* Maximum of signed integral types.  */





/* Maximum of unsigned integral types.  */






/* Minimum of signed integral types having a minimum size.  */




/* Maximum of signed integral types having a minimum size.  */





/* Maximum of unsigned integral types having a minimum size.  */






/* Minimum of fast signed integral types having a minimum size.  */
# 161 "/usr/include/stdint.h" 3 4
/* Maximum of fast signed integral types having a minimum size.  */
# 172 "/usr/include/stdint.h" 3 4
/* Maximum of fast unsigned integral types having a minimum size.  */
# 184 "/usr/include/stdint.h" 3 4
/* Values to test for integral types holding `void *' pointer.  */
# 196 "/usr/include/stdint.h" 3 4
/* Minimum for largest signed integral type.  */

/* Maximum for largest signed integral type.  */


/* Maximum for largest unsigned integral type.  */



/* Limits of other integer types.  */

/* Limits of `ptrdiff_t' type.  */
# 221 "/usr/include/stdint.h" 3 4
/* Limits of `sig_atomic_t'.  */



/* Limit of `size_t' type.  */
# 236 "/usr/include/stdint.h" 3 4
/* Limits of `wchar_t'.  */

/* These constants might also be defined in <wchar.h>.  */




/* Limits of `wint_t'.  */



/* Signed.  */
# 257 "/usr/include/stdint.h" 3 4
/* Unsigned.  */
# 267 "/usr/include/stdint.h" 3 4
/* Maximal type.  */
# 10 "/usr/lib/gcc/x86_64-linux-gnu/10/include/stdint.h" 2 3 4
# 42 "/usr/include/c++/10/cstdint" 2 3


namespace std
{

  using ::int8_t;
  using ::int16_t;
  using ::int32_t;
  using ::int64_t;

  using ::int_fast8_t;
  using ::int_fast16_t;
  using ::int_fast32_t;
  using ::int_fast64_t;

  using ::int_least8_t;
  using ::int_least16_t;
  using ::int_least32_t;
  using ::int_least64_t;

  using ::intmax_t;
  using ::intptr_t;

  using ::uint8_t;
  using ::uint16_t;
  using ::uint32_t;
  using ::uint64_t;

  using ::uint_fast8_t;
  using ::uint_fast16_t;
  using ::uint_fast32_t;
  using ::uint_fast64_t;

  using ::uint_least8_t;
  using ::uint_least16_t;
  using ::uint_least32_t;
  using ::uint_least64_t;

  using ::uintmax_t;
  using ::uintptr_t;





} // namespace std
# 45 "queue.h" 2


# 46 "queue.h"
//#include <stddef.h>
/*
 * From FREEBSD /sys/sys/cdefs.h
 * */
/*
 * Given the pointer x to the member m of the struct s, return
 * a pointer to the containing structure.  When using GCC, we first
 * assign pointer x to a local variable, to check that its type is
 * compatible with member m.
 */

//Required for GNU macros
# 1 "/usr/include/features.h" 1 3 4

# 1 "/usr/include/features.h" 3 4
/* Copyright (C) 1991-2020 Free Software Foundation, Inc.
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
   <https://www.gnu.org/licenses/>.  */
# 59 "queue.h" 2


# 60 "queue.h"
//Defined in sys/sys/cdefs.h
//#if __GNUC_PREREQ__(4, 1)
# 79 "queue.h"
//#if __GNUC_PREREQ__(3, 1)
# 92 "queue.h"
/*
 * This file defines four types of data structures: singly-linked lists,
 * singly-linked tail queues, lists and tail queues.
 *
 * A singly-linked list is headed by a single forward pointer. The elements
 * are singly linked for minimum space and pointer manipulation overhead at
 * the expense of O(n) removal for arbitrary elements. New elements can be
 * added to the list after an existing element or at the head of the list.
 * Elements being removed from the head of the list should use the explicit
 * macro for this purpose for optimum efficiency. A singly-linked list may
 * only be traversed in the forward direction.  Singly-linked lists are ideal
 * for applications with large datasets and few or no removals or for
 * implementing a LIFO queue.
 *
 * A singly-linked tail queue is headed by a pair of pointers, one to the
 * head of the list and the other to the tail of the list. The elements are
 * singly linked for minimum space and pointer manipulation overhead at the
 * expense of O(n) removal for arbitrary elements. New elements can be added
 * to the list after an existing element, at the head of the list, or at the
 * end of the list. Elements being removed from the head of the tail queue
 * should use the explicit macro for this purpose for optimum efficiency.
 * A singly-linked tail queue may only be traversed in the forward direction.
 * Singly-linked tail queues are ideal for applications with large datasets
 * and few or no removals or for implementing a FIFO queue.
 *
 * A list is headed by a single forward pointer (or an array of forward
 * pointers for a hash table header). The elements are doubly linked
 * so that an arbitrary element can be removed without a need to
 * traverse the list. New elements can be added to the list before
 * or after an existing element or at the head of the list. A list
 * may be traversed in either direction.
 *
 * A tail queue is headed by a pair of pointers, one to the head of the
 * list and the other to the tail of the list. The elements are doubly
 * linked so that an arbitrary element can be removed without a need to
 * traverse the list. New elements can be added to the list before or
 * after an existing element, at the head of the list, or at the end of
 * the list. A tail queue may be traversed in either direction.
 *
 * For details on the use of these macros, see the queue(3) manual page.
 *
 * Below is a summary of implemented functions where:
 *  +  means the macro is available
 *  -  means the macro is not available
 *  s  means the macro is available but is slow (runs in O(n) time)
 *
 *				SLIST	LIST	STAILQ	TAILQ
 * _HEAD			+	+	+	+
 * _CLASS_HEAD			+	+	+	+
 * _HEAD_INITIALIZER		+	+	+	+
 * _ENTRY			+	+	+	+
 * _CLASS_ENTRY			+	+	+	+
 * _INIT			+	+	+	+
 * _EMPTY			+	+	+	+
 * _END				+	+	+	+
 * _FIRST			+	+	+	+
 * _NEXT			+	+	+	+
 * _PREV			-	+	-	+
 * _LAST			-	-	+	+
 * _LAST_FAST			-	-	-	+
 * _FOREACH			+	+	+	+
 * _FOREACH_FROM		+	+	+	+
 * _FOREACH_SAFE		+	+	+	+
 * _FOREACH_FROM_SAFE		+	+	+	+
 * _FOREACH_REVERSE		-	-	-	+
 * _FOREACH_REVERSE_FROM	-	-	-	+
 * _FOREACH_REVERSE_SAFE	-	-	-	+
 * _FOREACH_REVERSE_FROM_SAFE	-	-	-	+
 * _INSERT_HEAD			+	+	+	+
 * _INSERT_BEFORE		-	+	-	+
 * _INSERT_AFTER		+	+	+	+
 * _INSERT_TAIL			-	-	+	+
 * _CONCAT			s	s	+	+
 * _REMOVE_AFTER		+	-	+	-
 * _REMOVE_HEAD			+	-	+	-
 * _REMOVE			s	+	s	+
 * _SWAP			+	+	+	+
 *
 */
# 221 "queue.h"
/*
 * In C++ there can be structure lists and class lists:
 */





/*
 * Singly-linked List declarations.
 */
# 255 "queue.h"
/*
 * Singly-linked List functions.
 */
# 363 "queue.h"
/*
 * Singly-linked Tail queue declarations.
 */
# 391 "queue.h"
/*
 * Singly-linked Tail queue functions.
 */
# 498 "queue.h"
/*
 * List declarations.
 */
# 526 "queue.h"
/*
 * List functions.
 */
# 674 "queue.h"
/*
 * Tail queue declarations.
 */
# 708 "queue.h"
/*
 * Tail queue functions.
 */
# 876 "queue.h"
/*
 * The FAST function is fast in that it causes no data access other
 * then the access to the head. The standard LAST function above
 * will cause a data access of both the element you want and
 * the previous element. FAST is very useful for instances when
 * you may want to prefetch the last data element.
 */
# 7 "queue_impl.h" 2

struct IntegerSLISTEntry {
    int data;
    struct { struct IntegerSLISTEntry *sle_next; } entries; /* Singly linked list */
};

struct mySinglyLinkedListHead { struct IntegerSLISTEntry *slh_first; };


struct IntegerSTAILQueueNode {
    int data;
    struct { struct IntegerSTAILQueueNode *stqe_next; } entries;
};

struct mySTAILQueueHead { struct IntegerSTAILQueueNode *stqh_first; struct IntegerSTAILQueueNode **stqh_last; };


struct myLISTHead { struct IntegerLISTEntry *lh_first; };

struct IntegerLISTEntry {
    int data;
    struct { struct IntegerLISTEntry *le_next; struct IntegerLISTEntry **le_prev; } entries;
};

struct myTAILQueueHead { struct IntegerTAILQueueNode *tqh_first; struct IntegerTAILQueueNode **tqh_last; };

struct IntegerTAILQueueNode {
    int data;
    struct { struct IntegerTAILQueueNode *tqe_next; struct IntegerTAILQueueNode **tqe_prev; } entries;
};


//When inlining the functions, no coverage was generated by gcov. Maybe solvable
//but it shouldn't affect functionality only performance.

//List
void SLIST_INIT_impl(mySinglyLinkedListHead*);
void SLIST_CONCAT_impl(mySinglyLinkedListHead* head1, mySinglyLinkedListHead* head2);
bool SLIST_EMPTY_impl(mySinglyLinkedListHead* head);
void SLIST_INSERT_AFTER_impl(IntegerSLISTEntry* slistelm, IntegerSLISTEntry* elm);
void SLIST_INSERT_HEAD_impl(mySinglyLinkedListHead* head,IntegerSLISTEntry* elm);
void SLIST_REMOVE_impl(mySinglyLinkedListHead* head, IntegerSLISTEntry* elm);
void SLIST_REMOVE_AFTER_impl(IntegerSLISTEntry* elm);
void SLIST_REMOVE_HEAD_impl(mySinglyLinkedListHead* head);
void SLIST_REMOVE_PREVPTR_impl(IntegerSLISTEntry**, IntegerSLISTEntry*);
void SLIST_SWAP_impl(mySinglyLinkedListHead*,mySinglyLinkedListHead*);
IntegerSLISTEntry* SLIST_END_impl(mySinglyLinkedListHead*);
IntegerSLISTEntry* SLIST_FIRST_impl(mySinglyLinkedListHead* h);

//Singly Linked Tail Queue
mySTAILQueueHead STAILQ_HEAD_INITIALIZER_impl(mySTAILQueueHead* head);
void STAILQ_CONCAT_impl(mySTAILQueueHead* head1,mySTAILQueueHead* head2);
bool STAILQ_EMPTY_impl(mySTAILQueueHead *head);
IntegerSTAILQueueNode* STAILQ_FIRST_impl(mySTAILQueueHead *head);
void STAILQ_INIT_impl(mySTAILQueueHead* head);
void STAILQ_INSERT_AFTER_impl(mySTAILQueueHead* head, IntegerSTAILQueueNode* tqelm,IntegerSTAILQueueNode* elm);
void STAILQ_INSERT_HEAD_impl(mySTAILQueueHead* head,IntegerSTAILQueueNode* elm);
void STAILQ_INSERT_TAIL_impl(mySTAILQueueHead* head,IntegerSTAILQueueNode* elm);
IntegerSTAILQueueNode* STAILQ_LAST_impl(mySTAILQueueHead* head);
IntegerSTAILQueueNode* STAILQ_NEXT_impl(IntegerSTAILQueueNode* elm);
void STAILQ_REMOVE_impl(mySTAILQueueHead* head,IntegerSTAILQueueNode* elm);
void STAILQ_REMOVE_AFTER_impl(mySTAILQueueHead* head,IntegerSTAILQueueNode* elm);
void STAILQ_REMOVE_HEAD_impl(mySTAILQueueHead* head);
void STAILQ_SWAP_impl(mySTAILQueueHead* head1,mySTAILQueueHead* head2);
IntegerSTAILQueueNode* STAILQ_END_impl(mySTAILQueueHead* head);

//doubly linked list
void LIST_CONCAT_impl(myLISTHead* , myLISTHead*);
bool LIST_EMPTY_impl(myLISTHead*);
IntegerLISTEntry* LIST_FIRST_impl(myLISTHead*);
void LIST_INIT_impl(myLISTHead* );
void LIST_INSERT_AFTER_impl(IntegerLISTEntry*, IntegerLISTEntry*);
void LIST_INSERT_BEFORE_impl(IntegerLISTEntry* , IntegerLISTEntry*);
void LIST_INSERT_HEAD_impl(myLISTHead*,IntegerLISTEntry*);
IntegerLISTEntry* LIST_NEXT_impl(IntegerLISTEntry*);
IntegerLISTEntry* LIST_PREV_impl(IntegerLISTEntry*, myLISTHead*);
void LIST_REMOVE_impl(IntegerLISTEntry*);
void LIST_SWAP_impl(myLISTHead*, myLISTHead*);
IntegerLISTEntry* LIST_END_impl(myLISTHead*);

//TAILQ, double linked Tail Queue
void TAILQ_CONCAT_impl(myTAILQueueHead* ,myTAILQueueHead*);
bool TAILQ_EMPTY_impl(myTAILQueueHead*);
IntegerTAILQueueNode* TAILQ_FIRST_impl(myTAILQueueHead *);
void TAILQ_INIT_impl(myTAILQueueHead*);
void TAILQ_INSERT_AFTER_impl(myTAILQueueHead* ,IntegerTAILQueueNode* , IntegerTAILQueueNode*);
void TAILQ_INSERT_BEFORE_impl(IntegerTAILQueueNode*, IntegerTAILQueueNode*);
void TAILQ_INSERT_HEAD_impl(myTAILQueueHead* , IntegerTAILQueueNode*);
void TAILQ_INSERT_TAIL_impl(myTAILQueueHead* , IntegerTAILQueueNode*);
IntegerTAILQueueNode* TAILQ_LAST_impl(myTAILQueueHead*);
IntegerTAILQueueNode* TAILQ_LAST_FAST_impl(myTAILQueueHead*);

IntegerTAILQueueNode* TAILQ_NEXT_impl(IntegerTAILQueueNode*);
IntegerTAILQueueNode* TAILQ_PREV_impl(IntegerTAILQueueNode*);
IntegerTAILQueueNode* TAILQ_PREV_FAST_impl(IntegerTAILQueueNode*, myTAILQueueHead* );
void TAILQ_REMOVE_impl(myTAILQueueHead* , IntegerTAILQueueNode* );
void TAILQ_SWAP_impl(myTAILQueueHead* , myTAILQueueHead* );
IntegerTAILQueueNode* TAILQ_END_impl(myTAILQueueHead* head);
# 2 "queue_impl_nonexpanded.cpp" 2

//We want to get metrics on coverage, but macros themselves can tell us about coverage
//Inline functions would be more like a macro. Can easily be done, but not when separate definition declaration


//Singly linked list
void SLIST_INIT_impl(mySinglyLinkedListHead* head) {
    do { (((head))->slh_first) = NULL; } while (0);
}
IntegerSLISTEntry* SLIST_FIRST_impl(mySinglyLinkedListHead* head) {
    return ((head)->slh_first);
}

void SLIST_CONCAT_impl(mySinglyLinkedListHead* head1, mySinglyLinkedListHead* head2) {
    do { IntegerSLISTEntry *curelm = ((head1)->slh_first); if (curelm == NULL) { if ((((head1)->slh_first) = ((head2)->slh_first)) != NULL) do { (((head2))->slh_first) = NULL; } while (0); } else if (((head2)->slh_first) != NULL) { while (((curelm)->entries.sle_next) != NULL) curelm = ((curelm)->entries.sle_next); ((curelm)->entries.sle_next) = ((head2)->slh_first); do { (((head2))->slh_first) = NULL; } while (0); } } while (0);
}

bool SLIST_EMPTY_impl(mySinglyLinkedListHead* head) {
    return ((head)->slh_first == NULL);
}

void SLIST_INSERT_AFTER_impl(IntegerSLISTEntry* slistelm, IntegerSLISTEntry* elm) {
    do { (((elm))->entries.sle_next) = (((slistelm))->entries.sle_next); (((slistelm))->entries.sle_next) = (elm); } while (0);
}

void SLIST_INSERT_HEAD_impl(mySinglyLinkedListHead* head,IntegerSLISTEntry* elm) {
    do { (((elm))->entries.sle_next) = (((head))->slh_first); (((head))->slh_first) = (elm); } while (0);
}

IntegerSLISTEntry* SLIST_NEXT_impl(IntegerSLISTEntry* elm) {
    return ((elm)->field.sle_next);
}

void SLIST_REMOVE_impl(mySinglyLinkedListHead* head, IntegerSLISTEntry* elm) {
    do { ; if ((((head))->slh_first) == (elm)) { do { ((((head)))->slh_first) = ((((((head)))->slh_first))->entries.sle_next); } while (0); } else { IntegerSLISTEntry *curelm = ((head)->slh_first); while (((curelm)->entries.sle_next) != (elm)) curelm = ((curelm)->entries.sle_next); do { ((curelm)->entries.sle_next) = ((((curelm)->entries.sle_next))->entries.sle_next); } while (0); } ; } while (0);
}

void SLIST_REMOVE_AFTER_impl(IntegerSLISTEntry* elm) {
    do { ((elm)->entries.sle_next) = ((((elm)->entries.sle_next))->entries.sle_next); } while (0);
}

void SLIST_REMOVE_HEAD_impl(mySinglyLinkedListHead* head) {
    do { (((head))->slh_first) = (((((head))->slh_first))->entries.sle_next); } while (0);
}

void SLIST_REMOVE_PREVPTR_impl(IntegerSLISTEntry** prevp, IntegerSLISTEntry* elm) {
    do { ; *(prevp) = ((elm)->entries.sle_next); ; } while (0);
}
void SLIST_SWAP_impl(mySinglyLinkedListHead* head1,mySinglyLinkedListHead* head2) {
    do { IntegerSLISTEntry *swap_first = ((head1)->slh_first); ((head1)->slh_first) = ((head2)->slh_first); ((head2)->slh_first) = swap_first; } while (0);
}

IntegerSLISTEntry* SLIST_END_impl(mySinglyLinkedListHead *head) {
    return NULL;
}

//Singly Linked Tail Queue
mySTAILQueueHead STAILQ_HEAD_INITIALIZER_impl(mySTAILQueueHead* head){
    return { NULL, &(*head).stqh_first };
}

void STAILQ_CONCAT_impl(mySTAILQueueHead* head1,mySTAILQueueHead* head2){
    do { if (!(((head2))->stqh_first == NULL)) { *(head1)->stqh_last = (head2)->stqh_first; (head1)->stqh_last = (head2)->stqh_last; do { ((((head2)))->stqh_first) = NULL; ((head2))->stqh_last = &((((head2)))->stqh_first); } while (0); } } while (0);
}

bool STAILQ_EMPTY_impl(mySTAILQueueHead *head) {
    return ((head)->stqh_first == NULL);
}

IntegerSTAILQueueNode* STAILQ_FIRST_impl(mySTAILQueueHead *head){
    return ((head)->stqh_first);
}

void STAILQ_INIT_impl(mySTAILQueueHead* head) {
    do { (((head))->stqh_first) = NULL; (head)->stqh_last = &(((head))->stqh_first); } while (0);
}

void STAILQ_INSERT_AFTER_impl(mySTAILQueueHead* head, IntegerSTAILQueueNode* tqelm,IntegerSTAILQueueNode* elm){
    do { if (((((elm))->entries.stqe_next) = (((tqelm))->entries.stqe_next)) == NULL) (head)->stqh_last = &(((elm))->entries.stqe_next); (((tqelm))->entries.stqe_next) = (elm); } while (0);
}

void STAILQ_INSERT_HEAD_impl(mySTAILQueueHead* head, IntegerSTAILQueueNode* elm){
    do { if (((((elm))->entries.stqe_next) = (((head))->stqh_first)) == NULL) (head)->stqh_last = &(((elm))->entries.stqe_next); (((head))->stqh_first) = (elm); } while (0);
}

void STAILQ_INSERT_TAIL_impl(mySTAILQueueHead* head,IntegerSTAILQueueNode* elm){
    do { (((elm))->entries.stqe_next) = NULL; *(head)->stqh_last = (elm); (head)->stqh_last = &(((elm))->entries.stqe_next); } while (0);
}

IntegerSTAILQueueNode* STAILQ_LAST_impl(mySTAILQueueHead* head, IntegerSTAILQueueNode){
    return ((((head))->stqh_first == NULL) ? NULL : ({ const volatile __typeof(((IntegerSTAILQueueNode *)0)->entries.stqe_next) *__x = ((head)->stqh_last); ((IntegerSTAILQueueNode *)(uintptr_t)(const volatile void *)((const volatile char *)__x - __builtin_offsetof(IntegerSTAILQueueNode, entries.stqe_next)));}));
}

IntegerSTAILQueueNode* STAILQ_NEXT_impl(IntegerSTAILQueueNode* elm){
    return ((elm)->entries.stqe_next);
}

void STAILQ_REMOVE_impl(mySTAILQueueHead* head,IntegerSTAILQueueNode* elm, IntegerSTAILQueueNode){
    do { ; if ((((head))->stqh_first) == (elm)) { do { if ((((((head)))->stqh_first) = ((((((head)))->stqh_first))->entries.stqe_next)) == NULL) ((head))->stqh_last = &((((head)))->stqh_first); } while (0); } else { IntegerSTAILQueueNode *curelm = ((head)->stqh_first); while (((curelm)->entries.stqe_next) != (elm)) curelm = ((curelm)->entries.stqe_next); do { if ((((curelm)->entries.stqe_next) = ((((curelm)->entries.stqe_next))->entries.stqe_next)) == NULL) (head)->stqh_last = &(((curelm))->entries.stqe_next); } while (0); } ; } while (0);
}

void STAILQ_REMOVE_AFTER_impl(mySTAILQueueHead* head,IntegerSTAILQueueNode* elm){
    do { if ((((elm)->entries.stqe_next) = ((((elm)->entries.stqe_next))->entries.stqe_next)) == NULL) (head)->stqh_last = &(((elm))->entries.stqe_next); } while (0);
}

void STAILQ_REMOVE_HEAD_impl(mySTAILQueueHead* head) {
    do { if (((((head))->stqh_first) = (((((head))->stqh_first))->entries.stqe_next)) == NULL) (head)->stqh_last = &(((head))->stqh_first); } while (0);
}

void STAILQ_SWAP_impl(mySTAILQueueHead* head1,mySTAILQueueHead* head2, IntegerSTAILQueueNode) {
    do { IntegerSTAILQueueNode *swap_first = ((head1)->stqh_first); IntegerSTAILQueueNode **swap_last = (head1)->stqh_last; ((head1)->stqh_first) = ((head2)->stqh_first); (head1)->stqh_last = (head2)->stqh_last; ((head2)->stqh_first) = swap_first; (head2)->stqh_last = swap_last; if (((head1)->stqh_first == NULL)) (head1)->stqh_last = &((head1)->stqh_first); if (((head2)->stqh_first == NULL)) (head2)->stqh_last = &((head2)->stqh_first); } while (0);
}

IntegerSTAILQueueNode* STAILQ_END_impl(mySTAILQueueHead* head){
    return NULL;
}


void STAILQ_END_impl(mySTAILQueueHead* head){
    NULL;
}

//Doubly linked list
void LIST_CONCAT_impl(myLISTHead* head1, myLISTHead* head2) {
    do { IntegerLISTEntry *curelm = ((head1)->lh_first); if (curelm == NULL) { if ((((head1)->lh_first) = ((head2)->lh_first)) != NULL) { ((head2)->lh_first)->entries.le_prev = &(((head1))->lh_first); do { (((head2))->lh_first) = NULL; } while (0); } } else if (((head2)->lh_first) != NULL) { while (((curelm)->entries.le_next) != NULL) curelm = ((curelm)->entries.le_next); ((curelm)->entries.le_next) = ((head2)->lh_first); ((head2)->lh_first)->entries.le_prev = &((curelm)->entries.le_next); do { (((head2))->lh_first) = NULL; } while (0); } } while (0);
}

bool LIST_EMPTY_impl(myLISTHead* head) {
    return ((head)->lh_first == NULL);
}

IntegerLISTEntry* LIST_FIRST_impl(myLISTHead* head) {
    return ((head)->lh_first);
}

void LIST_INIT_impl(myLISTHead* head) {
    do { (((head))->lh_first) = NULL; } while (0);
}

void LIST_INSERT_AFTER_impl(IntegerLISTEntry* listelm, IntegerLISTEntry* elm) {
    do { ; if (((((elm))->entries.le_next) = (((listelm))->entries.le_next)) != NULL) (((listelm))->entries.le_next)->entries.le_prev = &(((elm))->entries.le_next); (((listelm))->entries.le_next) = (elm); (elm)->entries.le_prev = &(((listelm))->entries.le_next); } while (0);
}

void LIST_INSERT_BEFORE_impl(IntegerLISTEntry* listelm, IntegerLISTEntry* elm) {
    do { ; (elm)->entries.le_prev = (listelm)->entries.le_prev; (((elm))->entries.le_next) = (listelm); *(listelm)->entries.le_prev = (elm); (listelm)->entries.le_prev = &(((elm))->entries.le_next); } while (0);
}

void LIST_INSERT_HEAD_impl(myLISTHead* head,IntegerLISTEntry* elm) {
    do { ; if (((((elm))->entries.le_next) = (((head))->lh_first)) != NULL) (((head))->lh_first)->entries.le_prev = &(((elm))->entries.le_next); (((head))->lh_first) = (elm); (elm)->entries.le_prev = &(((head))->lh_first); } while (0);
}

IntegerLISTEntry* LIST_NEXT_impl(IntegerLISTEntry* elm) {
    return ((elm)->entries.le_next);
}

IntegerLISTEntry* LIST_PREV_impl(IntegerLISTEntry* elm, myLISTHead* head) {
    return ((elm)->entries.le_prev == &(((head))->lh_first) ? NULL : ({ const volatile __typeof(((IntegerLISTEntry *)0)->entries.le_next) *__x = ((elm)->entries.le_prev); ((IntegerLISTEntry *)(uintptr_t)(const volatile void *)((const volatile char *)__x - __builtin_offsetof(IntegerLISTEntry, entries.le_next)));}));
}

void LIST_REMOVE_impl(IntegerLISTEntry* elm) {
    do { ; ; ; ; if ((((elm))->entries.le_next) != NULL) (((elm))->entries.le_next)->entries.le_prev = (elm)->entries.le_prev; *(elm)->entries.le_prev = (((elm))->entries.le_next); ; ; } while (0);
}

void LIST_SWAP_impl(myLISTHead* head1, myLISTHead* head2) {
    do { IntegerLISTEntry *swap_tmp = ((head1)->lh_first); (((head1))->lh_first) = (((head2))->lh_first); (((head2))->lh_first) = swap_tmp; if ((swap_tmp = (((head1))->lh_first)) != NULL) swap_tmp->entries.le_prev = &(((head1))->lh_first); if ((swap_tmp = (((head2))->lh_first)) != NULL) swap_tmp->entries.le_prev = &(((head2))->lh_first); } while (0);
}

IntegerLISTEntry* LIST_END_impl(myLISTHead* head) {
    return NULL;
}

//TAILQ, doubly linked tail queue
void TAILQ_CONCAT_impl(myTAILQueueHead* head1,myTAILQueueHead* head2) {
    do { if (!((head2)->tqh_first == NULL)) { *(head1)->tqh_last = (head2)->tqh_first; (head2)->tqh_first->entries.tqe_prev = (head1)->tqh_last; (head1)->tqh_last = (head2)->tqh_last; do { ((((head2)))->tqh_first) = NULL; ((head2))->tqh_last = &((((head2)))->tqh_first); ; } while (0); ; ; } } while (0);
}

bool TAILQ_EMPTY_impl(myTAILQueueHead* head) {
    return ((head)->tqh_first == NULL);
}

IntegerTAILQueueNode* TAILQ_FIRST_impl(myTAILQueueHead *head) {
    return ((head)->tqh_first);
}

void TAILQ_INIT_impl(myTAILQueueHead* head) {
    do { (((head))->tqh_first) = NULL; (head)->tqh_last = &(((head))->tqh_first); ; } while (0);
}

void TAILQ_INSERT_AFTER_impl(myTAILQueueHead* head,IntegerTAILQueueNode* listelm, IntegerTAILQueueNode* elm) {
    do { ; if (((((elm))->entries.tqe_next) = (((listelm))->entries.tqe_next)) != NULL) (((elm))->entries.tqe_next)->entries.tqe_prev = &(((elm))->entries.tqe_next); else { (head)->tqh_last = &(((elm))->entries.tqe_next); ; } (((listelm))->entries.tqe_next) = (elm); (elm)->entries.tqe_prev = &(((listelm))->entries.tqe_next); ; ; } while (0);
}

void TAILQ_INSERT_BEFORE_impl(IntegerTAILQueueNode* listelm, IntegerTAILQueueNode* elm) {
    do { ; (elm)->entries.tqe_prev = (listelm)->entries.tqe_prev; (((elm))->entries.tqe_next) = (listelm); *(listelm)->entries.tqe_prev = (elm); (listelm)->entries.tqe_prev = &(((elm))->entries.tqe_next); ; ; } while (0);
}

void TAILQ_INSERT_HEAD_impl(myTAILQueueHead* head, IntegerTAILQueueNode* elm) {
    do { ; if (((((elm))->entries.tqe_next) = (((head))->tqh_first)) != NULL) (((head))->tqh_first)->entries.tqe_prev = &(((elm))->entries.tqe_next); else (head)->tqh_last = &(((elm))->entries.tqe_next); (((head))->tqh_first) = (elm); (elm)->entries.tqe_prev = &(((head))->tqh_first); ; ; } while (0);
}

void TAILQ_INSERT_TAIL_impl(myTAILQueueHead* head, IntegerTAILQueueNode* elm) {
    do { ; (((elm))->entries.tqe_next) = NULL; (elm)->entries.tqe_prev = (head)->tqh_last; *(head)->tqh_last = (elm); (head)->tqh_last = &(((elm))->entries.tqe_next); ; ; } while (0);
}

IntegerTAILQueueNode* TAILQ_LAST_impl(myTAILQueueHead* head) {
    return (*(((struct myTAILQueueHead *)((head)->tqh_last))->tqh_last));
}

IntegerTAILQueueNode* TAILQ_LAST_FAST_impl(myTAILQueueHead* head) {
    return (((head)->tqh_first == NULL) ? NULL : ({ const volatile __typeof(((IntegerTAILQueueNode *)0)->entries.tqe_next) *__x = ((head)->tqh_last); ((IntegerTAILQueueNode *)(uintptr_t)(const volatile void *)((const volatile char *)__x - __builtin_offsetof(IntegerTAILQueueNode, entries.tqe_next)));}));
}

IntegerTAILQueueNode* TAILQ_NEXT_impl(IntegerTAILQueueNode* elm) {
    return ((elm)->entries.tqe_next);
}

IntegerTAILQueueNode* TAILQ_PREV_impl(IntegerTAILQueueNode* elm) {
    return (*(((struct myTAILQueueHead *)((elm)->entries.tqe_prev))->tqh_last));
}

IntegerTAILQueueNode* TAILQ_PREV_FAST_impl(IntegerTAILQueueNode* elm, myTAILQueueHead* head ) {
    return ((elm)->entries.tqe_prev == &(head)->tqh_first ? NULL : ({ const volatile __typeof(((IntegerTAILQueueNode *)0)->entries.tqe_next) *__x = ((elm)->entries.tqe_prev); ((IntegerTAILQueueNode *)(uintptr_t)(const volatile void *)((const volatile char *)__x - __builtin_offsetof(IntegerTAILQueueNode, entries.tqe_next)));}));
}

void TAILQ_REMOVE_impl(myTAILQueueHead* head, IntegerTAILQueueNode* elm) {
    do { ; ; ; ; if (((((elm))->entries.tqe_next)) != NULL) (((elm))->entries.tqe_next)->entries.tqe_prev = (elm)->entries.tqe_prev; else { (head)->tqh_last = (elm)->entries.tqe_prev; ; } *(elm)->entries.tqe_prev = (((elm))->entries.tqe_next); ; ; ; } while (0);
}
void TAILQ_SWAP_impl(myTAILQueueHead* head1, myTAILQueueHead* head2) {
    do { IntegerTAILQueueNode *swap_first = (head1)->tqh_first; IntegerTAILQueueNode **swap_last = (head1)->tqh_last; (head1)->tqh_first = (head2)->tqh_first; (head1)->tqh_last = (head2)->tqh_last; (head2)->tqh_first = swap_first; (head2)->tqh_last = swap_last; if ((swap_first = (head1)->tqh_first) != NULL) swap_first->entries.tqe_prev = &(head1)->tqh_first; else (head1)->tqh_last = &(head1)->tqh_first; if ((swap_first = (head2)->tqh_first) != NULL) swap_first->entries.tqe_prev = &(head2)->tqh_first; else (head2)->tqh_last = &(head2)->tqh_first; } while (0);
}

IntegerTAILQueueNode* TAILQ_END_impl(myTAILQueueHead* head) {
    return NULL;
}

//FIELD == entries
//TYPE = IntegerSLISTEntry
//elm = IntegerSLISTEntry
