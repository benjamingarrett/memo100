/*
 * File:   generate_operation_sequence_without_feedback.c
 * Author: benjamin
 *
 * Created on Aug 25, 2015, 12:22:19 AM
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../random/random.h"


#define RUN_TEST  


void test1(int num_operations, int max_key) {
    
    uint64_t g, operation, key;
    FILE * fp;
    char fname[200];
    
    printf("generate_operation_sequence_without_feedback\n");
    sprintf(fname, "../misc_phd/input/operation_sequences/without_feedback/%d/operation_sequence_without_feedback-%d-%d", 
            num_operations, num_operations, max_key);
    fp = fopen(fname,"w");
    fprintf(fp, "%d\n", num_operations);
    fprintf(fp, "%d\n", max_key);
    for(g=0; g<num_operations; g++){
        operation = rand_in_range(0,3);
        key = rand_in_range(1,max_key);
        fprintf(fp, "%d %d\n", operation, key);
    }
    fclose(fp);
}

int main(int argc, char** argv) {

    #ifdef RUN_TEST
        printf("%%TEST_STARTED%% test1 (generate_operation_sequence_without_feedback)\n");
        test1(100000,40000);
        test1(100000,80000);
        printf("%%TEST_FINISHED%% time=0 test1 (generate_operation_sequence_without_feedback) \n");
    #endif
    return (EXIT_SUCCESS);
}
