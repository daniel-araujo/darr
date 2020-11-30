#include <stdio.h>

#include "../src/darr.h"

int main(void)
{
	size_t original_size = 1;
	size_t copy_size = 2;

	struct darr array1;
	darr_init(&array1, sizeof(int));

	if (!darr_resize(&array1, original_size)) {
		fprintf(stderr, "Failed to resize the array.\n");
		darr_deinit(&array1);
		return 1;
	}

	struct darr array2;
	
	if (!darr_copy(&array2, &array1)) {
		fprintf(stderr, "Failed to copy.\n");
		darr_deinit(&array1);
		return 1;
	}

	if (!darr_resize(&array2, copy_size)) {
		fprintf(stderr, "Failed to resize the copy.\n");
		darr_deinit(&array1);
		darr_deinit(&array2);
		return 1;
	}

	if (darr_size(&array1) != original_size) {
		fprintf(stderr, "Resizing the copy seems to have changed the size of the original array.\n");
		darr_deinit(&array1);
		darr_deinit(&array2);
		return 1;
	}

	darr_deinit(&array1);
	darr_deinit(&array2);
	return 0;
}
