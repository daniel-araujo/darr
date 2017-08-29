#include <stdio.h>

#include "darr.h"

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));
	darr_resize(&array, 1);

	const struct darr *const_array = &array;

	// Size.
	const size_t size = darr_size(const_array);

	// Copy of const array.
	struct darr copy;
	darr_copy(&copy, const_array);

	// Copy slice of const array.
	struct darr copy2;
	darr_copy_slice(&copy2, const_array, 0, darr_size(const_array));

	// Const data pointer.
	const int *data = darr_data_const(const_array);

	// Const element pointer.
	const int *element = darr_element_const(const_array, 0);

	// Const iterators.
	const int *begin = darr_begin_const(const_array);
	const int *end = darr_end_const(const_array);

	// Check if empty.
	int empty = darr_empty(const_array);

	// Const pointers to first and last element.
	const int *first = darr_first_const(const_array);
	const int *last = darr_last_const(const_array);

	// Append const array.
	struct darr append;
	darr_init(&append, sizeof(int));
	darr_append(&append, const_array);

	// Prepend const array.
	struct darr prepend;
	darr_init(&prepend, sizeof(int));
	darr_prepend(&prepend, const_array);

	// Insert const array.
	struct darr insert;
	darr_init(&insert, sizeof(int));
	darr_insert(&insert, 0, const_array);

	return 0;
}
