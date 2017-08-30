#include "darr.h"

darr_realloc_t darr_realloc = realloc;

darr_free_t darr_free = free;

extern inline void darr_global_realloc_set(darr_realloc_t f);

extern inline void darr_global_free_set(darr_free_t f);

extern inline size_t darr_data_index(const struct darr *d, size_t i);

extern inline size_t darr_data_size(const struct darr *d);

extern inline void darr_init(struct darr *d, size_t element_size);

extern inline int darr_copy(struct darr *d, const struct darr *other);

extern inline int darr_copy_slice(
	struct darr *d,
	const struct darr *other,
	size_t i,
	size_t s);

extern inline void darr_deinit(struct darr *d);

extern inline size_t darr_size(const struct darr *d);

extern inline void *darr_data(struct darr *d);

extern inline const void *darr_data_const(const struct darr *d);

extern inline int darr_resize(struct darr *d, size_t size);

extern inline void *darr_element(struct darr *d, size_t i);

extern inline const void *darr_element_const(const struct darr *d, size_t i);

extern inline void *darr_begin(struct darr *d);

extern inline const void *darr_begin_const(const struct darr *d);

extern inline void *darr_end(struct darr *d);

extern inline const void *darr_end_const(const struct darr *d);

extern inline void darr_swap(struct darr *d, struct darr *other);

extern inline int darr_empty(const struct darr *d);

extern inline void darr_shift_left(struct darr *d, size_t steps);

extern inline void darr_shift_slice_left(
	struct darr *d,
	size_t steps,
	size_t start,
	size_t size);

extern inline void darr_shift_right(struct darr *d, size_t steps);

extern inline void darr_shift_slice_right(
	struct darr *d,
	size_t steps,
	size_t start,
	size_t size);

extern inline int darr_shrink(struct darr *d, size_t size);

extern inline int darr_grow(struct darr *d, size_t size);

extern inline void *darr_address(struct darr *d, size_t i);

extern inline void *darr_first(struct darr *d);

extern inline const void *darr_first_const(const struct darr *d);

extern inline void *darr_last(struct darr *d);

extern inline const void *darr_last_const(const struct darr *d);

extern inline int darr_append(struct darr *d, const struct darr *other);

extern inline int darr_prepend(struct darr *d, const struct darr *other);

extern inline int darr_insert(
	struct darr *d,
	size_t i,
	const struct darr *other);

extern inline int darr_remove(struct darr *d, size_t start, size_t size);

extern inline int darr_move_slice(
	struct darr *d,
	struct darr *other,
	size_t i,
	size_t s);

extern inline int darr_move(struct darr *d, struct darr *other);
