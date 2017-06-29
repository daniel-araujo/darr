#include <stdio.h>

#include "darr.h"

int main(void)
{
	int expected_value = 12345789;

	struct darr array1;
	darr_init(&array1, sizeof(int));
	darr_resize(&array1, 1);
	int *first1 = darr_address(&array1, 0);
	*first1 = expected_value;

	struct darr array2;
	
	if (!darr_copy(&array2, &array1)) {
		fprintf(stderr, "Failed to create copy.\n");
		darr_deinit(&array1);
		return 1;
	}

	int *first2 = darr_address(&array2, 0);

	if (darr_size(&array1) != darr_size(&array2)) {
		fprintf(stderr, "The copy has a different size.\n");
		darr_deinit(&array1);
		darr_deinit(&array2);
		return 1;
	}

	if (*first1 != expected_value || *first1 != *first2) {
		fprintf(stderr, "The copy does not contain the same value.\n");
		darr_deinit(&array1);
		darr_deinit(&array2);
		return 1;
	}

	if (first1 == first2) {
		fprintf(stderr, "The copy starts at the same address as the original. That's not a copy.\n");
		darr_deinit(&array1);
		darr_deinit(&array2);
		return 1;
	}

	darr_deinit(&array1);
	darr_deinit(&array2);
	return 0;
}
