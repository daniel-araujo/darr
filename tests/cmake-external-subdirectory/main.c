#include <stdio.h>

#include <darr.h>

int main(void)
{
	int expected_value = 123456789;
	int *whats_there;

	struct darr array;
	darr_init(&array, sizeof(int));
	darr_resize(&array, 1);
	whats_there = darr_element(&array, 0);
	*whats_there = expected_value;

	if (*whats_there != expected_value) {
		fprintf(stderr, "Failed to set value.\n");
		darr_deinit(&array);
		return 1;
	}

	darr_deinit(&array);
	return 0;
}
