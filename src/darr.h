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
 * Initializes a darr struct that will be a copy of a slice of another one.
 *
 * Returns 1 on success, 0 on failure.
 *
 * On failure, the darr struct is not initialized.
 *
 * Call darr_deinit to deinitialize.
 */
inline int darr_slice(struct darr *d, struct darr *other, size_t i, size_t s)
{
	void *new = darr_realloc(NULL, darr_data_size(other));

	if (new == NULL) {
		return 0;
	}

	d->data = new;
	d->element_size = other->element_size;
	d->size = s;

	memcpy(
		d->data,
		other->data + darr_data_index(other, i),
		darr_data_index(d, d->size));

	return 1;
}

/*
 * Deinitializes a darr struct.
 *
 * The struct must have been previously initialized with either darr_init or
 * darr_copy. You may not pass a struct that has not been initialized.
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
 * - size changes.
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
 * Moves a range of elements to the left, discarding the ones that would have
 * been moved out of the boundaries of the slice.
 *
 * The start parameter must be an index into the array that denotes where the
 * slice starts.
 *
 * The size parameter must be a positive number that does not exceed the size
 * of the array counting from the given index that denotes the size of the
 * slice.
 *
 * The steps parameter may not be greater than the size of the array plus the
 * given start index.
 */
inline void darr_shift_slice_left(
	struct darr *d,
	size_t steps,
	size_t start,
	size_t size)
{
	size_t data_offset = darr_data_index(d, steps);
	size_t data_start = darr_data_index(d, start);
	size_t data_size = darr_data_index(d, size) - data_offset;

	memmove(
		d->data + data_start,
		d->data + data_start + data_offset,
		data_size);
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
 * Moves a range of elements to the right, discarding the ones that would have
 * been moved out of the boundaries of the slice.
 *
 * The start parameter must be an index into the array that denotes where the
 * slice starts.
 *
 * The size parameter must be a positive number that does not exceed the size
 * of the array counting from the given index that denotes the size of the
 * slice.
 *
 * The steps parameter may not be greater than the size of the array plus the
 * given start index.
 */
inline void darr_shift_slice_right(
	struct darr *d,
	size_t steps,
	size_t start,
	size_t size)
{
	size_t data_offset = darr_data_index(d, steps);
	size_t data_start = darr_data_index(d, start);
	size_t data_size = darr_data_index(d, size) - data_offset;

	memmove(
		d->data + data_start + data_offset,
		d->data + data_start,
		data_size);
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

/*
 * Returns a pointer to the first element of the array.
 *
 * The behavior of this function is undefined if the array is empty.
 *
 * The restrictions for the pointers returned by darr_element apply.
 */
inline void *darr_first(struct darr *d)
{
	return darr_element(d, 0);
}

/*
 * Returns a pointer to the last element of the array.
 *
 * The behavior of this function is undefined if the array is empty.
 *
 * The restrictions for the pointers returned by darr_element apply.
 */
inline void *darr_last(struct darr *d)
{
	return darr_element(d, darr_size(d) - 1);
}

/*
 * Copies the elements of another array to the end of the array.
 *
 * Both arrays must have elements of the same size otherwise behavior is
 * undefined.
 *
 * Returns 1 on success, 0 on failure.
 *
 * On failure the size and the contents of the array remain untouched.
 */
inline int darr_append(struct darr *d, struct darr *other)
{
	size_t offset = darr_size(d);

	if (!darr_grow(d, darr_size(other))) {
		return 0;
	}

	memcpy(darr_element(d, offset), other->data, darr_data_size(other));

	return 1;
}

/*
 * Copies the elements of another array to the start of the array.
 *
 * Both arrays must have elements of the same size otherwise behavior is
 * undefined.
 *
 * Returns 1 on success, 0 on failure.
 *
 * On failure the size and the contents of the array remain untouched.
 */
inline int darr_prepend(struct darr *d, struct darr *other)
{
	if (!darr_grow(d, darr_size(other))) {
		return 0;
	}

	darr_shift_right(d, darr_size(other));

	memcpy(d->data, other->data, darr_data_size(other));

	return 1;
}

/*
 * Copies the elements of another array to the given index in the array.
 *
 * Both arrays must have elements of the same size otherwise behavior is
 * undefined.
 *
 * Returns 1 on success, 0 on failure.
 *
 * On failure the size and the contents of the array remain untouched.
 */
inline int darr_insert(struct darr *d, size_t i, struct darr *other)
{
	if (!darr_grow(d, darr_size(other))) {
		return 0;
	}

	darr_shift_slice_right(d, darr_size(other), i, darr_size(d) - i);

	memcpy(
		d->data + darr_data_index(d, i),
		other->data,
		darr_data_size(other));

	return 1;
}

/*
 * Removes a slice of elements from the array.
 *
 * Returns 1 on success, 0 on failure.
 */
inline int darr_remove(struct darr *d, size_t start, size_t size)
{
	darr_shift_slice_left(d, size, start, darr_size(d) - start);

	if (!darr_shrink(d, size)) {
		// TODO: With the current implementation, I am assuming that
		// this situation will never happpen. Though I may be wrong. In
		// that case, the shifting on the array needs to be reverted.
		return 0;
	}

	return 1;
}

/*
 * Initializes a darr struct that contains elements extracted from another
 * array.
 *
 * Returns 1 on success, 0 on failure.
 *
 * On failure, the darr struct is not initialized and the other array is left
 * untouched.
 *
 * Call darr_deinit to deinitialize.
 */
inline int darr_extract(struct darr *d, struct darr *other, size_t i, size_t s)
{
	if (!darr_slice(d, other, i, s)) {
		return 0;
	}

	if (!darr_remove(other, i, s)) {
		darr_deinit(d);
		return 0;
	}

	return 1;
}

#endif /* DARR_DARR_H */
