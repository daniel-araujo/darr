#ifndef DARR_DARR_H
#define DARR_DARR_H

#include <stdlib.h>
#include <string.h>

typedef void *(*darr_realloc_t)(void *, size_t);
typedef void (*darr_free_t)(void *);

extern darr_realloc_t darr_realloc;
extern darr_free_t darr_free;

/*
 * Allows you to override any call to realloc made by darr.
 */
inline void darr_global_realloc_set(darr_realloc_t f)
{
	darr_realloc = f;
}

/*
 * Allows you to override any call to free made by darr.
 */
inline void darr_global_free_set(darr_free_t f)
{
	darr_free = f;
}

/*
 * The darr struct. You can initialize it by calling darr_init.
 */
struct darr {
	size_t element_size;
	size_t size;
	char *data;
};

/*
 * This is an implementation detail. Don't call this function.
 *
 * Translates an index provided by the user to an index that can be used to
 * access an element.
 */
inline size_t darr_data_index(struct darr *d, size_t i)
{
	return i * d->element_size;
}

/*
 * This is an implementation detail. Don't call this function.
 *
 * Returns the total size of allocated memory.
 */
inline size_t darr_data_size(struct darr *d)
{
	return d->size * d->element_size;
}

/*
 * Initializes a darr struct.
 *
 * You may not pass a struct that has already been initialized.
 *
 * Call darr_deinit to deinitialize.
 */
inline void darr_init(struct darr *d, size_t element_size)
{
	d->element_size = element_size;
	d->size = 0;
	d->data = NULL;
}

/*
 * Initializes a darr struct that will be a copy of another one.
 *
 * Returns 1 on success, 0 on failure.
 *
 * On failure, the darr struct is not initialized.
 *
 * Call darr_deinit to deinitialize.
 */
inline int darr_copy(struct darr *d, struct darr *other)
{
	void *new = darr_realloc(NULL, darr_data_size(other));

	if (new == NULL) {
		return 0;
	}

	memcpy(new, other->data, darr_data_size(other));

	d->element_size = other->element_size;
	d->size = other->size;
	d->data = new;
	return 1;
}

/*
 * Deinitializes a darr struct.
 *
 * The struct must have been previously initialized with either darr_init or
 * darr_copy. You may not pass a struct that has isn't initialized.
 */
inline void darr_deinit(struct darr *d)
{
	if (d->data) {
		darr_free(d->data);
	}
}

/*
 * Returns the current size of the array.
 */
inline size_t darr_size(struct darr *d)
{
	return d->size;
}

/*
 * Returns a pointer to the start of the array.
 *
 * This is equivalent to calling darr_element with index 0.
 *
 * The restrictions for the pointers returned by darr_element apply.
 */
inline void *darr_data(struct darr *d)
{
	return d->data;
}

/*
 * Changes the size of the array.
 *
 * Returns 1 on success, 0 on failure.
 *
 * On failure the size and the contents of the array remain untouched.
 *
 * If the new size is the same as the current one, this function will do
 * nothing and report success.
 */
inline int darr_resize(struct darr *d, size_t size)
{
	if (size == d->size) {
		return 1;
	}

	if (size == 0) {
		if (d->data) {
			darr_free(d->data);
			d->data = NULL;
		}

		d->size = size;
		return 1;
	}

	void *new = darr_realloc(d->data, size * d->element_size);

	if (new == NULL) {
		return 0;
	}

	d->size = size;
	d->data = new;
	return 1;
}

/*
 * Returns a pointer to an element by index.
 *
 * The first element is at index 0 and the last element is at size minus one.
 *
 * The pointer is valid until either one of these events occur:
 * - a successful resize is made.
 * - the array is deinitialized.
 *
 * If the array is empty, the returned pointer is invalid.
 *
 * Dereferencing an invalid pointer results in undefined behavior.
 */
inline void *darr_element(struct darr *d, size_t i)
{
	return d->data + darr_data_index(d, i);
}

/*
 * Returns a pointer to the start of the array, which is also a pointer to the
 * first element.
 *
 * If the array is empty, the returned pointer shall not be dereferenced.
 *
 * The restrictions for the pointers returned by darr_element apply.
 *
 * The purpose of this function is to implement the iterator pattern from C++
 */
inline void *darr_begin(struct darr *d)
{
	return darr_element(d, 0);
}

/*
 * Returns a pointer past the end of the array.
 *
 * If the array is empty, the function returns the same as darr_begin.
 *
 * The restrictions for the pointers returned by darr_element also apply.
 *
 * The purpose of this function is to implement the iterator pattern from C++.
 */
inline void *darr_end(struct darr *d)
{
	return darr_element(d, darr_size(d));
}

/*
 * Swaps the elements of the array with another.
 *
 * The arrays must have elements of the same size but the number of elements
 * may differ.
 */
inline void darr_swap(struct darr *d, struct darr *other)
{
	struct darr tmp;

	tmp = *d;
	*d = *other;
	*other = tmp;
}

/*
 * Returns 1 if the array is empty otherwise it returns 0.
 */
inline int darr_empty(struct darr *d)
{
	return d->size == 0;
}

/*
 * Moves a specified number of elements to the left, discarding the ones that
 * would have been moved out of bounds.
 *
 * Steps may not be greater than the size of the array otherwise behavior is
 * undefined.
 */
inline void darr_shift_left(struct darr *d, size_t steps)
{
	size_t offset = darr_data_index(d, steps);
	size_t size = darr_data_size(d);

	memmove(d->data, d->data + offset, size - offset);
}

/*
 * Moves a specified number of elements to the right, discarding the ones that
 * would have been moved out of bounds.
 *
 * Steps may not be greater than the size of the array otherwise behavior is
 * undefined.
 */
inline void darr_shift_right(struct darr *d, size_t steps)
{
	size_t offset = darr_data_index(d, steps);
	size_t size = darr_data_size(d);

	memmove(d->data + offset, d->data, size - offset);
}

/*
 * Decreases the size of the array by a given amount.
 *
 * Returns 1 on success, 0 on failure.
 *
 * On failure the size and the contents of the array remain untouched.
 *
 * Behavior is undefined if the given amount is less than the size of the
 * array.
 */
inline int darr_shrink(struct darr *d, size_t size)
{
	return darr_resize(d, darr_size(d) - size);
}

/*
 * Increases the size of the array by a given amount.
 *
 * Returns 1 on success, 0 on failure.
 *
 * On failure the size and the contents of the array remain untouched.
 */
inline int darr_grow(struct darr *d, size_t size)
{
	return darr_resize(d, darr_size(d) + size);
}

/*
 * This function is deprecated, use darr_element instead.
 *
 * Additionally to doing everything that darr_element does, it guarantees that
 * it will return the same address as darr_end if it is passed the size of the
 * array as the index.
 *
 * This will be removed in version 2.
 */
inline void *darr_address(struct darr *d, size_t i)
{
	return darr_element(d, i);
}

#endif /* DARR_DARR_H */
