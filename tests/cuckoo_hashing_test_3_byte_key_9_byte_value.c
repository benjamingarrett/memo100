/*
 * File:   cuckoo_hashing_test_3_byte_key_9_byte_value.c
 * Author: benjamin
 *
 * Created on Aug 12, 2015, 10:06:29 PM
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*
#define RUN_TEST  
*/
/*
#define SHOW_PROGRESS  
*/

void test1() {
    
    uint64_t TABLE_SIZE = 64;
    uint64_t NON_VALUE = -1;
    uint64_t NON_POSITION = -1;
    uint64_t KEY__LENGTH = 3;
    uint64_t VALUE__LENGTH = 9;
    uint64_t num_values = 32;
    int32_t g, h, j;
    unsigned char * key, * k;
    int64_t successes, failures, trials;
    struct nine_byte_value {
        unsigned char byte[9];
    };
    struct nine_byte_value * value;
    unsigned char t, * vp;
    
    #ifdef SHOW_PROGRESS
        printf("cuckoo_hashing_test_3_byte_key_9_byte_value test 1\n");
    #endif
    key = (unsigned char *)calloc(num_values, sizeof(KEY__LENGTH));
    value = (struct nine_byte_value *)calloc(num_values, sizeof(struct nine_byte_value));
    
    t = 1;
    for(g=0; g<num_values; g++){
        h = g+10000000;
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
        for(j=0; j<VALUE__LENGTH; j++){
            value[g].byte[j] = t++;
        }
    }
    
    #ifdef SHOW_PROGRESS
        printf("look at all keys and values:\n");
        for(g=0; g<num_values; g++){
            printf("%x %x %x - %x %x %x %x %x %x %x %x %x\n",
                    key[g*KEY__LENGTH+2],
                    key[g*KEY__LENGTH+1],
                    key[g*KEY__LENGTH],
                    value[g].byte[0],
                    value[g].byte[1],
                    value[g].byte[2],
                    value[g].byte[3],
                    value[g].byte[4],
                    value[g].byte[5],
                    value[g].byte[6],
                    value[g].byte[7],
                    value[g].byte[8]
                    );
        }
    #endif
    
    initialize_memoization(
            "MurmurHash32", TABLE_SIZE, &NON_VALUE, &NON_POSITION,
            KEY__LENGTH, VALUE__LENGTH, "cuckoo", "hashing", 0, 0);
    for(g=0; g<num_values; g++){
        vp = (struct nine_byte_value *)cache_write(key+g*KEY__LENGTH);
        for(j=0; j<VALUE__LENGTH; j++){
            *(vp+j) = value[g].byte[j];
        }
        #ifdef SHOW_PROGRESS
            printf("%d: %x %x %x %x - %x %x %x %x %x %x %x %x %x inserted\n",
                    key[g*KEY__LENGTH+3], key[g*KEY__LENGTH+2],
                    key[g*KEY__LENGTH+1], key[g*KEY__LENGTH],
                    value[g].byte[0],
                    value[g].byte[1],
                    value[g].byte[2],
                    value[g].byte[3],
                    value[g].byte[4],
                    value[g].byte[5],
                    value[g].byte[6],
                    value[g].byte[7],
                    value[g].byte[8]
                    );
        #endif
    }
    #ifdef SHOW_PROGRESS
        printf("Retrieving values...\n");
    #endif
    successes = failures = trials = 0;
    for(g=0; g<num_values; g++){
        vp = (int64_t *)cache_read(key+g*KEY__LENGTH);
        for(j=0; j<VALUE__LENGTH; j++){
            if( *(vp+j) != value[g].byte[j] )
                goto failure;
        }
        successes++;
        failure:
        trials++;
    }
    
    if(successes==trials){
        printf("cuckoo hashing test 3 byte key 9 byte value - PASSED!\n");
    } else {
        printf("cuckoo hashing test 3 byte key 9 byte value - FAILED! (%d failures)", trials - successes);
    }
}

int main(int argc, char** argv) {
    
    #ifdef RUN_TEST
        printf("%%TEST_STARTED%% test1 (cuckoo_hashing_test_3_byte_key_9_byte_value)\n");
        test1();
        printf("%%TEST_FINISHED%% time=0 test1 (cuckoo_hashing_test_3_byte_key_9_byte_value) \n");
    #endif
    return (EXIT_SUCCESS);
}
