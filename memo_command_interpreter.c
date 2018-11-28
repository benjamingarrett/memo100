#include "memo_command_interpreter.h"

char RANDOM_VALUES;
const char * GET = "get";
const char * PUT = "put";
const char * DEL = "del";
const char * EXIT = "exit";
const char * PROMPT = "> ";

void memo_command_interpreter(int argc, char** argv) {

  char cmd[200], *t, token[20][100];
  int64_t k, v, *r, num_args;

  initialize_long_int_cache(argc, argv);
  printf("commands (get, put, del)\n");
  while(1){
    printf("%s", PROMPT);
    fgets(cmd, 200, stdin);
    num_args = 0;
    t = strtok(cmd, " \n");
    while (t != NULL){
      strcpy(token[num_args++], t);
      t = strtok(NULL, " \n");
    }
    for(int64_t g = 0; g < num_args; g++){
      printf("%ld: <<%s>>\n", g, token[g]);
    }
    if(num_args < 0){
      fprintf(stderr, "No command given!\n");
      exit(1);
    }
    if( ! strcmp(token[0], EXIT)){
      printf("Goodbye!\n");
      exit(0);
    }
    else if(num_args == 1){
      fprintf(stderr, "No command arguments given!\n");
      exit(1);
    }
    else if( ! strcmp(token[0], GET)){
      printf("get\n");
      k = (int64_t)atoi(token[1]);
      printf("using key -->%ld<-- -->%ld<--\n", &k, k);
      r = (int64_t *) cache_read_long_int(&k);
      if(r == NULL){
        printf("Value for key %ld not found\n", k);
      } else {
        printf("Value %ld found for key %ld was found\n", *r, k);
      }
    }
    else if( ! strcmp(token[0], PUT)){
      printf("put\n");
      k = (int64_t)atoi(token[1]);
      printf("using key -->%ld<-- -->%ld<--\n", &k, k);
      if(num_args >= 3){
        v = (int64_t)atoi(token[2]);
      } else {
        v = (int64_t)atoi(token[1]);
      }
      printf("using val -->%ld<-- -->%ld<--\n", &v, v);
      r = (int64_t *) cache_read_long_int(&k);
      if (r == NULL) {
        cache_write_long_int(&k, &v);
      } else {
        printf("Value %ld already found for key %ld.\n", *r, k);
      }
    }
    else if( ! strcmp(token[0], DEL)){
      printf("del\n");
      k = (int64_t)atoi(token[1]);
      printf("using key %ld %ld\n", &k, k);
      r = (int64_t *) cache_read_long_int(&k);
      if(r == NULL){
        printf("Value for key %ld not found.\n", k);
      } else {
        printf("Value %ld found for key %ld, attempting deletion.\n", *r, k);
        if(cache_delete_long_int(&k) == 0){
          printf("Deletion of %ld succeeded.\n", k);
        } else {
          printf("Attempted deletion of %ld failed.\n", k);
        }
      }
    }
    else {
      printf("unknown command %s\n", token[0]);
      exit(1);
    }
    view_hashtable_long_int();
    view_lru_queue();
    view_lru_queue_logical();
  }
}
