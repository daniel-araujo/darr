EXTRA_DIST = README.md
include_HEADERS =
lib_LIBRARIES =
TESTS =
check_PROGRAMS =

include_HEADERS += src/darr.h
lib_LIBRARIES += libdarr.a
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

TESTS += tests/access-element
check_PROGRAMS += tests/access-element
tests_access_element_SOURCES = src/tests/access-element.c
tests_access_element_LDADD = libdarr.a
