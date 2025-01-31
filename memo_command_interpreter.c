#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../memoization/memo_long_int.h"
#include "../random/random.h"
#include "memo_command_interpreter.h"


char RANDOM_VALUES;
const char * GET = "0";
const char * PUT = "1";
const char * DEL = "2";
const char * EXIT = "q";
const char * PROMPT = "> ";


void memo_command_interpreter(int argc, char** argv){
  char cmd[200], *t, token[20][100];
  int64_t g,k,v,*r,num_args;
  initialize_long_int_cache(argc, argv);
  printf("commands (get=0, put=1, del=2, exit=q)\n");
  while(1){
    printf("%s", PROMPT);
    fgets(cmd, 200, stdin);
    num_args = 0;
    t = strtok(cmd, " \n");
    while (t != NULL){
      strcpy(token[num_args++], t);
      t = strtok(NULL, " \n");
    }
    for(g = 0; g < num_args; g++){
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
      printf("using val -->%ld<-- -->%ld<--\n", k, v);
      r = (int64_t *) cache_write_long_int(&k, &v);
      if (r == NULL) {
        printf("Value already found for key %ld.\n", k);
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
    //view_lru_queue();
    //view_lru_queue_logical();
  }
}
