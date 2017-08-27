#include <stdio.h>

#include "darr.h"

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));
	darr_resize(&array, 4);

	int *element = darr_element(&array, 0);

	element[0] = 0;
	element[1] = 1;
	element[2] = 2;
	element[3] = 3;

	darr_remove(&array, 1, 2);

	element = darr_element(&array, 0);

	if (element[0] != 0) {
		fprintf(stderr, "Wrong value for first element.\n");
		darr_deinit(&array);
		return 1;
	}

	if (element[1] != 3) {
		fprintf(stderr, "Wrong value for second element.\n");
		darr_deinit(&array);
		return 1;
	}

	darr_deinit(&array);
	return 0;
}
