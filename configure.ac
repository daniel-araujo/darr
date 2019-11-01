AC_PREREQ([2.69])
AC_INIT([darr], [1.7.6], [https://github.com/daniel-araujo/darr/issues])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_CONFIG_SRCDIR([src/darr.h])
AC_CONFIG_FILES([Makefile])

AC_PROG_CC
AC_PROG_RANLIB

AC_TYPE_SIZE_T

# Use C11.
AX_CHECK_COMPILE_FLAG([-std=c11],
	[AX_APPEND_FLAG([-std=c11])],
	[AC_MSG_ERROR([-std=c11 not supported.])])

# Error messages: the more the better.
AX_APPEND_FLAG([-Wall -Wextra])

# Turn certain warning messages into error messages.
AX_CHECK_COMPILE_FLAG([-Werror=incompatible-pointer-types],
	[AX_APPEND_FLAG([-Werror=incompatible-pointer-types])])

# Suppress less desirable warning messages.
AX_APPEND_FLAG([-Wno-unused-variable])

# Allowing C files to rely on being able to include files relative to the src
# directory.
AX_APPEND_FLAG([-iquote $srcdir/src -iquote src])

AC_OUTPUT
