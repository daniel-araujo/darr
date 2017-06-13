#ifndef DARR_DARR_H
#define DARR_DARR_H

#include <stdlib.h>
#include <string.h>

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
inline size_t darr_data_index(struct darr *d, int i)
{
	return i * d->item_size;
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
 * Deinitializes a darr struct.
 *
 * The struct must have been previously passed to a call to darr_init.
 *
 * You may only deinitialize as many times as you have initialized.
 */
inline void darr_deinit(struct darr *d)
{
	if (d->data) {
		free(d->data);
	}
}

/*
 * Returns the current size of the array.
 */
inline int darr_size(struct darr *d)
{
	return d->size;
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
			free(d->data);
			d->data = NULL;
		}

		d->size = size;
		return 1;
	}

	void *new = realloc(d->data, size);

	if (new == NULL) {
		return 0;
	}

	d->size = size;
	d->data = new;
	return 1;
}

/*
 * Returns the address of an element.
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
 * Sets the value of an element.
 *
 * This function assumes that it can safely read the contents pointed to by the
 * address.
 *
 * The index must be a positive value less than the current size of the array.
 *
 * Passing an invalid index results in undefined behavior.
 */
inline void darr_set(struct darr *d, size_t i, void *value)
{
	memcpy(darr_address(d, i), value, d->item_size);
}

/*
 * Copies the value of an element to the given address.
 *
 * This function assumes that it can safely dereference the given the address.
 *
 * The index must be a value smaller than the size.
 *
 * Passing an invalid index results in undefined behavior.
 */
inline void darr_copy(struct darr *d, size_t i, void *value)
{
	memcpy(value, darr_address(d, i), d->item_size);
}

#endif /* DARR_DARR_H */
