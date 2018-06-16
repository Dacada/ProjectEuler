#include "euler.h"
#include <curl/curl.h>
#include <sys/wait.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

/*
 * Take size*nmemb bytes from the location pointed to by ptr. buffer
 * is a pointer to a pointer to a char allocated dynamically, with
 * CURL_MAX_WRITE_SIZE+1 bytes the first time. The pointer pointed to
 * is the one allocated dynamically, and it's resized by this
 * function. The taken bytes are all copied to this pointer to char,
 * with a null terminating byte.
 */
static size_t write_to_buffer(void *ptr, size_t size, size_t nmemb, void **buffer) {
  static size_t buffer_capacity_total = CURL_MAX_WRITE_SIZE+1;
  static size_t buffer_index_pointer = 0;
  size_t bytes_to_write = size*nmemb;

  if (bytes_to_write > buffer_capacity_total - buffer_index_pointer) {
    buffer_capacity_total += CURL_MAX_WRITE_SIZE+1;
    void *tmp = realloc(*buffer, buffer_capacity_total);
    if (tmp == NULL) {
      free(*buffer);
      return 0;
    }
    *buffer = tmp;
  }

  void *current_buffer = (void*)((char*)(*buffer)+buffer_index_pointer); //points to the next area to write to
  memcpy(current_buffer, ptr, bytes_to_write);
  buffer_index_pointer += bytes_to_write;
  ((char*)*buffer)[buffer_index_pointer] = 0;

  return bytes_to_write;
}

size_t sorted_array_count_remove_dups(
       NUM_TYPE *array, size_t count,
       NUM_TYPE *array_no_dups, NUM_TYPE *array_count_dups) {

  if (count <= 0) return -1;

  size_t result_i = 1;
  size_t counts_i = 0;
  NUM_TYPE last_n = array[0];
  array_no_dups[0] = last_n;
  array_count_dups[0] = 1;

  for (size_t i=1; i<count; i++) {
    NUM_TYPE n = array[i];
    if (n == last_n) {
      array_count_dups[counts_i]++;
    } else {
      last_n = n;
      array_no_dups[result_i++] = n;
      array_count_dups[++counts_i] = 1;
    }
  }

  return result_i;
}

int time_wrapper(int (fun)(void)) {
  struct timespec ts, te;
  if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1) return -1;
  NUM_TYPE return_code = fun();
  if (clock_gettime(CLOCK_MONOTONIC, &te) == -1) return -1;

  double time_difference = (double)(te.tv_nsec - ts.tv_nsec) / 1000000000.0;
  time_difference += (double)(te.tv_sec - ts.tv_sec);

  if (printf("%f\n", time_difference) < 0) {
    return 1;
  }

  return return_code;
}

NUM_TYPE *factorize(NUM_TYPE n, size_t *count) {
  int pipefd[2];
  if (pipe(pipefd) == -1) goto error;

  pid_t pid = fork();

  if (pid == 0) { // child process
    char n_str[50];
    if (sprintf(n_str, "%"NUM_TYPE_PRINTF, n) == -1) goto child_error;

    if (close(pipefd[0] == -1)) goto child_error;
    if (dup2(pipefd[1], 1) == -1) goto child_error;
    if (close(pipefd[1]) == -1) goto child_error;

    if (execlp("factor", "factor", n_str, NULL) == -1) goto child_error;

  } else if (pid == -1) {
    goto error;
  } else { // parent process
    char buffer[1024];

    if (close(pipefd[1]) == -1) goto error;

    NUM_TYPE *result = malloc(ALLOC_CHUNK_SIZE*sizeof(NUM_TYPE));
    size_t capacity = ALLOC_CHUNK_SIZE;
    size_t result_i = 0;
    NUM_TYPE tmp = 0;
    bool found_colon = false;

    if (result == NULL) goto error;

    ssize_t read_ret;
    while ((read_ret = read(pipefd[0], buffer, sizeof(buffer))) != 0) {
      if (read_ret == -1) goto error;

      for (size_t i=0; i<1024; i++) {
	char c = buffer[i];
	if (found_colon) {
	  if (c == ' ' || c == '\n') {
	    if (tmp != 0) { // don't add 0s
	      // append digit to array
	      result[result_i++] = tmp;
	      if (result_i >= capacity) {
		capacity += ALLOC_CHUNK_SIZE;
		NUM_TYPE *tmp_result = realloc(result, capacity*sizeof(NUM_TYPE));
		if (tmp_result == NULL) goto error;
		result = tmp_result;
	      }
	      if (c == '\n') break;

	      tmp = 0;
	    }
	  } else {
	    // append digit to tmp integer
	    tmp *= 10;
	    tmp += c - 0x30;
	  }
	} else {
	  if (c == ':') {
	    found_colon = true;
	  }
	}
      }
    }

    int wstatus;
    int exit_status;
    wait(&wstatus);
    if (WIFEXITED(wstatus) && (exit_status = WEXITSTATUS(wstatus)) != 0) {
      errno = exit_status;
      goto error;
    }

    close(pipefd[0]);
    *count = result_i;
    return result;
  }

 error:
  *count = -1;
  return NULL;

 child_error:
  exit(errno);
}

/*
static NUM_TYPE modmul(NUM_TYPE a, NUM_TYPE b, NUM_TYPE modulus) {
  if (modulus == 0) return a*b;

  NUM_TYPE r = 0;

  if (a > 0) {
    if (a & 1) {
      if ((r += b) > modulus) r %= modulus;
    }
    a >>= 1;
    if ((b <<= 1) > modulus) b %= modulus;
  }

  return r;
}

static NUM_TYPE modpow(NUM_TYPE base, NUM_TYPE exponent, NUM_TYPE modulus) {
  NUM_TYPE result = 1;

  while (exponent > 0) {
    if (exponent & 1) {
      result = modmul(result, base, modulus);
    }
    base = modmul(base, base, modulus);
    exponent >>= 1;
  }

  return result;
}

// Miller-Rabin primality test
bool is_prime(NUM_TYPE n) {
  static bool first_time = true;
  if (first_time) {
    srand(time(NULL));
    first_time = false;
  }

  if (n < 2) return false;
  else if (n == 2) return true;
  else if (n % 2 == 0) return false;

  NUM_TYPE odd_part_n = n - 1;
  NUM_TYPE times_div_2 = 0;

  while (odd_part_n % 2 == 0) {
    odd_part_n /= 2;
    times_div_2++;
  }

  NUM_TYPE rand_num_pow;
  for (int time=0; time<3; time++) {
    NUM_TYPE rand_num = 2 + (rand() % (n-2));
    rand_num_pow = modpow(rand_num, odd_part_n, n);
    printf("Random number: %lu\nRandom number power: %lu\n\n", n, rand_num_pow);

    if ((rand_num_pow != 1) && (rand_num_pow != n - 1)) {
      NUM_TYPE iter_num = 1;
      while ((iter_num <= times_div_2 - 1) && (rand_num_pow != n - 1)) {
	rand_num_pow = modpow(rand_num_pow, 2, n);
	iter_num++;
      }
      if (rand_num_pow != n - 1) {
	return false;
      }
    }
  }

  return true;
}
*/

bool is_prime(NUM_TYPE n) {
  if (n < 2) return false;

  NUM_TYPE limit = (NUM_TYPE)sqrt((double)n);

  for (size_t i=2; i<=limit; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

NUM_TYPE gcd(NUM_TYPE a, NUM_TYPE b) {
  if (b == 0) {
    return a;
  } else {
    return gcd(b, a%b);
  }
}

NUM_TYPE *primes_sieve(NUM_TYPE limit, size_t *count) {
  bool sieve[limit];
  for (size_t i=0; i<limit; i++) {
    sieve[i] = true;
  }
  sieve[0] = sieve[1] = false;

  NUM_TYPE *result = malloc(limit*sizeof(NUM_TYPE));
  size_t result_i = 0;
  *count = 0;

  if (result == NULL) {
    *count = -1;
    return NULL;
  }

  for (NUM_TYPE i=2; i<limit; i++) {
    if (sieve[i]) {
      result[result_i++] = i;
      *count = *count + 1;

      for (NUM_TYPE j=i*2; j<limit; j+=i) {
	sieve[j] = false;
      }
    }
  }

  return result;
}

char *read_url(char url[]) {
  CURL *curl;
  CURLcode res;
  char *read_data = malloc(CURL_MAX_WRITE_SIZE+1);

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    //curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_buffer);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_data);

    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    if (res != CURLE_OK) {
      return NULL;
    } else {
      return read_data;
    }

  } else {
    return NULL;
  }
}

NUM_TYPE sum_divisors(NUM_TYPE n) {
  size_t count;
  NUM_TYPE *factors = factorize(n, &count);
  if (factors == NULL) return -1;

  NUM_TYPE factors_no_dups[count];
  NUM_TYPE factors_count_dups[count];
  size_t count_no_dups = sorted_array_count_remove_dups(
	factors, count,
	factors_no_dups, factors_count_dups);
  free(factors);
  if (count_no_dups == -1) return -1;

  NUM_TYPE result = 1;
  for (size_t i=0; i<count_no_dups; i++) {
    NUM_TYPE p = factors_no_dups[i];
    NUM_TYPE a = factors_count_dups[i];

    NUM_TYPE s = 0;
    for (NUM_TYPE ai=0; ai<=a; ai++) {
      s += (NUM_TYPE)pow((double)p, (double)ai);
    }

    result *= s;
  }

  return result - n;
}

hash_table_t *hash_table_new(size_t table_size, size_t bucket_size, NUM_TYPE error_return) {
  hash_table_t *new_ht = malloc(sizeof(hash_table_t));

  new_ht->error_return = error_return;
  new_ht->total_buckets = table_size;
  new_ht->bucket_increase = bucket_size;
  new_ht->buckets = calloc(table_size, sizeof(new_ht)); //sizeof pointer

  return new_ht;
}

void hash_table_free(hash_table_t *hashtable) {
  if (hashtable == NULL) return;
  if (hashtable->buckets == NULL) return;

  for (size_t i=0; i<hashtable->total_buckets; i++) {
    hash_table_bucket_t *bucket = hashtable->buckets[i];
    if (bucket != NULL) {
      free(bucket->values);
      free(bucket->indexes);
    }
    free(bucket);
  }

  free(hashtable->buckets);
  free(hashtable);
}

size_t hash_table_hash(NUM_TYPE index, size_t total_buckets) {
  return index % total_buckets; // trivial hash
}

NUM_TYPE hash_table_get(hash_table_t *hashtable, NUM_TYPE index) {
  hash_table_bucket_t *bucket;
  bucket = hashtable->buckets[hash_table_hash(index, hashtable->total_buckets)];

  if (bucket != NULL) {
    for (size_t i=0; i<bucket->next_value; i++) {
      if (bucket->indexes[i] == index) {
	return bucket->values[i];
      }
    }
  }

  return hashtable->error_return;
}

int hash_table_put(hash_table_t *hashtable, NUM_TYPE index, NUM_TYPE value) {
  hash_table_bucket_t *bucket;
  size_t hashed_index = hash_table_hash(index, hashtable->total_buckets);
  bucket = hashtable->buckets[hashed_index];

  if (bucket == NULL) {
    bucket = malloc(sizeof(hash_table_bucket_t));
    if (bucket == NULL) goto error;
    bucket->allocated_size = 0;
    hashtable->buckets[hashed_index] = bucket;
  }

  if (bucket->allocated_size == 0) {
    bucket->allocated_size = hashtable->bucket_increase;
    bucket->next_value = 0;
    bucket->values = calloc(bucket->allocated_size, sizeof(NUM_TYPE));
    if (bucket->values == NULL) goto error;
    bucket->indexes = calloc(bucket->allocated_size, sizeof(NUM_TYPE));
    if (bucket->values == NULL) goto error;
  } else if (bucket->allocated_size == bucket->next_value) {
    bucket->allocated_size += hashtable->bucket_increase;
    bucket->values = realloc(bucket->values, bucket->allocated_size*sizeof(NUM_TYPE));
    if (bucket->values == NULL) goto error;
    bucket->indexes = realloc(bucket->indexes, bucket->allocated_size*sizeof(NUM_TYPE));
    if (bucket->indexes == NULL) goto error;
  }

  bucket->values[bucket->next_value] = value;
  bucket->indexes[bucket->next_value] = index;
  bucket->next_value++;

  return 0;

 error:
  return -1;
}

permutation_enumerator_t *permutation_enumerator_new(
                          void *const *const array,
                          size_t array_len) {
  permutation_enumerator_t *e = NULL;
  e = malloc(sizeof(permutation_enumerator_t));
  if (e == NULL) {
    goto bail;
  }

  e->array = malloc(sizeof(void*)*array_len);
  if (e->array == NULL){
    goto bail;
  }
  memcpy(e->array, array, array_len*sizeof(void*));

  e->i = 0;
  e->array_len = array_len;

  e->c = malloc(sizeof(size_t)*array_len);
  if (e->c == NULL) {
    goto bail;
  }
  for (size_t i=0; i<array_len; i++) {
    e->c[i] = 0;
  }

  e->first = true;

  return e;

  bail:
  if (e != NULL) {
    free(e->array);
    free(e->c);
  }
  free(e);
  return NULL;
}

static void swap(void **array, size_t i1, size_t i2) {
  void *tmp = array[i1];
  array[i1] = array[i2];
  array[i2] = tmp;
}

void **permutation_enumerator_next(permutation_enumerator_t *const e) {
  if (e->first) {
    e->first = false;
    void **r = malloc(sizeof(void*)*e->array_len);
    if (r == NULL) return NULL;
    memcpy(r, e->array, e->array_len*sizeof(void*));
    return r;
  }

  if (e->i >= e->array_len) {
    return NULL;
  }

  while (e->c[e->i] >= e->i) {
    e->c[e->i] = 0;
    e->i++;
  }

  if (e->i >= e->array_len) {
    return NULL;
  }

  if (e->i % 2 == 0) {
    swap(e->array, 0, e->i);
  } else {
    swap(e->array, e->c[e->i], e->i);
  }

  e->c[e->i]++;
  e->i = 0;

  void **r = malloc(sizeof(void*)*e->array_len);
  if (r == NULL) return NULL;
  memcpy(r, e->array, e->array_len*sizeof(void*));
  return r;
}

void permutation_enumerator_free(permutation_enumerator_t *const e) {
  if (e == NULL) return;
  free(e->c);
  free(e->array);
  free(e);
}
