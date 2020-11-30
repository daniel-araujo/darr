#include <stdio.h>

#include "../src/darr.h"

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));
	darr_resize(&array, 5);

	int *first = darr_element(&array, 0);
	int *last = darr_element(&array, 4);

	if (darr_first(&array) != first) {
		fprintf(stderr, "darr_first is not pointing to the first element.\n");
		darr_deinit(&array);
		return 1;
	}

	if (darr_last(&array) != last) {
		fprintf(stderr, "darr_last is not pointing to the last element.\n");
		darr_deinit(&array);
		return 1;
	}

	darr_deinit(&array);
	return 0;
}
