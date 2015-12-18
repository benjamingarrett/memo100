/*
 * File:   generate_operation_sequence_feedback.c
 * Author: benjamin
 *
 * Created on Aug 25, 2015, 1:20:46 AM
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*
#define RUN_TEST  
*/
#define WRITE_FILE  
#define READ 0
#define WRITE 1
#define DELETE 2

void test1() {
    
    int g, max_key;
    int num_operations, * key, capacity, * load, max_load;
    int64_t size;
    FILE * fp;
    int * operation, * status, * cache;
    
    printf("generate_operation_sequence_feedback\n");
    fp = fopen("operation_sequence_without_feedback","r");
    capacity = 128;
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
        printf("%d %d %d\n", g, operation[g], key[g]);
    }
    fclose(fp);
    
    
    for(g=0; g<num_operations; g++){
        
        printf("operation %d: %d %d\n", g, operation[g], key[g]);
        
        switch(operation[g]){
            case READ:
                if(cache[key[g]]==0){
                    status[g] = 0;
                } else {
                    status[g] = 1;
                }
                break;
            case WRITE:
                if(size>=capacity){
                    status[g] = 0;
                } else {
                    if(cache[key[g]]==0){
                        cache[key[g]]=1;
                        status[g] = 1;
                        size++;
                    } else {
                        status[g] = 0;
                    }
                }
                break;
            case DELETE:
                printf("deletion of %d\n", key[g]);
                
/*
                printf("cache: %d\n", cache[key[g]]);
*/
                
                if(cache[key[g]]==0){
                    printf("failed deletion\n");
                    status[g] = 0;
                } else {
                    printf("succeeded deletion\n");
                    cache[key[g]] = 0;
                    status[g] = 1;
                    size--;
                    if(size<0){
                        size = 0;
                    }
                }
/*
                printf("done!\n");
*/
                break;
            default:
                printf("bad operation\n!");
                exit(1);
        }
        load[g] = size;
        max_load = (load[g] > max_load) ? load[g] : max_load;
    }
    
    printf("feedback\n");
    for(g=0; g<num_operations; g++){
        printf("%d %d %d --- %d\n", operation[g], key[g], status[g], load[g]);
    }
    printf("num_operations=%d  max_key=%d  capacity=%d  max_load=%d\n", 
            num_operations, max_key, capacity, max_load);
    
    #ifdef WRITE_FILE
        char fname[200];
        sprintf(fname, "operation_sequence_with_feedback");
        fp = fopen(fname,"w");
        fprintf(fp, "0\n");
        fprintf(fp, "%d\n", num_operations);
        fprintf(fp, "%d\n", max_key);
        fprintf(fp, "%d\n", capacity);
        fprintf(fp, "%d\n", max_load);
        for(g=0; g<num_operations; g++){
            fprintf(fp, "%d %d %d\n", operation[g], key[g], status[g]);
        }
        fclose(fp);
    #endif
}

int main(int argc, char** argv) {

    #ifdef RUN_TEST
        printf("%%TEST_STARTED%% (generate_artificial_operation_sequence_feedback\n");
        test1();
        printf("%%TEST_FINISHED%% (generate_artificial_operation_sequence_feedback)\n");
    #endif
    return (EXIT_SUCCESS);
}
