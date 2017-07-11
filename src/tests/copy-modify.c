#include <stdio.h>

#include "darr.h"

int main(void)
{
	int original_value = 12345789;
	int copy_value = 1;

	struct darr array1;
	darr_init(&array1, sizeof(int));
	darr_resize(&array1, 1);
	int *first1 = darr_element(&array1, 0);
	*first1 = original_value;

	struct darr array2;
	
	if (!darr_copy(&array2, &array1)) {
		fprintf(stderr, "Failed to create copy.\n");
		darr_deinit(&array1);
		return 1;
	}

	int *first2 = darr_element(&array2, 0);
	*first2 = copy_value;

	if (*first1 != original_value) {
		fprintf(stderr, "The copy seems to have modified the original array.\n");
		darr_deinit(&array1);
		darr_deinit(&array2);
		return 1;
	}

	darr_deinit(&array1);
	darr_deinit(&array2);
	return 0;
}
