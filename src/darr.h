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
inline void darr_global_set_realloc(darr_realloc_t f)
{
	darr_realloc = f;
}

/*
 * Allows you to override any call to free made by darr.
 */
inline void darr_global_set_free(darr_free_t f)
{
	darr_free = f;
}

/*
 * The darr struct. You can initialize it by calling darr_init.
 */
struct darr {
	size_t item_size;
	size_t size;
	char *data;
};

/*
 * This is an implementation detail. Don't call this function.
 *
 * Returns the index of an element.
 */
inline size_t darr_data_index(struct darr *d, size_t i)
{
	return i * d->item_size;
}

/*
 * This is an implementation detail. Don't call this function.
 *
 * Returns the total size of allocated memory.
 */
inline size_t darr_data_size(struct darr *d)
{
	return d->size * d->item_size;
}

/*
 * Initializes a darr struct.
 *
 * You may only initialize the struct once.
 *
 * Call darr_deinit to deinitialize.
 */
inline void darr_init(struct darr *d, size_t item_size)
{
	d->item_size = item_size;
	d->size = 0;
	d->data = NULL;
}

/*
 * Creates a copy of an array.
 *
 * Returns 1 on success, 0 on failure.
 *
 * On failure none of the arrays are modified.
 */
inline int darr_copy(struct darr *d, struct darr *other)
{
	void *new = darr_realloc(NULL, darr_data_size(other));

	if (new == NULL) {
		return 0;
	}

	memcpy(new, other->data, darr_data_size(other));

	d->item_size = other->item_size;
	d->size = other->size;
	d->data = new;
	return 1;
}

/*
 * Deinitializes a darr struct.
 *
 * The struct must have been previously passed to a call to darr_init.
 *
 * You may only deinitialize as many times as you have initialized.
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
 * This is equivalent to calling darr_address with index 0.
 *
 * The restrictions for the addresses returned by darr_address apply.
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

	void *new = darr_realloc(d->data, size * d->item_size);

	if (new == NULL) {
		return 0;
	}

	d->size = size;
	d->data = new;
	return 1;
}

/*
 * Returns the address of an element by its index.
 *
 * The first element is at index 0 and the last element is at size minus one.
 * You may also request the address of the end of the array by passing size as
 * the index but you cannot dereference it.
 *
 * The address is valid until either one of these events occur:
 * - a successful resize is made.
 * - the array is deinitialized.
 *
 * Dereferencing an invalid address results in undefined behavior.
 */
inline void *darr_address(struct darr *d, size_t i)
{
	return d->data + darr_data_index(d, i);
}

/*
 * Returns the address pointing to the first element in the array.
 *
 * If the array is empty, the returned address shall not be dereferenced.
 *
 * The restrictions for the addresses returned by darr_address apply.
 *
 * The purpose of this function is to implement the iterator pattern from C++
 */
inline void *darr_begin(struct darr *d)
{
	return darr_address(d, 0);
}

/*
 * Returns the address pointing past the end of the elements in the array.
 *
 * If the array is empty, the function returns the same as darr_begin.
 *
 * The restrictions for the addresses returned by darr_address apply.
 *
 * The purpose of this function is to implement the iterator pattern from C++
 */
inline void *darr_end(struct darr *d)
{
	return darr_address(d, darr_size(d));
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

#endif /* DARR_DARR_H */
