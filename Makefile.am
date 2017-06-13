EXTRA_DIST = README.md
noinst_LIBRARIES =
TESTS =
check_PROGRAMS =

noinst_LIBRARIES += libdarr.a
libdarr_a_SOURCES = \
	src/darr.h \
	src/darr.c

TESTS += tests/init-state
check_PROGRAMS += tests/init-state
tests_init_state_SOURCES = src/tests/init-state.c
tests_init_state_LDADD = libdarr.a

TESTS += tests/resize
check_PROGRAMS += tests/resize
tests_resize_SOURCES = src/tests/resize.c
tests_resize_LDADD = libdarr.a

TESTS += tests/resize-zero
check_PROGRAMS += tests/resize-zero
tests_resize_zero_SOURCES = src/tests/resize-zero.c
tests_resize_zero_LDADD = libdarr.a

TESTS += tests/set
check_PROGRAMS += tests/set
tests_set_SOURCES = src/tests/set.c
tests_set_LDADD = libdarr.a

TESTS += tests/copy
check_PROGRAMS += tests/copy
tests_copy_SOURCES = src/tests/copy.c
tests_copy_LDADD = libdarr.a
