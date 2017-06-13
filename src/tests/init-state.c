#include <stdio.h>

#include "darr.h"

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));

	if (darr_size(&array) != 0) {
		fprintf(stderr, "Was expecting array to start out empty (0 size).\n");
		darr_deinit(&array);
		return 1;
	}

	darr_deinit(&array);
	return 0;
}
