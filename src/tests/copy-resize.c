#include <stdio.h>

#include "darr.h"

int main(void)
{
	size_t original_size = 1;
	size_t copy_size = 2;

	struct darr array1;
	darr_init(&array1, sizeof(int));
	darr_resize(&array1, original_size);

	struct darr array2;
	darr_copy(&array2, &array1);
	darr_resize(&array2, copy_size);

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
