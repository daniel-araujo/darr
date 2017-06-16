#include <stdio.h>

#include "darr.h"

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));
	darr_resize(&array, 1);

	size_t expected_size = sizeof(int);

	char *first = darr_address(&array, 0);
	char *second = darr_address(&array, 1);

	if ((second - first) != expected_size) {
		fprintf(stderr, "Incorrect element size.\n");
		darr_deinit(&array);
		return 1;
	}

	darr_deinit(&array);
	return 0;
}
