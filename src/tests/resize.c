#include <stdio.h>

#include "darr.h"

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));
	darr_resize(&array, 2);

	if (darr_size(&array) != 2) {
		fprintf(stderr, "Was expecting size to be 2.\n");
		darr_deinit(&array);
		return 1;
	}

	darr_deinit(&array);
	return 0;
}
