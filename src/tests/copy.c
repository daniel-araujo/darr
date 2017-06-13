#include <stdio.h>

#include "darr.h"

int main(void)
{
	int expected_value = 123456789;
	int retrieved_value = 0;

	struct darr array;
	darr_init(&array, sizeof(int));
	darr_resize(&array, 1);
	darr_set(&array, 0, &expected_value);
	darr_copy(&array, 0, &retrieved_value);

	if (retrieved_value != expected_value) {
		fprintf(stderr, "Failed to copy value.\n");
		darr_deinit(&array);
		return 1;
	}

	darr_deinit(&array);
	return 0;
}
