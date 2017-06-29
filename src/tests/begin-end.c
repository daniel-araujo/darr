#include <stdio.h>

#include "darr.h"

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));
	darr_resize(&array, 1);

	int *begin = darr_address(&array, 0);
	int *end = darr_address(&array, 1);

	if (darr_begin(&array) != begin) {
		fprintf(stderr, "darr_begin is not pointing to the first element.\n");
		darr_deinit(&array);
		return 1;
	}

	if (darr_end(&array) != end) {
		fprintf(stderr, "darr_end is not pointing to the end of the array.\n");
		darr_deinit(&array);
		return 1;
	}

	darr_deinit(&array);
	return 0;
}
