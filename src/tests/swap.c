#include <stdio.h>

#include "darr.h"

int main(void)
{
	size_t original_array1_size = 1;
	int original_array1_element1_value = 12345;

	size_t original_array2_size = 2;
	int original_array2_element1_value = 54321;
	int original_array2_element2_value = 87654321;

	struct darr array1;
	darr_init(&array1, sizeof(int));
	darr_resize(&array1, original_array1_size);
	int *original_array1_element1 = darr_element(&array1, 0);
	*original_array1_element1 = original_array1_element1_value;

	struct darr array2;
	darr_init(&array2, sizeof(int));
	darr_resize(&array2, original_array2_size);
	int *original_array2_element1 = darr_element(&array2, 0);
	*original_array2_element1 = original_array2_element1_value;
	int *original_array2_element2 = darr_element(&array2, 1);
	*original_array2_element2 = original_array2_element2_value;

	darr_swap(&array1, &array2);

	// Check sizes.

	if (darr_size(&array1) != original_array2_size) {
		fprintf(stderr, "The first array was expected to have the original size of the second array.\n");
		darr_deinit(&array1);
		darr_deinit(&array2);
		return 1;
	}

	if (darr_size(&array2) != original_array1_size) {
		fprintf(stderr, "The second array was expected to have the original size of the first array.\n");
		darr_deinit(&array1);
		darr_deinit(&array2);
		return 1;
	}

	// Check elements.

	int *array1_element1 = darr_element(&array1, 0);

	if (*array1_element1 != original_array2_element1_value) {
		fprintf(stderr, "The first element of the first array was expected to have the original value of the first element of the second array.\n");
		darr_deinit(&array1);
		darr_deinit(&array2);
		return 1;
	}

	int *array1_element2 = darr_element(&array1, 1);

	if (*array1_element2 != original_array2_element2_value) {
		fprintf(stderr, "The second element of the first array was expected to have the original value of the second element of the second array.\n");
		darr_deinit(&array1);
		darr_deinit(&array2);
		return 1;
	}

	int *array2_element1 = darr_element(&array2, 0);

	if (*array2_element1 != original_array1_element1_value) {
		fprintf(stderr, "The first element of the second array was expected to have the original value of the first element of the first array.\n");
		darr_deinit(&array1);
		darr_deinit(&array2);
		return 1;
	}

	darr_deinit(&array1);
	darr_deinit(&array2);
	return 0;
}
