/*
 * File:   linear_probe_test_fill_table_32.c
 * Author: benjamin
 *
 * Created on Aug 11, 2015, 8:28:30 PM
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*
#define RUN_TEST  
#define SHOW_PROGRESS  
*/

void test1() {
    
    uint64_t TABLE_SIZE = 32;
    uint64_t NON_VALUE = -1;
    uint64_t NON_POSITION = -1;
    uint64_t KEY__LENGTH = 4;
    uint64_t VALUE__LENGTH = 8;
    uint64_t num_values = 32;
    int32_t g, h, j;
    unsigned char * key, * k;
    int64_t * value, * vp, val;
    int64_t successes, failures, trials;
    
    #ifdef SHOW_PROGRESS
        printf("linear_probe_test_fill_table test 1\n");
    #endif
    key = (unsigned char *)calloc(num_values, sizeof(KEY__LENGTH));
    value = (int64_t *)calloc(num_values, sizeof(int64_t));
    
    for(g=0; g<num_values; g++){
        h = g+1000000000;
        k = (unsigned char *)&h;
        for(j=0; j<KEY__LENGTH; j++){
/*
            printf("%x ", *(k + j));
*/
            key[g*KEY__LENGTH+j] = *(k + j);
        }
/*
        printf("\n");
*/
        value[g] = h;
    }
    
    #ifdef SHOW_PROGRESS
        printf("look at all keys and values:\n");
        for(g=0; g<num_values; g++){
            printf("%x %x %x %x - %d\n",
                    key[g*KEY__LENGTH+3],
                    key[g*KEY__LENGTH+2],
                    key[g*KEY__LENGTH+1],
                    key[g*KEY__LENGTH],
                    value[g]
                    );
        }
    #endif
    
    initialize_memoization(
            "MurmurHash32", TABLE_SIZE, &NON_VALUE, &NON_POSITION,
            KEY__LENGTH, VALUE__LENGTH, "linear_probe", "hashing", 0, 0);
    for(g=0; g<num_values; g++){
        vp = (int64_t *)cache_write(key+g*KEY__LENGTH);
        *vp = value[g];
        #ifdef SHOW_PROGRESS
            printf("%d: %x %x %x %x - %d inserted\n",
                    key[g*KEY__LENGTH+3], key[g*KEY__LENGTH+2],
                    key[g*KEY__LENGTH+1], key[g*KEY__LENGTH],
                    value[g]);
        #endif
    }
    #ifdef SHOW_PROGRESS
        printf("Retrieving values...\n");
    #endif
    successes = failures = trials = 0;
    for(g=0; g<num_values; g++){
        trials++;
        vp = (int64_t *)cache_read(key+g*KEY__LENGTH);
        val = *vp;
        if(val==value[g]){
            successes++;
        } else {
            failures++;
        }
    }
    
    if(successes==trials){
        printf("linear probe test fill table - PASSED!\n");
    } else {
        printf("linear probe test fill table - FAILED! (%d failures)", failures);
    }
}

int main(int argc, char** argv) {

    #ifdef RUN_TEST
        printf("%%TEST_STARTED%% test1 (linear_probe_test_fill_table_32)\n");
        test1();
        printf("%%TEST_FINISHED%% time=0 test1 (linear_probe_test_fill_table_32) \n");
    #endif
    return (EXIT_SUCCESS);
}
