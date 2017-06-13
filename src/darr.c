#include "darr.h"

size_t darr_data_index(struct darr *d, int i);

void darr_init(struct darr *d, size_t item_size);

void darr_deinit(struct darr *d);

int darr_size(struct darr *d);

int darr_resize(struct darr *d, size_t size);

void *darr_address(struct darr *d, size_t i);

void darr_set(struct darr *d, size_t i, void *value);

void darr_copy(struct darr *d, size_t i, void *value);
