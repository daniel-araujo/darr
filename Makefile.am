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

TESTS += tests/correct-element-size
check_PROGRAMS += tests/correct-element-size
tests_correct_element_size_SOURCES = src/tests/correct-element-size.c
tests_correct_element_size_LDADD = libdarr.a

TESTS += tests/correct-allocation-size
check_PROGRAMS += tests/correct-allocation-size
tests_correct_allocation_size_SOURCES = src/tests/correct-allocation-size.c
tests_correct_allocation_size_LDADD = libdarr.a

TESTS += tests/copy
check_PROGRAMS += tests/copy
tests_copy_SOURCES = src/tests/copy.c
tests_copy_LDADD = libdarr.a

TESTS += tests/copy-modify
check_PROGRAMS += tests/copy-modify
tests_copy_modify_SOURCES = src/tests/copy-modify.c
tests_copy_modify_LDADD = libdarr.a

TESTS += tests/copy-resize
check_PROGRAMS += tests/copy-resize
tests_copy_resize_SOURCES = src/tests/copy-resize.c
tests_copy_resize_LDADD = libdarr.a

TESTS += tests/begin-end
check_PROGRAMS += tests/begin-end
tests_begin_end_SOURCES = src/tests/begin-end.c
tests_begin_end_LDADD = libdarr.a

TESTS += tests/swap
check_PROGRAMS += tests/swap
tests_swap_SOURCES = src/tests/swap.c
tests_swap_LDADD = libdarr.a

TESTS += tests/empty
check_PROGRAMS += tests/empty
tests_empty_SOURCES = src/tests/empty.c
tests_empty_LDADD = libdarr.a

TESTS += tests/shift
check_PROGRAMS += tests/shift
tests_shift_SOURCES = src/tests/shift.c
tests_shift_LDADD = libdarr.a

TESTS += tests/shift-boundary
check_PROGRAMS += tests/shift-boundary
tests_shift_boundary_SOURCES = src/tests/shift-boundary.c
tests_shift_boundary_LDADD = libdarr.a

TESTS += tests/shrink-grow
check_PROGRAMS += tests/shrink-grow
tests_shrink_grow_SOURCES = src/tests/shrink-grow.c
tests_shrink_grow_LDADD = libdarr.a
