#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef enum {
	Empty,
	Filled,
	Deleted
} BucketState;

#define _Bucket(type) struct { \
	BucketState state;         \
	char* key;                 \
	type value;                \
}

#define HashMap(type) struct { \
	size_t capacity;           \
	size_t size;               \
	_Bucket(type)* buckets;    \
}*

#define capacity(hashmap) \
	(hashmap ? hashmap->capacity : 0)

#define size(hashmap) \
	(hashmap ? hashmap->size : 0)

#define _grow_hashmap(hashmap) \
	resize_hashmap(hashmap, capacity(hashmap) * 2);

#define _shrink_hashmap(hashmap) \
	resize_hashmap(hashmap, capacity(hashmap) / 2);

#define _insert_item_internal(hashmap, key2, value2) do {          \
	size_t index = 0;                                              \
	size_t attempt = 0;                                            \
	while (true) {                                                 \
		index = _get_hash(key2, capacity(hashmap), attempt);       \
		if ((*hashmap).buckets[index].state == Empty)   break;     \
		if ((*hashmap).buckets[index].state == Deleted) break;     \
			if ((*hashmap).buckets[index].state == Filled          \
			&& strcmp((*hashmap).buckets[index].key, key2) == 0) { \
			_delete_hashmap_item(hashmap, index);                  \
			break;                                                 \
		}                                                          \
		attempt += 1;                                              \
	}                                                              \
	(*hashmap).buckets[index].state = Filled;                      \
	(*hashmap).buckets[index].key = strdup(key2);                  \
	(*hashmap).buckets[index].value = value2;                      \
	(*hashmap).size += 1;                                          \
} while (false)

#define insert_item(hashmap, key, value) do {                       \
	if (hashmap == NULL) {                                          \
		resize_hashmap(hashmap, 53);                                \
	}                                                               \
	if (((float) (size(hashmap) + 1) / capacity(hashmap)) >= 0.7) { \
		_grow_hashmap(hashmap);                                     \
	}                                                               \
	if (((float) (size(hashmap) + 1) / capacity(hashmap)) <= 0.1) { \
		_shrink_hashmap(hashmap);                                   \
	}                                                               \
	_insert_item_internal(hashmap, key, value);                     \
} while (false)

#define get_item(hashmap, key2) ({ \
	typeof((*(*hashmap).buckets).value)* __value = NULL;            \
	size_t attempt = 0;                                             \
	while (true) {                                                  \
		size_t index = _get_hash(key2, capacity(hashmap), attempt); \
		if (hashmap->buckets[index].state == Filled) {              \
			if (strcmp(hashmap->buckets[index].key, key2) == 0) {   \
				__value = &(hashmap->buckets[index].value);         \
			}                                                       \
		}                                                           \
		if (hashmap->buckets[index].state == Empty) break;          \
		if (attempt + 1 > capacity(hashmap))        break;          \
		attempt += 1;                                               \
	}                                                               \
	__value;                                                        \
})

#define delete_item(hashmap, key2) do {                           \
	size_t attempt = 0;                                           \
	while (true) {                                                \
		int index = _get_hash(key2, hashmap->capacity, attempt);  \
		if (hashmap->buckets[index].state == Filled) {            \
			if (strcmp(hashmap->buckets[index].key, key2) == 0) { \
				_delete_hashmap_item(hashmap, index);             \
				break;                                            \
			}                                                     \
		}                                                         \
		if (hashmap->buckets[index].state == Empty) break;        \
		if (attempt + 1 > hashmap->capacity)        break;        \
		attempt += 1;                                             \
	}                                                             \
} while (false)

#define resize_hashmap(hashmap, new_capacity) do {                                                                     \
	if (new_capacity > size(hashmap)) {                                                                                \
		typeof(hashmap) new_hashmap = malloc(sizeof(typeof(*hashmap)));                                                \
		assert(new_hashmap);                                                                                           \
		new_hashmap->capacity = _next_prime(new_capacity);                                                             \
		new_hashmap->size = 0;                                                                                         \
		new_hashmap->buckets = (typeof(hashmap->buckets)) malloc(capacity(new_hashmap) * sizeof(*(hashmap->buckets))); \
		assert(new_hashmap->buckets);                                                                                  \
		for (size_t i = 0; i < capacity(new_hashmap); i++) {                                                           \
			new_hashmap->buckets[i].state = Empty;                                                                     \
		}                                                                                                              \
		size_t items_moved = 0;                                                                                        \
		for (size_t i = 0; i < capacity(hashmap); i++) {                                                               \
			if (hashmap->buckets[i].state == Filled) {                                                                 \
				char* key = (*hashmap).buckets[i].key;                                                                 \
				typeof(hashmap->buckets[i].value) value = hashmap->buckets[i].value;                                   \
				_insert_item_internal(new_hashmap, key, value);                                                        \
				items_moved += 1;                                                                                      \
				if (items_moved == hashmap->size) break;                                                               \
			}                                                                                                          \
		}                                                                                                              \
		if (hashmap) delete_hashmap(hashmap);                                                                          \
		hashmap = new_hashmap;                                                                                         \
	}                                                                                                                  \
} while (false)

#define delete_hashmap(hashmap) do {                 \
	for (size_t i = 0; i < capacity(hashmap); i++) { \
		if (hashmap->buckets[i].state == Filled) {   \
			_delete_hashmap_item(hashmap, i);        \
		}                                            \
	}                                                \
	if (hashmap) {                                   \
		free(hashmap->buckets);                      \
		free(hashmap);                               \
		hashmap = NULL;                              \
	}                                                \
} while (false)

#define _delete_hashmap_item(hashmap, index) do { \
	hashmap->size -= 1;                           \
	hashmap->buckets[index].state = Deleted;      \
	free(hashmap->buckets[index].key);            \
	hashmap->buckets[index].key = NULL;           \
} while (false)

// From https://stackoverflow.com/a/25525853
static long _hashmap_pow(long base, long exp) {
	if(exp < 0) return -1;
	long result = 1;
	while (exp) {
		if (exp & 1)
		result *= base;
		exp >>= 1;
		base *= base;
	}
	return result;
}

static bool _is_prime(const size_t n) {
	for (int i = 2; i < n / 2; i++) {
		if (n % i == 0) return false;
	}
	return true;
}

static size_t _next_prime(size_t n) {
	while (!_is_prime(n)) {
		n++;
	}
	return n;
}

static int _hash(const char* str, const int a, const int m) {
	long hash = 0;
	for (size_t i = 0; i < strlen(str); i++) {
		hash +=  (long) _hashmap_pow(a, strlen(str) - (i + 1)) * str[i];
		hash = hash % m;
	}
	return (int)hash;
}

static int _get_hash(const char* str, const int num_buckets, const int attempt) {
	const int hash_a = _hash(str, 547, num_buckets);
	const int hash_b = _hash(str, 1607, num_buckets);
	return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

#endif
