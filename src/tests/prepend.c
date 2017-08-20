#include <stdio.h>

#include "darr.h"

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));
	darr_resize(&array, 3);

	for (int *e = darr_begin(&array); e != darr_end(&array); ++e) {
		*e = 0;
	}

	struct darr array2;
	darr_init(&array2, sizeof(int));
	darr_resize(&array2, 3);

	for (int *e = darr_begin(&array2); e != darr_end(&array2); ++e) {
		*e = -1;
	}

	darr_prepend(&array, &array2);

	for (int i = 0; i < 3; ++i) {
		int *e = darr_element(&array, i);

		if (*e != -1) {
			fprintf(stderr, "Element %d does not have the expected value.\n", i);
			darr_deinit(&array);
			darr_deinit(&array2);
			return 1;
		}
	}

	for (int i = 3; i < 6; ++i) {
		int *e = darr_element(&array, i);

		if (*e != 0) {
			fprintf(stderr, "Element %d does not have the expected value.\n", i);
			darr_deinit(&array);
			darr_deinit(&array2);
			return 1;
		}
	}

	darr_deinit(&array);
	return 0;
}
