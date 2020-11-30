#include <stdio.h>

#include "../src/darr.h"

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));
	darr_resize(&array, 5);

	int *element = darr_element(&array, 0);

	element[0] = 0;
	element[1] = 1;
	element[2] = 2;
	element[3] = 3;
	element[4] = 4;

	darr_shift_slice_right(&array, 1, 1, 3);

	if (element[0] != 0) {
		fprintf(stderr, "First element was changed after right shift.\n");
		darr_deinit(&array);
		return 1;
	}

	if (element[2] != 1) {
		fprintf(stderr, "Wrong value for third element after right shift.\n");
		darr_deinit(&array);
		return 1;
	}

	if (element[3] != 2) {
		fprintf(stderr, "Wrong value for fourth element after right shift.\n");
		darr_deinit(&array);
		return 1;
	}

	if (element[4] != 4) {
		fprintf(stderr, "Last element was changed after right shift.\n");
		darr_deinit(&array);
		return 1;
	}

	element[0] = 0;
	element[1] = 1;
	element[2] = 2;
	element[3] = 3;
	element[4] = 4;

	darr_shift_slice_left(&array, 1, 1, 3);

	if (element[0] != 0) {
		fprintf(stderr, "First element was changed after left shift.\n");
		darr_deinit(&array);
		return 1;
	}

	if (element[1] != 2) {
		fprintf(stderr, "Wrong value for third element after left shift.\n");
		darr_deinit(&array);
		return 1;
	}

	if (element[2] != 3) {
		fprintf(stderr, "Wrong value for fourth element after left shift.\n");
		darr_deinit(&array);
		return 1;
	}

	if (element[4] != 4) {
		fprintf(stderr, "Last element was changed after left shift.\n");
		darr_deinit(&array);
		return 1;
	}

	darr_deinit(&array);
	return 0;
}
