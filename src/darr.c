#include "darr.h"

darr_realloc_t darr_realloc = realloc;

darr_free_t darr_free = free;

void darr_global_set_realloc(darr_realloc_t f);

void darr_global_set_free(darr_free_t f);

size_t darr_data_index(struct darr *d, size_t i);

size_t darr_data_size(struct darr *d);

void darr_init(struct darr *d, size_t item_size);

int darr_copy(struct darr *d, struct darr *other);

void darr_deinit(struct darr *d);

size_t darr_size(struct darr *d);

int darr_resize(struct darr *d, size_t size);

void *darr_address(struct darr *d, size_t i);
