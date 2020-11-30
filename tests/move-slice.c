#include <stdio.h>

#include "../src/darr.h"

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
	darr_move_slice(&array2, &array, 1, 2);

	if (darr_size(&array) != 2) {
		fprintf(stderr, "Wrong size for first array.\n");
		darr_deinit(&array);
		darr_deinit(&array2);
		return 1;
	}

	if (darr_size(&array2) != 2) {
		fprintf(stderr, "Wrong size for second array.\n");
		darr_deinit(&array);
		darr_deinit(&array2);
		return 1;
	}

	element = darr_element(&array, 0);

	if (element[0] != 0) {
		fprintf(stderr, "Wrong value for first element of first array.\n");
		darr_deinit(&array);
		darr_deinit(&array2);
		return 1;
	}

	if (element[1] != 3) {
		fprintf(stderr, "Wrong value for second element of first array.\n");
		darr_deinit(&array);
		darr_deinit(&array2);
		return 1;
	}

	int *element2 = darr_element(&array2, 0);

	if (element2[0] != 1) {
		fprintf(stderr, "Wrong value for first element of second array.\n");
		darr_deinit(&array);
		darr_deinit(&array2);
		return 1;
	}

	if (element2[1] != 2) {
		fprintf(stderr, "Wrong value for second element of second array.\n");
		darr_deinit(&array);
		darr_deinit(&array2);
		return 1;
	}


	darr_deinit(&array);
	darr_deinit(&array2);
	return 0;
}
