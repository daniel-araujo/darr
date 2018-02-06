# Darr 1.7.2

A resizable array for the C language.


## Table of contents

1. Introduction
2. Examples
3. How to use
4. Reporting bugs
5. License


## 1. Introduction

Darr is a C library that abstracts most of the arithmetic that is needed to be
done when attempting to create an array of variable size with malloc, realloc
and free. The motivation for creating this library is to stop having to
repeatedly write such code and instead use a collection of functions.

The functions in this library assume that they're going to be used correctly.
This is in the same spirit that the C language was designed with which makes it
so efficient.


## 2. Examples

Here's a simple use case. This declares an array variable, initializes it,
resizes it, stores a value in it, prints the value and disposes it.

```C
#include <stdio.h>

// Include the header.
#include <darr.h>

int main(void)
{
	// Declare array variable.
	struct darr array;

	// Initialize an array of ints.
	darr_init(&array, sizeof(int));

	// Set the size of the array.
	// This operation may fail.
	if (!darr_resize(&array, 1)) {
		fprintf(stderr, "Failed to resize the array.\n");

		// Don't forget to dispose the array even on failure.
		darr_deinit(&array);

		return 1;
	}

	// Get a pointer to the first element.
	int *element = darr_element(&array, 0);

	// Store a value.
	*element = 1;

	// Access the value and print it.
	printf("The first element holds the value %d.\n", *element);

	// Dispose the array.
	darr_deinit(&array);

	return 0;
}
```

This shows you how you can iterate over the elements of the array with either a
C style indexing `for` loop or using C++ like iterators with pointers.

```C
#include <stdio.h>
#include <darr.h>

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));

	if (!darr_resize(&array, 3)) {
		fprintf(stderr, "Failed to resize the array.\n");
		darr_deinit(&array);
		return 1;
	}

	// C style indexing.
	for (int i = 0; i < darr_size(&array); ++i) {
		int *e = darr_element(&array, i);

		*e = i + 1;
	}

	// C++ style iterators.
	for (int *e = darr_begin(&array); e != darr_end(&array); ++e) {
		printf("%d\n", *e);
	}

	darr_deinit(&array);

	return 0;
}
```

Copies another array.

```C
#include <stdio.h>
#include <darr.h>

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));

	if (!darr_resize(&array, 3)) {
		fprintf(stderr, "Failed to resize the array.\n");
		darr_deinit(&array);
		return 1;
	}

	for (int i = 0; i < darr_size(&array); ++i) {
		int *e = darr_element(&array, i);

		*e = i + 1;
	}

	struct darr array_copy;
	if (!darr_copy(&array_copy, &array)) {
		fprintf(stderr, "Failed to copy array.\n");
		darr_deinit(&array);
		return 1;
	}

	// Original array is no longer needed
	darr_deinit(&array);

	for (int *e = darr_begin(&array_copy); e != darr_end(&array_copy); ++e) {
		printf("Copied %d\n", *e);
	}

	darr_deinit(&array_copy);

	return 0;
}
```

Copies a slice from another array.

```C
#include <stdio.h>
#include <darr.h>

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));

	if (!darr_resize(&array, 3)) {
		fprintf(stderr, "Failed to resize the array.\n");
		darr_deinit(&array);
		return 1;
	}

	for (int i = 0; i < darr_size(&array); ++i) {
		int *e = darr_element(&array, i);

		*e = i + 1;
	}

	struct darr array_copy;
	if (!darr_copy_slice(&array_copy, &array, 1, 2)) {
		fprintf(stderr, "Failed to copy array.\n");
		darr_deinit(&array);
		return 1;
	}

	// Original array is no longer needed
	darr_deinit(&array);

	for (int *e = darr_begin(&array_copy); e != darr_end(&array_copy); ++e) {
		printf("Copied %d\n", *e);
	}

	darr_deinit(&array_copy);

	return 0;
}
```

Swaps elements from one array to another.

```C
#include <stdio.h>
#include <darr.h>

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));

	if (!darr_resize(&array, 3)) {
		fprintf(stderr, "Failed to resize the array.\n");
		darr_deinit(&array);
		return 1;
	}

	struct darr other_array;
	darr_init(&other_array, sizeof(int));

	if (!darr_resize(&other_array, 3)) {
		fprintf(stderr, "Failed to resize the other array.\n");
		darr_deinit(&array);
		darr_deinit(&other_array);
		return 1;
	}

	for (int i = 0; i < 3; ++i) {
		int *e1 = darr_element(&array, i);
		int *e2 = darr_element(&other_array, i);

		*e1 = i + 1;
		*e2 = -*e1;
	}

	darr_swap(&array, &other_array);

	for (int i = 0; i < 3; ++i) {
		int *e1 = darr_element(&array, i);
		int *e2 = darr_element(&other_array, i);

		printf("array[%d] = %d\n", i, *e1);
		printf("other_array[%d] = %d\n", i, *e2);
	}

	darr_deinit(&array);
	darr_deinit(&other_copy);

	return 0;
}
```

Shifts elements left and right.

```C
#include <stdio.h>
#include <darr.h>

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));

	if (!darr_resize(&array, 2)) {
		fprintf(stderr, "Failed to resize the array.\n");
		darr_deinit(&array);
		return 1;
	}

	int *first = darr_element(&array, 0);
	int *second = darr_element(&array, 1);

	*second = 100;

	// Shift all elements 1 position to the left.
	darr_shift_left(&array, 1);

	printf("First after left shift: %d\n", *first);

	// Shift all elements 1 position to the right.
	darr_shift_right(&array, 1);

	printf("Second after right shift: %d\n", *second);

	darr_deinit(&array);

	return 0;
}
```

Shifts elements left and right inside slices.

```C
#include <stdio.h>
#include <darr.h>

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));

	if (!darr_resize(&array, 4)) {
		fprintf(stderr, "Failed to resize the array.\n");
		darr_deinit(&array);
		return 1;
	}

	int *first = darr_element(&array, 0);
	int *second = darr_element(&array, 1);
	int *third = darr_element(&array, 2);
	int *fourth = darr_element(&array, 3);

	*first = 100;
	*third = 200;

	// Shift to the left.
	darr_shift_slice_left(&array, 1, 1, 2);

	printf("First after left shift: %d\n", *first);
	printf("Second after left shift: %d\n", *second);

	// Shift to the right.
	darr_shift_slice_right(&array, 1, 1, 2);

	printf("First after right shift: %d\n", *first);
	printf("Third after right shift: %d\n", *third);

	darr_deinit(&array);

	return 0;
}
```

Shrinks and grows array size.

```C
#include <stdio.h>
#include <darr.h>

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));

	if (!darr_resize(&array, 3)) {
		fprintf(stderr, "Failed to resize the array.\n");
		darr_deinit(&array);
		return 1;
	}

	printf("Initial size: %d\n", (int) darr_size(&array));

	if (!darr_grow(&array, 1)) {
		fprintf(stderr, "Failed to grow the size of the array.\n");
		darr_deinit(&array);
		return 1;
	}

	printf("Size after growing by 1: %d\n", (int) darr_size(&array));

	if (!darr_shrink(&array, 1)) {
		fprintf(stderr, "Failed to shrink the size of the array.\n");
		darr_deinit(&array);
		return 1;
	}

	printf("Size after shrinking by 1: %d\n", (int) darr_size(&array));

	darr_deinit(&array);

	return 0;
}
```

Access first and last element.

```C
#include <stdio.h>
#include <darr.h>

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));

	if (!darr_resize(&array, 3)) {
		fprintf(stderr, "Failed to resize the array.\n");
		darr_deinit(&array);
		return 1;
	}

	for (int i = 0; i < darr_size(&array); ++i) {
		int *e = darr_element(&array, i);

		*e = i + 1;
	}

	int *first = darr_first(&array);
	int *last = darr_last(&array);

	printf("First element: %d\n", *first);
	printf("Last element: %d\n", *last);

	darr_deinit(&array);

	return 0;
}
```

Inserts, appends and prepends elements from another array.

```C
#include <stdio.h>
#include <darr.h>

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));

	if (!darr_resize(&array, 2)) {
		fprintf(stderr, "Failed to resize the array.\n");
		darr_deinit(&array);
		return 1;
	}

	printf("Original size: %d\n", (int) darr_size(&array));

	for (int *e = darr_begin(&array); e != darr_end(&array); ++e) {
		*e = 0;
	}

	struct darr other_array;
	darr_init(&other_array, sizeof(int));

	if (!darr_resize(&other_array, 2)) {
		fprintf(stderr, "Failed to resize the other array.\n");
		darr_deinit(&array);
		darr_deinit(&other_array);
		return 1;
	}

	for (int *e = darr_begin(&other_array); e != darr_end(&other_array); ++e) {
		*e = 1;
	}

	if (!darr_insert(&array, 1, &other_array)) {
		fprintf(stderr, "Failed to insert elements in the middle.\n");
		darr_deinit(&array);
		darr_deinit(&other_array);
		return 1;
	}

	if (!darr_append(&array, &other_array)) {
		fprintf(stderr, "Failed to append.\n");
		darr_deinit(&array);
		darr_deinit(&other_array);
		return 1;
	}

	if (!darr_prepend(&array, &other_array)) {
		fprintf(stderr, "Failed to prepend.\n");
		darr_deinit(&array);
		darr_deinit(&other_array);
		return 1;
	}

	printf("New size: %d\n", (int) darr_size(&array));

	for (int i = 0; i < darr_size(&array); ++i) {
		int *e = darr_element(&array, i);

		printf("Element %d: %d\n", i, *e);
	}

	darr_deinit(&array);
	darr_deinit(&other_array);

	return 0;
}
```

Removes elements from an array.

```C
#include <stdio.h>
#include <darr.h>

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));

	if (!darr_resize(&array, 3)) {
		fprintf(stderr, "Failed to resize the array.\n");
		darr_deinit(&array);
		return 1;
	}

	for (int i = 0; i < darr_size(&array); ++i) {
		int *e = darr_element(&array, i);

		*e = i + 1;
	}

	printf("Original size: %d\n", (int) darr_size(&array));

	darr_remove(&array, 0, 1);

	printf("Size after removal: %d\n", (int) darr_size(&array));

	for (int i = 0; i < darr_size(&array); ++i) {
		int *e = darr_element(&array, i);

		printf("Element %d: %d\n", i, *e);
	}

	darr_deinit(&array);

	return 0;
}
```

Moves all elements from one array to a new one.

```C
#include <stdio.h>
#include <darr.h>

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));

	if (!darr_resize(&array, 3)) {
		fprintf(stderr, "Failed to resize the array.\n");
		darr_deinit(&array);
		return 1;
	}

	for (int i = 0; i < darr_size(&array); ++i) {
		int *e = darr_element(&array, i);

		*e = i + 1;
	}

	struct darr other_array;
	if (!darr_move(&other_array, &array)) {
		fprintf(stderr, "Failed to move elements.\n");
		darr_deinit(&array);
		return 1;
	}

	for (int i = 0; i < darr_size(&other_array); ++i) {
		int *e = darr_element(&other_array, i);

		printf("Moved element %d: %d\n", i, *e);
	}

	darr_deinit(&array);
	darr_deinit(&other_array);

	return 0;
}
```

Moves a slice of elements from one array to a new one.

```C
#include <stdio.h>
#include <darr.h>

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));

	if (!darr_resize(&array, 3)) {
		fprintf(stderr, "Failed to resize the array.\n");
		darr_deinit(&array);
		return 1;
	}

	for (int i = 0; i < darr_size(&array); ++i) {
		int *e = darr_element(&array, i);

		*e = i + 1;
	}

	printf("Original size: %d\n", (int) darr_size(&array));

	struct darr other_array;
	if (!darr_move_slice(&other_array, &array, 1, 2)) {
		fprintf(stderr, "Failed to move elements.\n");
		darr_deinit(&array);
		return 1;
	}

	printf("New size: %d\n", (int) darr_size(&array));

	for (int i = 0; i < darr_size(&array); ++i) {
		int *e = darr_element(&array, i);

		printf("Old array element %d: %d\n", i, *e);
	}

	for (int i = 0; i < darr_size(&other_array); ++i) {
		int *e = darr_element(&other_array, i);

		printf("New array element %d: %d\n", i, *e);
	}

	darr_deinit(&array);
	darr_deinit(&other_array);

	return 0;
}
```

Supports const semantics.

```C
#include <stdio.h>
#include <darr.h>

// Accepts const pointers.
void print_int_array_representation(const struct darr *array)
{
	// darr_size works on const pointers.
	int size = darr_size(array);

	printf("array[%d] = ", size);
	printf("{\n");
	for (int i = 0; i < size; ++i) {
		// Using const counterpart of darr_element.
		const int *e = darr_element_const(array, i);

		printf("\t[%d] = %d,\n", i, *e);
	}
	printf("};\n");
}

int main(void)
{
	struct darr array;
	darr_init(&array, sizeof(int));

	if (!darr_resize(&array, 3)) {
		fprintf(stderr, "Failed to resize the array.\n");
		darr_deinit(&array);
		return 1;
	}

	for (int i = 0; i < darr_size(&array); ++i) {
		int *e = darr_element(&array, i);

		*e = i + 1;
	}

	print_int_array_representation(&array);

	darr_deinit(&array);

	return 0;
}
```


## 3. How to use

You can either copy the source files into your own project or install the
header file and the static library in your system and have your compiler link
to `libdarr.a`.

In your code you will need to include the `darr.h` header file.

```C
#include <darr.h>
```

Then you can declare variables of type `struct darr`.

```C
struct darr my_dynamic_array;
```

While the struct is not an opaque data structure, you're not supposed to access
its data members directly. You're going to call functions that operate on it,
instead.

The first thing you will always want to do is to initialize the struct. That's
what the function `darr_init` is for. It accepts the address of the struct as
its first argument and the size of each element as its second argument.

```C
darr_init(&my_dynamic_array, sizeof(int));
```

This initializes an empty array that that can hold an `int`.
To set the size you need to call `darr_resize`. It takes a pointer to the
struct as its first argument and the number of elements as its second argument.
It will return 0 on failure, 1 on success.

```C
int result = darr_resize(&my_dynamic_array, new_size);
```

You have probably noticed a pattern by now. Functions that operate on the
struct always take a pointer to it as their first argument. I will stop
pointing that out from now on.

You can call `darr_element` to get a pointer to an element by index.

```C
int *element = darr_element(&my_dynamic_array, index);
```

You can retrieve and assign its value through the pointer.

```C
// Assignment using pointer syntax.
*element = 1;

// Assignment using array syntax.
element[0] = 1;
```

The elements are guaranteed to be stored in sequence so you're allowed to use
the array syntax to access the other elements.

```C
// Assigning a value to the next element.
element[1] = 1;
```

But be wary that the pointer must no longer be used after calling `darr_resize`
or any operation that changes the size of the array. You would need to call
`darr_element` to get a new pointer.

When you are done using the array you should call `darr_deinit` to release all
the resources that are bound to it.

```C
darr_deinit(&my_dynamic_array);
```

Read the comments in the `darr.h` header file for detailed descriptions of
these functions and others.


## 4. Reporting bugs

If you encounter a bug, please open an issue on GitHub:

	https://github.com/daniel-araujo/darr/issues


## 5. License

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
