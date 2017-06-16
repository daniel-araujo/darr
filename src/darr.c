#include "darr.h"

darr_realloc_t darr_realloc = realloc;

darr_free_t darr_free = free;

void darr_global_set_realloc(darr_realloc_t f);

void darr_global_set_free(darr_free_t f);

size_t darr_data_index(struct darr *d, int i);

void darr_init(struct darr *d, size_t item_size);

void darr_deinit(struct darr *d);

int darr_size(struct darr *d);

int darr_resize(struct darr *d, size_t size);

void *darr_address(struct darr *d, size_t i);
