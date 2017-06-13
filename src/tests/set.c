#include <stdio.h>

#include "darr.h"

int main(void)
{
	int expected_value = 123456789;
	int *whats_there;

	struct darr array;
	darr_init(&array, sizeof(int));
	darr_resize(&array, 1);
	darr_set(&array, 0, &expected_value);
	whats_there = darr_address(&array, 0);

	if (*whats_there != expected_value) {
		fprintf(stderr, "Failed to set value.\n");
		darr_deinit(&array);
		return 1;
	}

	darr_deinit(&array);
	return 0;
}
