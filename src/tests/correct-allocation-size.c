#include <stdio.h>

#include "darr.h"

static size_t allocated;

static void *override_realloc(void *p, size_t size)
{
	allocated += size;

	return realloc(p, size);
}

int main(void)
{
	darr_global_realloc_set(&override_realloc);

	size_t expected_size = sizeof(int);

	struct darr array;
	darr_init(&array, sizeof(int));
	darr_resize(&array, 1);

	if (allocated != expected_size) {
		fprintf(stderr, "Unexpected amount of space allocated.\n");
		darr_deinit(&array);
		return 1;
	}

	darr_deinit(&array);
	return 0;
}
