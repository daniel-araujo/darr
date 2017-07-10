#include <stdio.h>

#include "darr.h"

int main(void)
{
	int value1 = 0x55667788;
	int value2 = 0x11223344;

	struct darr array;
	darr_init(&array, sizeof(int));
	darr_resize(&array, 4);

	int *element = darr_address(&array, 0);

	element[0] = value1;
	element[1] = value2;

	darr_shift_right(&array, 1);

	if (element[1] != value1) {
		fprintf(stderr, "Wrong value for second element after right shift.\n");
		darr_deinit(&array);
		return 1;
	}

	if (element[2] != value2) {
		fprintf(stderr, "Wrong value for third element after right shift.\n");
		darr_deinit(&array);
		return 1;
	}

	darr_shift_left(&array, 1);

	if (element[0] != value1) {
		fprintf(stderr, "Wrong value for first element after left shift.\n");
		darr_deinit(&array);
		return 1;
	}

	if (element[1] != value2) {
		fprintf(stderr, "Wrong value for second element after left shift.\n");
		darr_deinit(&array);
		return 1;
	}

	darr_deinit(&array);
	return 0;
}
