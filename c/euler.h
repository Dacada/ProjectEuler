#ifndef _EULER_H
#define _EULER_H

#define ALLOC_CHUNK_SIZE 2048

#define NUM_TYPE long
#define NUM_TYPE_PRINTF "ld"

#include <stdbool.h>
#include <stdlib.h>

/*
 * Takes an array of sorted integers and its length, and two
 * sufficiently long arrays to store all elements without duplicates,
 * and how many times the corresponding element is repeated. Return -1
 * if count is less than or equal to zero. Otherwise the amount of
 * elements written into the two given arrays.
 */
size_t sorted_array_count_remove_dups(
       NUM_TYPE *array, size_t count,
       NUM_TYPE *array_no_dups, NUM_TYPE *array_count_dups);

/*
 * Runs and times the given pointer to a function returning int and
 * accepting no parameters. Then prints the time. If everything goes
 * correctly, return the return code of the function. Otherwise, in
 * case of error, return 1.
 */
int time_wrapper(int (fun)(void));

/*
 * Given a number and a pointer to another integer, this function
 * returns a pointer to an array of the factors of the given number,
 * and saves the number of factors into the given pointer. The array
 * is allocated dynamically and should be freed later on. On error
 * NULL is returned and count is set to -1.
 */
NUM_TYPE *factorize(NUM_TYPE n, size_t *count);

/*
 * Return whether a number is prime.
 */
bool is_prime(NUM_TYPE n);

/*
 * Return the greatest common divisor of two numbers.
 */
NUM_TYPE gcd(NUM_TYPE a, NUM_TYPE b);

/*
 * Return an array of primes until the given limit by using a
 * sieve. The array is allocated dynamically and should be freed later
 * on. The number of primes returned is saved in the second parameter,
 * a pointer to an integer. On failure returns NULL and sets count to -1.
 */

NUM_TYPE *primes_sieve(NUM_TYPE limit, size_t *count);

/*
 * Return the text in a given url as a zero terminated string of char. Return NULL on failure.
 */
char *read_url(char url[]);

/*
 * Return the sum of the proper divisors of n. Return -1 on failure.
 */
NUM_TYPE sum_divisors(NUM_TYPE n);


#define MAX(a,b) (a > b ? a : b)
#define MIN(a,b) (a < b ? a : b)


/*
 * Hash table implementation. Both keys and values are NUM_TYPE.
 */

typedef struct {
  NUM_TYPE *values;
  NUM_TYPE *indexes;
  size_t allocated_size;
  size_t next_value;
} hash_table_bucket_t;

typedef struct {
  hash_table_bucket_t **buckets;
  size_t total_buckets;
  size_t bucket_increase;
  NUM_TYPE error_return;
} hash_table_t;

/*
 * Allocate space for a new hash table.
 *
 * table_size is the size of the table itself.
 *
 * bucket_size is the size by which of each bucket in the table
 * increments. Starting with this size and incrementing by this much
 * whenever relocating is necessary.
 *
 * error_return is what value will be returned on lookup error.
 *
 * This function only allocates space for the table itself, with all
 * buckets pointing to NULL until they themselves are allocated by
 * other functions.
 *
 * Return NULL on failure.
 */
hash_table_t *hash_table_new(size_t table_size, size_t bucket_size, NUM_TYPE error_return);

void hash_table_free(hash_table_t *hashtable);

size_t hash_table_hash(NUM_TYPE index, size_t total_buckets);

NUM_TYPE hash_table_get(hash_table_t *hashtable, NUM_TYPE index);

// Return -1"' on failure, 0 otherwise
int hash_table_put(hash_table_t *hashtable, NUM_TYPE index, NUM_TYPE value);

// hash_table_remove: hashtable,index -> value

#endif
