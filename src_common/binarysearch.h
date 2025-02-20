#ifndef PKSV_BINARY_SEARCH_H
#define PKSV_BINARY_SEARCH_H 1

#include <stddef.h>

typedef int bsearch_compare_func(const void *a, const void *b);
typedef void *bsearch_copy_func(const void *a);
typedef void bsearch_free_key_func(void *a);
typedef void bsearch_free_val_func(void *a);

struct bsearch_kv {
  void *key;
  void *value;
};

struct bsearch_root {
  struct bsearch_kv *pairs;
  bsearch_compare_func *compare;
  bsearch_copy_func *copy;
  bsearch_free_key_func *free_key;
  bsearch_free_val_func *free_val;
  size_t size;
  size_t capacity;
};

/** @brief Initialise a bsearch_root structure which is already allocated. */
void bsearch_init_root(struct bsearch_root *root, bsearch_compare_func *compare,
                       bsearch_copy_func *copy, bsearch_free_key_func *free_key,
                       bsearch_free_val_func *free_val);

/** @brief Allocate and initialise a bsearch_root structure. */
struct bsearch_root *bsearch_create_root(bsearch_compare_func *compare,
                                         bsearch_copy_func *copy,
                                         bsearch_free_key_func *free_key,
                                         bsearch_free_val_func *free_val);

/** @brief Free a bsearch_root structure. */
void bsearch_destroy_root(struct bsearch_root *root);

/** @brief Free the contents of a bsearch_root structure, but not the structure
 * itself. */
void bsearch_deinit_root(struct bsearch_root *root);

/** @brief Ensure that the bsearch_root has enough space to hold the given
 * number of elements. */
void bsearch_ensure_capacity(struct bsearch_root *root, size_t capacity);

/** @brief Insert a key/value pair into a bsearch_root. */
size_t bsearch_upsert(struct bsearch_root *kvs, void const *key, void *value);

/** @brief Find a key in a bsearch_root.
 *  @return the index of the matching entry, or kvs->size if not found.
 */
size_t bsearch_find_if_exists(struct bsearch_root *kvs, void const *key);

#endif
