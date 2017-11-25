#include "memo_command_interpreter.h"

#define FALSE 0
#define TRUE 1

char * default_hashing_algorithm = "MurmurHash32";
char * default_collision_resolution_type = "linear_probe";
char * default_caching_strategy = "hashing";

int64_t NON__VALUE = -1;
int64_t NON__POSITION = -1;
uint64_t KEY_LENGTH = 4;
uint64_t VALUE_LENGTH = sizeof (int64_t);
char RANDOM_VALUES;
uint64_t default_table_size = 8;
uint64_t default_queue_size = 4;

void initialize(int argc, char ** argv) {

  char hashing_algorithm[100], collision_resolution_type[100];
  char caching_strategy[100];
  uint64_t g, k, table_size, queue_size;
  int64_t t;
  void * non_value, * non_position;
  size_t key_length, value_length;
  uint8_t cuckoo_k;

  /* defaults */
  strcpy(hashing_algorithm, default_hashing_algorithm);
  strcpy(collision_resolution_type, default_collision_resolution_type);
  strcpy(caching_strategy, default_caching_strategy);
  table_size = default_table_size;
  queue_size = default_queue_size;
  non_value = &NON__VALUE;
  non_position = &NON__POSITION;
  key_length = KEY_LENGTH;
  value_length = VALUE_LENGTH;
  RANDOM_VALUES = TRUE;
  cuckoo_k = 2;

  /* parse options */
  for (g = 0; g < argc; g++) {
    if (!strcmp(argv[g], "-h")) {
      if (g + 1 < argc) {
        strcpy(hashing_algorithm, &argv[++g]);
      }
    } else if (!strcmp(argv[g], "-t")) {
      if (g + 1 < argc) {
        table_size = (int64_t) atoi(argv[++g]);
      }
    } else if (!strcmp(argv[g], "-c")) {
      if (g + 1 < argc) {
        strcpy(collision_resolution_type, &argv[++g][0]);
      }
    } else if (!strcmp(argv[g], "-s")) {
      if (g + 1 < argc) {
        strcpy(caching_strategy, &argv[++g][0]);
      }
    } else if (!strcmp(argv[g], "-q")) {
      if (g + 1 < argc) {
        t = (int64_t) atoi(argv[++g]);
        if (t > 0) {
          queue_size = t;
        }
      }
    } else if (!strcmp(argv[g], "-k")) {
      if (g + 1 < argc) {
        t = (int64_t) atoi(argv[++g]);
        if (t > 0) {
          key_length = t;
        } else {
          printf("Key length must be positive. Default key length = %d\n", (int) key_length);
        }
      }
    } else if (!strcmp(argv[g], "-v")) {
      if (g + 1 < argc) {
        value_length = (uint64_t) atoi(argv[++g]);
      }
    } else if (!strcmp(argv[g], "-u")) {
      if (g + 1 < argc) {
        cuckoo_k = (uint8_t) atoi(argv[++g]);
        printf("cuckoo_k %d\n", cuckoo_k);
        if (cuckoo_k != 2 && cuckoo_k != 3 && cuckoo_k != 4) {
          printf("Cuckoo_k must be either 2, 3, or 4. Default is 2\n");
          cuckoo_k = 2;
        }
      }
    }
  }

  if (queue_size >= table_size) {
    table_size = default_table_size;
    queue_size = default_queue_size;
    printf("Queue size must be smaller than table_size. Reverting to defaults: table size = %ld, queue size = %ld\n",
            table_size, queue_size);
  }

  initialize_memoization(
          hashing_algorithm, table_size, non_value, non_position,
          key_length, value_length, collision_resolution_type,
          caching_strategy, queue_size, cuckoo_k);
}

void memo_command_interpreter(int argc, char** argv) {

  char cmd[200], * t, token[20][100];
  unsigned char * key;
  uint64_t n, g;
  int64_t r, * lp;

  initialize(argc, argv);
  while (TRUE) {
    printf("> ");
    fgets(cmd, 200, stdin);
    g = 0;
    t = strtok(cmd, " \n");
    while (t != NULL) {
      strcpy(token[g++], t);
      t = strtok(NULL, " \n");
    }
    n = g;
    /*
            for(g=0; g<n; g++){
                printf("%d: <<%s>>\n", g, token[g]);
            }
     */
    if (n > 0 && !strcmp(token[0], "exit")) {
      exit(0);
    }
    if (!strcmp(token[0], "get")) {
      r = (int64_t) atoi(token[1]);
      key = (int64_t *) & r;
      lp = (int64_t *) cache_read(key);
      if (*lp == NON__VALUE) {
        printf("Value %ld not found\n", r);
      } else {
        printf("Value %ld was found\n", *lp);
      }
    }
    if (!strcmp(token[0], "put")) {
      if (n == 1) {
        r = rand_in_range(0, 10);
        printf("put without second argument, random value %ld\n", r);
      } else {
        r = (int64_t) atoi(token[1]);
        printf("put second argument %ld\n", r);
      }
      key = (int64_t *) & r;
      lp = (int64_t *) cache_read(key);
      if (*lp == NON__VALUE) {
        key = (int64_t *) & r;
        lp = (int64_t *) cache_write(key);
        *lp = r;
      } else {
        printf("Value %ld already in cache.\n", *lp);
      }
    }
    if (!strcmp(token[0], "del")) {
      if (n >= 2) {
        r = (int64_t) atoi(token[1]);
        key = (int64_t *) & r;
        lp = (int64_t *) cache_read(key);
        if (*lp == NON__VALUE) {
          printf("Value %ld not found\n", r);
        } else {
          printf("Value %ld was found, attempting deletion\n", r);
          if (cache_delete(key) == 0) {
            printf("Deletion of %ld succeeded.\n", r);
          } else {
            printf("Attempted deletion of %ld failed\n", r);
          }
        }
      } else {
        printf("delete needs key argument.\n");
      }
    }

    view_hashtable();
    view_lru_queue();
  }
}
