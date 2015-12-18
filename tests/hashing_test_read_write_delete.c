/*
 * File:   cuckoo_hashing_test_read_write_delete.c
 * Author: benjamin
 *
 * Created on Aug 24, 2015, 9:41:10 PM
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*
#define RUN_TEST  
*/
#define VIEW_PROGRESS  
#define READ 0
#define WRITE 1
#define DELETE 2
#define FAILURE 0
#define SUCCESS 1

uint64_t NON_VALUE = -1;
uint64_t NON_POSITION = -1;

void test1() {
    
    uint64_t g, h, * key, num_operations, max_key, capacity, max_load, num_trials, num_anomalies;
    int * operation, * status, * result, type;
    FILE * fp;
    unsigned char * k;
    unsigned char KEY[4];
    uint64_t * vp, val;
    
    printf("hashing_test_read_write_delete\n");
    
    /* read operations */
    fp = fopen("../operation_sequences/operation_sequence_with_feedback","r");
    fscanf(fp, "%d\n", &type);
    if(type == 0){
        printf("Artificial feedback detected\n");
    }
    fscanf(fp, "%d\n", &num_operations);
    fscanf(fp, "%d\n", &max_key);
    fscanf(fp, "%d\n", &capacity);
    fscanf(fp, "%d\n", &max_load);
    operation = calloc(num_operations, sizeof(int));
    key = calloc(num_operations, sizeof(uint64_t));
    status = calloc(num_operations, sizeof(int));
    result = calloc(num_operations, sizeof(int));
    for(g=0; g<num_operations; g++){
        fscanf(fp, "%d %d %d\n", &operation[g], &key[g], &status[g]);
    }
    fclose(fp);
    
/*
    for(g=0; g<num_operations; g++){
        printf("%d %d %d %d\n", g, operation[g], key[g], status[g]);
    }
*/
    
    /* initialize cache */
    
/*
    initialize_memoization("MurmurHash32", capacity, &NON_VALUE, 
            &NON_POSITION, 4, 8, "linear_probe_with_deletions", "hashing", 0, 2);
*/
    
    initialize_memoization("MurmurHash32", capacity, &NON_VALUE, 
            &NON_POSITION, 4, 8, "cuckoo", "hashing", 0, 2);
    
    #ifdef VIEW_PROGRESS
        printf("Starting trials\n");
    #endif

    /* perform operations, recording result */
    for(g=0; g<num_operations; g++){
        k = (unsigned char *)&key[g];
        for(h=0; h<4; h++){
            KEY[h] = *(k+h);
        }
        
/*
        #ifdef VIEW_PROGRESS
            printf("-------hashing test: g=%d  operation=%d  key=%d  status=%d-------\n", 
                    g, operation[g], key[g], status[g]);

            
            view_hashtable();
            

        #endif
*/
        
        switch(operation[g]){
            case READ:
                vp = (uint64_t *)cache_read(KEY);
                val = *vp;
                if(val == NON_VALUE){
                    result[g] = FAILURE;
                } else {
                    result[g] = SUCCESS;
                }
                break;
            case WRITE:
                vp = (uint64_t *)cache_read(KEY);
                val = *vp;
                if(val == NON_VALUE){
                    vp = (uint64_t *)cache_write(KEY);
                    if( *vp != NON_POSITION ){
                        *vp = key[g];
                        result[g] = SUCCESS;
                    } else {
                        result[g] = FAILURE;
                    }
                } else {
                    result[g] = FAILURE;
                }
                break;
            case DELETE:
                vp = (uint64_t *)cache_read(KEY);
                val = *vp;
                if(val == NON_VALUE){
                    result[g] = FAILURE;
                } else {
                    if( delete(KEY) == 0 ){
                        result[g] = SUCCESS;
                    } else {
                        result[g] = FAILURE;
                    }
                }
                break;
            default:
                printf("bad operation: %d %d\n", g, operation[g]);
                exit(1);
                break;
        }
        
        #ifdef VIEW_PROGRESS
            if(status[g] != result[g]){
                printf("Anomaly found after operation %d\n", g);
            }
        #endif
    }
    
    num_anomalies = num_trials = 0;
    for(g=0; g<num_operations; g++){
/*
        printf("%d %d %d\n", g, status[g], result[g]);
*/
        if(status[g]!=result[g]){
            num_anomalies++;
        }
        num_trials++;
    }
    printf("trials: %d  anomalies: %d\n", num_trials, num_anomalies);
}

int main(int argc, char** argv) {

    #ifdef RUN_TEST
        printf("%%TEST_STARTED%% (hashing_test_read_write_delete)\n");
        test1();
        printf("%%TEST_FINISHED%% (hashing_test_read_write_delete)\n");
    #endif
    return (EXIT_SUCCESS);
}
