#include <stdio.h>

#include "darr.h"

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));

	darr_resize(&array, 3);

	darr_grow(&array, 1);

	if (darr_size(&array) != 4) {
		fprintf(stderr, "Failed to grow.\n");
		darr_deinit(&array);
		return 1;
	}

	darr_shrink(&array, 1);

	if (darr_size(&array) != 3) {
		fprintf(stderr, "Failed to shrink.\n");
		darr_deinit(&array);
		return 1;
	}

	darr_deinit(&array);
	return 0;
}
