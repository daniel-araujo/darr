# Darr 1.0.0

A resizable array for the C language.


## Table of contents

1. Introduction
2. How to use
3. Examples
4. Reporting Bugs
5. License


## 1. Introduction

Darr is a C library that abstracts most of the arithmetic that is done when
attempting to create an array of variable size with malloc and realloc. The
motivation for creating this tiny library is to stop writing repetitive memory
allocation code.


## 2. How to use

You can either copy the source files into your own project or install the
header file and the static library in your system.

In your code you're going to need to include the `darr.h` header file.

```C
#include <darr.h>
```

Now you can declare variables of type `struct darr`.

```C
struct darr my_dynamic_array;
```

The struct is not an opaque data structure but you're not supposed to access
its data members directly. You're going to call functions that operate on it,
instead.

The first thing you will always want to do is to initialize the struct. That's
what the function darr_init is for.

```C
darr_init(&my_dynamic_array, sizeof(int));
```

It accepts the address of the struct as its first argument and the size of each
element as its second argument.

You're going to notice that functions that operate on the struct always accept
its address as its first argument.

Here's how to set the size:

```C
darr_resize(&my_dynamic_array, new_size);
```

Getting the address of an element:

```C
darr_address(&my_dynamic_array, index);
```

When you are done using the array you should call darr_deinit to release all
the resources that are bound to it.

```C
darr_deinit(&my_dynamic_array);
```

Read the comments in the `darr.h` header file for detailed descriptions of
these functions.


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
