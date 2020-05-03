#include "defines.h"

#define MAX_SIZE_TASK_1 16

#define ARRAY_SIZE_TASK_2 6

int main(void){
	
//TASK 1	
	uint8_t A[MAX_SIZE_TASK_1] = "Hello world";
	uint8_t B[MAX_SIZE_TASK_1];
	
	StrCopyRev(A, B);
	
	
//TASK 2
	uint32_t unsig_data[ARRAY_SIZE_TASK_2] = {0xffffffff, 5, 0xfffffffD, 0x7ffffffd, 0x7ffffffd, 0x7fffffff};
	volatile uint64_t unsig_res = SumOfUnsigned(unsig_data, ARRAY_SIZE_TASK_2);	


	int32_t sig_data[ARRAY_SIZE_TASK_2] = {0x7fffffff, 0x7fffffff, 0x7ffffffd, -41, 0x7fffffff, -92};
	volatile int64_t sig_res = SumOfSigned(sig_data, ARRAY_SIZE_TASK_2);	

	
	while(1);
	
}
