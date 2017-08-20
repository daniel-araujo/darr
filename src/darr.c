#include "darr.h"

darr_realloc_t darr_realloc = realloc;

darr_free_t darr_free = free;

void darr_global_realloc_set(darr_realloc_t f);

void darr_global_free_set(darr_free_t f);

size_t darr_data_index(struct darr *d, size_t i);

size_t darr_data_size(struct darr *d);

void darr_init(struct darr *d, size_t element_size);

int darr_copy(struct darr *d, struct darr *other);

void darr_deinit(struct darr *d);

size_t darr_size(struct darr *d);

void *darr_data(struct darr *d);

int darr_resize(struct darr *d, size_t size);

void *darr_element(struct darr *d, size_t i);

void *darr_begin(struct darr *d);

void *darr_end(struct darr *d);

void darr_swap(struct darr *d, struct darr *other);

int darr_empty(struct darr *d);

void darr_shift_left(struct darr *d, size_t steps);

void darr_shift_right(struct darr *d, size_t steps);

int darr_shrink(struct darr *d, size_t size);

int darr_grow(struct darr *d, size_t size);

void *darr_address(struct darr *d, size_t i);

void *darr_first(struct darr *d);

void *darr_last(struct darr *d);

int darr_append(struct darr *d, struct darr *other);

int darr_prepend(struct darr *d, struct darr *other);
