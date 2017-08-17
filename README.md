# Darr 1.5.0

A resizable array for the C language.


## Table of contents

1. Introduction
2. Examples
3. How to use
4. Reporting Bugs
5. License


## 1. Introduction

Darr is a C library that abstracts most of the arithmetic that is done when
attempting to create an array of variable size with malloc, realloc and free.
The motivation for creating this tiny library is to stop having to repeatedly
write such code.

The functions in this library assume that they're going to be used correctly.
There's no bounds checking, for example. this is in the same spirit that the
language is designed with that makes it so efficient. The programmer is
trusted.


## 2. Examples

The following C program shows you some of the most common operations.

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

	printf("The first element holds the value %d.\n", *element);

	// Dispose the array.
	darr_deinit(&array);

	return 0;
}
```

This shows you how you can iterate over the elements.

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
To set the size you need to call `darr_resize`. It takes the address of the
struct as its first argument and the number of elements as its second argument.
It will return 0 on failure, 1 on success.

```C
int result = darr_resize(&my_dynamic_array, new_size);
```

You have probably noticed a pattern by now. Functions that operate on the
struct always accept its address as their first argument. I will stop pointing
that out from now on.

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

But be wary that the pointer must no longer be used after calling
`darr_resize`. You would need to call `darr_element` to get a new pointer.

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
