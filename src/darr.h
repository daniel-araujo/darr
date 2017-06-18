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

#endif /* DARR_DARR_H */
