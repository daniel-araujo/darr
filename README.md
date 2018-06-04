# Darr 1.7.5

A resizable array for the C language.


## Table of contents

1. Introduction
2. Example
3. How to use
    * Resizing
    * Storing and retrieving elements
    * Iterating over elements
    * Copying
    * Moving
    * Swaping elements
    * Shifting
    * Inserting
    * Removing
    * Const
    * Sorting
4. Reporting bugs
5. License


## 1. Introduction

Darr is a C library that abstracts the math needed to create and manage an
array of variable size with malloc, realloc and free. The motivation for
creating this library is to stop having to repeatedly write such code on every
new code base.

The functions in this library assume that they're going to be used correctly.
This is in the same spirit that the C language is designed with that allows it
to be efficient.

All functions are marked `inline` so that no operation incurs a function call
overhead if the compiler agrees that it's worth it.


## 2. Example

```C
#include <stdio.h>

// Include header.
#include <darr.h>

int main(void)
{
	// Declare array variable.
	struct darr array;

	// Initialize array of ints.
	darr_init(&array, sizeof(int));

	// Set the size of the array.
	// This operation may fail.
	if (!darr_resize(&array, 1)) {
		fprintf(stderr, "Failed to resize the array.\n");

		// Dispose the array.
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


## 3. How to use

You can either copy the source files into your own project or install the
header file and the static library in your system and have your compiler link
to `libdarr.a`. Then include `darr.h` in your code.

```C
#include <darr.h>
```

This lets you declare variables of type `struct darr`.

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

At this point you can set the size of the array and insert elements into it.

When you are done using the array you must call `darr_deinit` to release all
the resources that are bound to it.

```C
darr_deinit(&my_dynamic_array);
```

Read the comments in the `darr.h` header file for detailed descriptions of all
functions.


### 3.1. Resizing

There are several functions available for changing the size of the array. 

The `darr_resize` function allows you to set a new size for the array. It takes
a pointer to the struct as its first argument and the number of elements as its
second argument. It will return 0 on failure and 1 on success.

```C
int success = darr_resize(&array, new_size);
```

The `darr_grow` and `darr_shrink` functions allow you to increase and decrease
the existing size of the array, respectively.

```C
// Increases size of array by n.
int result = darr_grow(&array, n);

// Decreases size of array by n.
int result = darr_shrink(&array, n);
```


### 3.2. Storing and retrieving elements

You can call `darr_element` to get a pointer to an element. You can only call
this function if the array has at least one element.

```C
int *element = darr_element(&array, index);
```

You can use the pointer however you like. You can retrieve and assign values to
it like you would with any other pointer.

```C
// Assignment using pointer syntax.
*element = 1;

// Assignment using array syntax.
element[0] = 1;
```

The elements are guaranteed to be stored in sequence so you're allowed to use
the array syntax to access other elements.

```C
// Assigning a value to the next element.
element[1] = 1;
```

But be wary that the pointer must no longer be used after any operation that
could change the size of the array. You need to call `darr_element` again to
get a new pointer.

You can also get a pointer to the first and last elements using `darr_first`
and `darr_last`, respectively. You can only call these functions if the array
has at least one element.

```C
// Get first element.
int *first = darr_first(&array);

// Get last element.
int *last = darr_last(&array);
```


### 3.3. Iterating over elements

With a for loop you can sequentially access every element of the array.

```C
// Index iterator.
for (int i = 0; i < darr_size(&array); ++i) {
	int *e = darr_element(&array, i);
	[...]
}
```

You can also use `darr_begin` and `darr_end` to create a C++ style iterator.

```C
// C++ style iterator.
for (int *e = darr_begin(&array); e != darr_end(&array); ++e) {
	[...]
}
```


### 3.4. Copying

The `darr_copy` function lets you initialize a new array with a copy of the
elements of an other array. It returns 1 on success, 0 on failure.

```C
int success = darr_copy(&array_copy, &array);
```

The `darr_copy_slice` function is similar to `darr_copy` but allows you to
specify the range of elements to copy.

```C
int success = darr_copy_slice(&array_copy, &array, 1, 2);
```


### 3.5. Moving

The `darr_move` function lets you initialize a new array with the elements of
an other array. It returns 1 on success, 0 on failure.

```C
int success = darr_move(&array, &other_array);
```

The `darr_move_slice` function is similar to `darr_move` but allows you to
specify the range of elements to move. 

```C
int success = darr_move_slice(&array, &other_array, 1, 2);
```


### 3.6. Swaping elements

The `darr_swap` function can be used to swap elements from 2 arrays.

```C
darr_swap(&array, &other_array);
```


### 3.7. Shifting

Shift elements left and right by `n` elements.

```C
darr_shift_left(&array, n);
darr_shift_right(&array, n);
```

Shift elements left and right inside slices.

```C
darr_shift_slice_left(&array, n, start, size);
darr_shift_slice_right(&array, n, start, size);
```

### 3.8. Inserting

The `darr_insert` function allows you to insert a copy of the elements from
another array. It lets you specify at which index to insert the elements. It
returns 1 on success and 0 on failure.

```C
int success = darr_insert(&array, 1, &other_array);
```

The `darr_append` and `darr_prepend` functions are similar to `darr_insert` but
the elements are inserted at the beginning and at the end, respectively.

```C
int success = darr_append(&array, &other_array);
int success = darr_prepend(&array, &other_array);
```


### 3.9. Removing

The `darr_remove` function allows you to remove elements from an array. You
have to specify at which index to start removing and the number of elements to
remove. Returns 1 on success, 0 on failure.

```C
int success = darr_remove(&array, 0, 1);
```


### 3.10. Const

Const semantics are supported. Some functions have `const` versions of
themselves, usually the same name with the _const suffix.

```C
const int *data = darr_data_const(&const_array);
```

```C
const int *element = darr_element_const(&const_array, 0);
```

```C
const int *begin = darr_begin_const(&const_array);
const int *end = darr_end_const(&const_array);
```

```C
const int *first = darr_first_const(&const_array);
const int *last = darr_last_const(&const_array);
```


### 3.11. Sorting

Darr provides the means for you to use existing sorting algorithms.

Here's how you would use the standard library's `qsort`.

```C
int compare(const void *a, const void *b)
{
	const int *x = a;
	const int *y = b;

	if (*x > *y) {
		return 1;
	} else if (*x < *y) {
		return -1;
	} else {
		return 0;
	}
}

qsort(darr_data(&array), darr_size(&array), sizeof(int), compare);
```


## 4. Reporting bugs

If you encounter a bug, please open an issue on GitLab:

	https://gitlab.com/daniel-araujo/darr/issues


## 5. License

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
