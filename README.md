# Darr 1.3.0

A resizable array for the C language.


## Table of contents

1. Introduction
2. How to use
3. Examples
4. Reporting Bugs
5. License


## 1. Introduction

Darr is a C library that abstracts most of the arithmetic that is done when
attempting to create an array of variable size with malloc, realloc and free.
The motivation for creating this tiny library is to stop having to write
repetitive memory allocation code.

The functions in this library assume that they're always going to be used
correctly so that they can avoid having to validate their input. For instance,
no bounds checking is done and the size for the array is expected to always be
a positive number.


## 2. How to use

You can either copy the source files into your own project or install the
header file and the static library in your system.

In your code you're going to need to include the `darr.h` header file.

```C
#include <darr.h>
```

Then you can declare variables of type `struct darr`.

```C
struct darr my_dynamic_array;
```

The struct is not an opaque data structure but you're not supposed to access
its data members directly. You're going to call functions that operate on it,
instead.

The first thing you will always want to do is to initialize the struct. That's
what the function `darr_init` is for. It accepts the address of the struct as
its first argument and the size of each element as its second argument.

```C
darr_init(&my_dynamic_array, sizeof(int));
```

This initializes an empty array that will store values that can hold an
`int`. To set the size you need to call `darr_resize`. It takes the address of
the struct as its first argument and the number of elements as its second
argument. It will return 0 on failure, 1 on success.

```C
int result = darr_resize(&my_dynamic_array, new_size);
```

You have probably noticed a pattern by now. Functions that operate on the
struct always accept its address as their first argument. I will stop pointing
that out from now on.

The only way to access the elements of the array is to ask for their addresses.
To do that, you need to call `darr_address`. This takes the index of the
element.

```C
int *element = darr_address(&my_dynamic_array, index);
```

With the address you can pretty much do anything you would be able to do with a
pointer in C.

```C
// Assignment using pointer syntax.
*element = 1;

// Assignment using array syntax.
element[0] = 1;
```

The elements are guaranteed to be stored in sequence.

But be wary that the address must no longer be used after calling
`darr_resize`, you would need to call `darr_address` again.

When you are done using the array you should call `darr_deinit` to release all
the resources that are bound to it.

```C
darr_deinit(&my_dynamic_array);
```

You may also be interested in making copies of arrays. You can do so by calling
`darr_copy`. The first argument must be an array that has not been initialized,
the second argument is the array you want to copy.

```C
darr_copy(&copy_array, &source_array);
```

You can then treat the copy like any other array, which includes having
to deinitialize it.

Read the comments in the `darr.h` header file for detailed descriptions of
these functions and others.


## 3. Examples

The following program shows you the most common operations you will do.
Initializing, resizing, storing and retrieving data, deinitializing and error
handling.

```C
#include <stdio.h>

// Include the header.
#include <darr.h>

int main(void)
{
	// Declare array variable.
	struct darr array;

	// Initialize array of ints.
	darr_init(&array, sizeof(int));

	// Set size.
	if (!darr_resize(&array, 1)) {
		fprintf(stderr, "Failed to resize the array.\n");

		// Don't forget to dispose the array even on failure.
		darr_deinit(&array);

		return 1;
	}

	// Retrieve the address of the first element.
	int *element = darr_address(&array, 0);

	*element = 1;

	printf("The first element holds the value %d.\n", *element);

	// Dispose the array.
	darr_deinit(&array);

	return 0;
}
```


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
