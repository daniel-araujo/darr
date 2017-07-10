#include <stdio.h>

#include "darr.h"

static size_t margin = sizeof(int);

/*
 * Allocates memory like realloc but allocates an extra space at the begining
 * and the end.
 */
static void *margin_realloc(void *m, size_t size)
{
	char *mem = m;

	if (mem != NULL) {
		mem -= margin;
	}

	char *new = realloc(mem, size + margin * 2);

	if (new == NULL) {
		return new;
	}

	memset(new, 0, size + margin * 2);

	return new + margin;
}

static void margin_free(void *m)
{
	char *mem = m;

	free(mem - margin);
}

int main(void)
{
	int value1 = 0x55667788;
	int value2 = 0x11223344;

	darr_global_realloc_set(margin_realloc);
	darr_global_free_set(margin_free);

	struct darr array;
	darr_init(&array, sizeof(int));
	darr_resize(&array, 3);

	int *element = darr_address(&array, 0);

	element[0] = value1;
	element[1] = value2;

	darr_shift_left(&array, 1);

	if (element[-1] != 0) {
		fprintf(stderr, "Buffer overflow on the left.\n");
		darr_deinit(&array);
		return 1;
	}

	if (element[0] != value2) {
		fprintf(stderr, "Unexpected value after left shift.\n");
		darr_deinit(&array);
		return 1;
	}

	element[1] = value2;
	element[2] = value1;

	darr_shift_right(&array, 1);

	if (element[3] != 0) {
		fprintf(stderr, "Buffer overflow on the right.\n");
		darr_deinit(&array);
		return 1;
	}

	if (element[2] != value2) {
		fprintf(stderr, "Unexpected value after right shift.\n");
		darr_deinit(&array);
		return 1;
	}

	darr_deinit(&array);
	return 0;
}
