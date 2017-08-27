#include <stdio.h>

#include "darr.h"

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));
	darr_resize(&array, 2);

	for (int *e = darr_begin(&array); e != darr_end(&array); ++e) {
		*e = 0;
	}

	struct darr array2;
	darr_init(&array2, sizeof(int));
	darr_resize(&array2, 2);

	for (int *e = darr_begin(&array2); e != darr_end(&array2); ++e) {
		*e = -1;
	}

	darr_insert(&array, 1, &array2);

	int *element = darr_element(&array, 0);

	if (element[0] != 0) {
		fprintf(stderr, "First element was changed after insertion.\n");
		darr_deinit(&array);
		darr_deinit(&array2);
		return 1;
	}

	if (element[1] != -1) {
		fprintf(stderr, "Second element was supposed to be the first element of the second array.\n");
		darr_deinit(&array);
		darr_deinit(&array2);
		return 1;
	}

	if (element[2] != -1) {
		fprintf(stderr, "Third element was supposed to be the second element of the second array.\n");
		darr_deinit(&array);
		darr_deinit(&array2);
		return 1;
	}

	if (element[3] != 0) {
		fprintf(stderr, "Last element was changed after insertion.\n");
		darr_deinit(&array);
		darr_deinit(&array2);
		return 1;
	}

	darr_deinit(&array);
	return 0;
}
