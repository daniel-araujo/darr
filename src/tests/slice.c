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

	struct darr array2;
	darr_slice(&array2, &array, 1, 2);

	if (darr_size(&array2) != 2) {
		fprintf(stderr, "Wrong size for slice.\n");
		darr_deinit(&array);
		darr_deinit(&array2);
		return 1;
	}

	int *element2 = darr_element(&array2, 0);

	if (element2[0] != 1) {
		fprintf(stderr, "Wrong value for first element of slice.\n");
		darr_deinit(&array);
		darr_deinit(&array2);
		return 1;
	}

	if (element2[1] != 2) {
		fprintf(stderr, "Wrong value for second element of slice.\n");
		darr_deinit(&array);
		darr_deinit(&array2);
		return 1;
	}

	darr_deinit(&array);
	darr_deinit(&array2);
	return 0;
}
