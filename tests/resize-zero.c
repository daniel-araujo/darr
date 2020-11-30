#include <stdio.h>

#include "../src/darr.h"

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));
	darr_resize(&array, 2);
	darr_resize(&array, 0);

	if (darr_size(&array) != 0) {
		fprintf(stderr, "Was expecting size to be 0.\n");
		darr_deinit(&array);
		return 1;
	}

	darr_deinit(&array);
	return 0;
}
