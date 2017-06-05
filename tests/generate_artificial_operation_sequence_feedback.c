/*
 * File:   generate_operation_sequence_feedback.c
 * Author: benjamin
 *
 * Created on Aug 25, 2015, 1:20:46 AM
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define RUN_TEST  
/*
#define SHOW_PROGRESS  
*/
#define WRITE_FILE  
#define READ 0
#define WRITE 1
#define DELETE 2

#define NO_DELETIONS 0
#define WITH_DELETIONS 1

void test1(int num_operations, int max_key, int capacity, int deletions_enabled) {
    
    int g, * key, * load, max_load;
    int64_t size;
    FILE * fp;
    int * operation, * status, * cache;
    char fname[200];
    
    printf("generate_operation_sequence_feedback\n");
    sprintf(fname, "../misc_phd/input/operation_sequences/without_feedback/%d/operation_sequence_without_feedback-%d-%d", 
            num_operations, num_operations, max_key);
    fp = fopen(fname,"r");
    size = 0;
    max_load = 0;
    fscanf(fp, "%d\n", &num_operations);
    fscanf(fp, "%d\n", &max_key);
    operation = calloc(num_operations, sizeof(int));
    key = calloc(num_operations, sizeof(int));
    status = calloc(num_operations, sizeof(int));
    load = calloc(num_operations, sizeof(int));
    cache = calloc(max_key, sizeof(int));
    
    printf("%d %d\n", num_operations, max_key);
    for(g=0; g<num_operations; g++){
        fscanf(fp, "%d %d\n", &operation[g], &key[g]);
        #ifdef SHOW_PROGRESS
            printf("%d %d %d\n", g, operation[g], key[g]);
        #endif
    }
    fclose(fp);
    
    for(g=0; g<num_operations; g++){
        #ifdef SHOW_PROGRESS
            printf("operation %d: %d %d\n", g, operation[g], key[g]);
        #endif
        switch(operation[g]){
            case READ:
                if(cache[key[g]]==0){
                    status[g] = 0; /* not found */
                } else {
                    status[g] = 1; /* found */
                }
                break;
            case WRITE:
                if(size>=capacity){
                    status[g] = 0; /* cache is full, therefore cannot write key */
                } else {
                    if(cache[key[g]]==0){ /* not already in cache, therefore write key */
                        cache[key[g]]=1;
                        status[g] = 1;
                        size++;
                    } else {
                        status[g] = 0; /* already in cache, therefore cannot write key */
                    }
                }
                break;
            case DELETE:
                #ifdef SHOW_PROGRESS
                    printf("deletion of %d\n", key[g]);
                #endif
/*
                printf("cache: %d\n", cache[key[g]]);
*/
                if(deletions_enabled){
                    if(cache[key[g]]==0){ /* key not found, therefore cannot delete key */
                        #ifdef SHOW_PROGRESS
                            printf("failed deletion\n");
                        #endif
                        status[g] = 0;
                    } else { /* key is in cache, therefore delete key */
                        #ifdef SHOW_PROGRESS
                            printf("succeeded deletion\n");
                        #endif
                        cache[key[g]] = 0;
                        status[g] = 1;
                        size--;
                        if(size<0){
                            fprintf(stderr, "Error: cache underflow. How did the size of the cache become negative?!\n");
                            exit(EXIT_FAILURE);
                        }
                    }
                } else {
                    status[g] = 0;
                }
/*
                printf("done!\n");
*/
                break;
            default:
                fprintf(stderr, "bad operation\n!");
                exit(EXIT_FAILURE);
        }
        load[g] = size;
        max_load = (load[g] > max_load) ? load[g] : max_load;
    }
    #ifdef SHOW_PROGRESS
        printf("feedback\n");
        for(g=0; g<num_operations; g++){
            printf("%d %d %d --- %d\n", operation[g], key[g], status[g], load[g]);
        }
    #endif
    printf("num_operations=%d  max_key=%d  capacity=%d  max_load=%d  deletions_enabled=%d\n", 
            num_operations, max_key, capacity, max_load, deletions_enabled);
    
    #ifdef WRITE_FILE
        if(deletions_enabled){
            sprintf(fname, "../misc_phd/input/operation_sequences/feedback/deletions/%d/operation_sequence_with_feedback-%d-%d-%d-%d", 
                    num_operations, num_operations, max_key, capacity, max_load);
        } else {
            sprintf(fname, "../misc_phd/input/operation_sequences/feedback/no_deletions/%d/operation_sequence_with_feedback-%d-%d-%d-%d", 
                    num_operations, num_operations, max_key, capacity, max_load);
        }
        fp = fopen(fname,"w");
        fprintf(fp, "0\n");
        fprintf(fp, "%d\n", num_operations);
        fprintf(fp, "%d\n", max_key);
        fprintf(fp, "%d\n", capacity);
        fprintf(fp, "%d\n", max_load);
        fprintf(fp, "%d\n", deletions_enabled);
        for(g=0; g<num_operations; g++){
            fprintf(fp, "%d %d %d\n", operation[g], key[g], status[g]);
        }
        fclose(fp);
    #endif
}

int main(int argc, char** argv) {

    #ifdef RUN_TEST
        printf("%%TEST_STARTED%% (generate_artificial_operation_sequence_feedback\n");

        test1(100,20,16,WITH_DELETIONS);
        test1(100,20,16,NO_DELETIONS);
        test1(100,20,32,WITH_DELETIONS);
        test1(100,20,32,NO_DELETIONS);
        
        test1(1000,40,32,WITH_DELETIONS);
        test1(1000,40,32,NO_DELETIONS);
        test1(1000,40,64,WITH_DELETIONS);
        test1(1000,40,64,NO_DELETIONS);
        
        test1(10000,400,256,WITH_DELETIONS);
        test1(10000,400,256,NO_DELETIONS);
        test1(10000,400,512,WITH_DELETIONS);
        test1(10000,400,512,NO_DELETIONS);
        
        test1(100000,400,256,WITH_DELETIONS);
        test1(100000,400,256,NO_DELETIONS);
        test1(100000,400,512,WITH_DELETIONS);
        test1(100000,400,512,NO_DELETIONS);
        
        test1(100000,800,512,WITH_DELETIONS);
        test1(100000,800,512,NO_DELETIONS);
        test1(100000,800,1024,WITH_DELETIONS);
        test1(100000,800,1024,NO_DELETIONS);
        
        test1(100000,40000,32768,WITH_DELETIONS);
        test1(100000,40000,32768,NO_DELETIONS);
        test1(100000,40000,65536,WITH_DELETIONS);
        test1(100000,40000,65536,NO_DELETIONS);
        
        test1(100000,80000,65536,WITH_DELETIONS);
        test1(100000,80000,65536,NO_DELETIONS);
        test1(100000,80000,131072,WITH_DELETIONS);
        test1(100000,80000,131072,NO_DELETIONS);
        printf("%%TEST_FINISHED%% (generate_artificial_operation_sequence_feedback)\n");
    #endif
    return (EXIT_SUCCESS);
}
