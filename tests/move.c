#include <stdio.h>

#include "../src/darr.h"

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));
	darr_resize(&array, 2);

	int *element = darr_element(&array, 0);

	element[0] = 0;
	element[1] = 1;

	struct darr array2;
	darr_move(&array2, &array);

	if (darr_size(&array) != 0) {
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

	int *element2 = darr_element(&array2, 0);

	if (element2[0] != 0) {
		fprintf(stderr, "Wrong value for first element of second array.\n");
		darr_deinit(&array);
		darr_deinit(&array2);
		return 1;
	}

	if (element2[1] != 1) {
		fprintf(stderr, "Wrong value for second element of second array.\n");
		darr_deinit(&array);
		darr_deinit(&array2);
		return 1;
	}

	darr_deinit(&array);
	darr_deinit(&array2);
	return 0;
}
