#ifndef LIST_H_
#define LIST_H_

#include <assert.h> // for assert
#include <stdlib.h> // for malloc/realloc/free
#include <stdbool.h>

#define List(type) type*

#define _list_set_capacity(list, size) do { \
	if (list) {                             \
		((size_t *)(list))[-1] = (size);    \
	}                                       \
} while (false)

#define _list_set_size(list, size) do {   \
	if (list) {                           \
		((size_t *)(list))[-2] = (size);  \
	}                                     \
} while (0)


#define list_capacity(list) \
	((list) ? ((size_t *)(list))[-1] : (size_t)0)

#define list_size(list) \
	((list) ? ((size_t *)(list))[-2] : (size_t)0)

#define list_empty(list) \
	(cvector_size(list) == 0)

#define _list_grow(list, new_capacity) do {                                       \
	const size_t cv_sz = (new_capacity) * sizeof(*(list)) + (sizeof(size_t) * 2); \
	if (!(list)) {                                                                \
		size_t *cv_p = malloc(cv_sz);                                             \
		assert(cv_p);                                                             \
		(list) = (void *)(&cv_p[2]);                                              \
		_list_set_capacity((list), (new_capacity));                               \
		_list_set_size((list), 0);                                                \
	} else {                                                                      \
		size_t *cv_p1 = &((size_t *)(list))[-2];                                  \
		size_t *cv_p2 = realloc(cv_p1, (cv_sz));                                  \
		assert(cv_p2);                                                            \
		(list) = (void *)(&cv_p2[2]);                                             \
		_list_set_capacity((list), (new_capacity));                               \
	}                                                                             \
} while (false)


#define pop_back(list) do {                 \
	_list_set_size((list), list_size(list) - 1); \
} while (false)

#define delete_list_item(list, i) do {                     \
	if (list) {                                            \
		const size_t cv_sz = list_size(list);              \
		if ((i) < cv_sz) {                                 \
			_list_set_size((list), cv_sz - 1);             \
			size_t cv_x;                                   \
			for (cv_x = (i); cv_x < (cv_sz - 1); ++cv_x) { \
				(list)[cv_x] = (list)[cv_x + 1];           \
			}                                              \
		}                                                  \
	}                                                      \
} while (0)

#define delete_list(list) do {                \
	if (list) {                               \
		size_t *p1 = &((size_t *)(list))[-2]; \
		free(p1);                             \
	}                                         \
} while (false)

#ifdef CVECTOR_LOGARITHMIC_GROWTH

#define push_back(list, value) do {                            \
	size_t cv_cap = list_capacity(list);                       \
	if (cv_cap <= list_size(list)) {                           \
		_list_grow((list), !cv_cap ? cv_cap + 1 : cv_cap * 2); \
	}                                                          \
	list[list_size(list)] = (value);                           \
	_list_set_size((list),  list_size(list) + 1);              \
} while (false)

#else

#define push_back(list, value) do {              \
	size_t cv_cap = list_capacity(list);         \
	if (cv_cap <= list_size(list)) {             \
		_list_grow((list), cv_cap + 1);          \
	}                                            \
	list[list_size(list)] = (value);             \
	_list_set_size((list), list_size(list) + 1); \
} while (false)

#endif /* CVECTOR_LOGARITHMIC_GROWTH */

#define list_copy(from, to) do {                  \
	for(size_t i = 0; i < list_size(from); i++) { \
		push_back(to, from[i]);	                  \
	}                                             \
} while (false)

#endif
