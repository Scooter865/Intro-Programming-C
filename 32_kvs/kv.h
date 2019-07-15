#ifndef __KV_H__
#define __KV_H__

/*kvpair_t contains key and value strings*/
struct _kvpair_t {
  char * key;
  char * val;
};
typedef struct _kvpair_t kvpair_t;

/*kvarray_t contains the count of key-value pairs and an
array of pointers each of which points at a kvpair_t*/
struct _kvarray_t {
  size_t nPairs;
  kvpair_t ** pairs;
};
typedef struct _kvarray_t kvarray_t;


kvarray_t * readKVs(const char * fname);

void freeKVs(kvarray_t * pairs);

void printKVs(kvarray_t * pairs);

char * lookupValue(kvarray_t * pairs, const char * key);

#endif
