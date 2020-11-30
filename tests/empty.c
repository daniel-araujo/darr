#include <stdio.h>

#include "../src/darr.h"

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));

	if (!darr_empty(&array)) {
		fprintf(stderr, "A new array with 0 size is incorrectly reporting to be not empty.\n");
		darr_deinit(&array);
		return 1;
	}

	darr_resize(&array, 2);

	if (darr_empty(&array)) {
		fprintf(stderr, "An array with size 2 is incorrectly reporting to be empty.\n");
		darr_deinit(&array);
		return 1;
	}

	darr_resize(&array, 0);

	if (!darr_empty(&array)) {
		fprintf(stderr, "An array resized to 0 is incorrectly reporting to be not empty.\n");
		darr_deinit(&array);
		return 1;
	}

	darr_deinit(&array);
	return 0;
}
