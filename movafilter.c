#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

extern void filter4(float alpha, float beta, int s, int *start, int length, int *dest) asm("filter");
 
 
 /**
 A function that mimics the functionality of the asm program to cross validate the results when testing.
  **/
void cFilter4(float alpha, float beta, int s, int *start, int length, int *dest){
	float lastGk =  s; 
	if(alpha+beta == 0){
		for(int i = 0;i<length;i++){
			dest[i] = 1;
		}
		return;
	}
	for(int i = 0;i<length;i++){
		lastGk = (alpha*lastGk+beta*start[i])/(alpha+beta);
		
		// Mimics the rounding behavior of the FPU
		float cutLastGk = (float) (int) lastGk;
		if(lastGk == cutLastGk+0.5){
			if((int)cutLastGk%2 == 0){
				dest[i] = (int) cutLastGk;
			}else{
				dest[i] = (int) cutLastGk+1;
			}
			
		}else if(lastGk < cutLastGk+0.5){
			dest[i] =  (int) cutLastGk;
		}else{
			dest[i] =  (int) cutLastGk+1;
		}
	}
 }
 
 /** 
	Assert replacement for testing purposes. Compares the output of the 
	asm filter and the cross validation c function.
	measures the accuracy of the filter method while also providing 
	details about how long the calculations of each functions took.
 **/
 
 void validate(int *testData, int length, float alpha, float beta, int s){
	 
	struct timespec start, end;
	int filteredValues[length];
	int validationValues[length];
	int *start_ptr = &testData[0];
	int *dest_ptr = &filteredValues[0];
	int *val_ptr = &validationValues[0];
	
	printf("Input Values:\n");
	for(int i = 0;i<length;i++){
		printf("%d ",testData[i]);
	}
	
	
	// Call filter in asm and measure the time it took to complete
	clock_gettime(CLOCK_MONOTONIC, &start);
	filter4(alpha,beta,s,start_ptr,length,dest_ptr); 
	clock_gettime(CLOCK_MONOTONIC, &end);
	
	
	// Print the results along with timestamps
	printf("\n");
	printf("\nFiltered Values %ld ms:\n",(end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000);
	for(int i = 0;i<length;i++){
		printf("%d ",filteredValues[i]);
	}
	
	
	// Call filter in c and measure the time it took to complete
	clock_gettime(CLOCK_MONOTONIC, &start);
	cFilter4(alpha,beta,s,start_ptr,length,val_ptr);
	clock_gettime(CLOCK_MONOTONIC, &end);
	
	// Print the results along with timestamps
	printf("\n");
	printf("\nValidation Values %ld ms:\n",(end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000);
	for(int i = 0;i<length;i++){
		printf("%d ",validationValues[i]);
	}
	printf("\n");
	
	
	// Check the filtered values against the validation function
	int counter = length;
	for(int i = 0;i<length;i++){
		if(validationValues[i] != filteredValues[i]){
			printf("\nUnmatching Values at position:%d filter: %d validation: %d\n\n",i,filteredValues[i],validationValues[i]);
			counter--;
			//return 0;
		}
	}
	printf("\n %d of %d Values match!:\n\n\n",counter,length);

 }
 
int main(int argc, char** argv) { 

	 
	if(argc == 2 && !strcmp(argv[1], "runtest")){
		//Default behavior if no argument is specified
		
		// Note: Small ifferences between the filtered values and the validation are not necessarily a sign of the filter malfunctioning.
		// They could also be caused by differences in the handling of floating point between the c standard library and the assembler routine.
		
		// testsignal sets 
		int testData1[] = {400,10,20,30,40,50,60,70,80,90,80,70,60,50,40}; 
		int testData2[] = {2705,2975,3406,4472,2952,2592,2429,2450,2335,2477};
		
		
		int randomSetLength = 200;
		int maxIntRandom = 200000;
		
		float alpha1 = 0.3;
		float alpha2 = -0.4;
		float alpha3 = 0.6;
		
		float beta1 = 0.4;
		float beta2 = 0.7;
		float beta3 = 0.4;
		
		int s1 = 400;
		int s2 = 3555;
		int s3 = 10000;
		
		
		// randomised testset
		int testData3[randomSetLength];
		srand(time(NULL));
		for(int i = 0;i<sizeof(testData3)/4;i++){
			testData3[i] = rand() % (maxIntRandom + 1 - 0)+0;
		}
		
		
		int testData4[] = {};

		// regular functionality , constant sets
		validate(testData1,sizeof(testData1)/4,alpha1,beta1,s1);
		validate(testData2,sizeof(testData2)/4,alpha2,beta2,s2);
		
		// edgecase: alpha+beta = 0
		validate(testData1,sizeof(testData1)/4,alpha1,(-1.0)*alpha1,s1);
		
		// edgecase: empty input
		validate(testData4,sizeof(testData4)/4,1.0,1.0,333);
		
		// regular functionality , randomized sets
		validate(testData3,sizeof(testData3)/4,alpha3,beta3,s3);
		
		printf("\n\n Test done!");
		getchar();
	
	}else if (argc == 6){
		
		
		FILE *fp = fopen(argv[4], "r");
		int lines = 0;
		

		while(!feof(fp)){
			char ch = fgetc(fp);
			if(ch == '\n'){
				lines++;
			}
		}

		
		rewind(fp);
		
		int unfilteredValues[lines];
		int filteredValues[lines];
		
		for (int i = 0; i < lines; i++){
		
			fscanf(fp, "%d\n", &unfilteredValues[i]);

		}

				
		fclose(fp);
		
		int *start_ptr = &unfilteredValues[0];
		int *dest_ptr = &filteredValues[0];
		
		filter4( atof(argv[1]), atof(argv[2]), atoi(argv[3]), start_ptr, lines, dest_ptr);
		
		FILE *fpout = fopen(argv[5], "w");
		
		for (int i = 0; i < lines; i++){
			fprintf(fpout, "%d\n", filteredValues[i]);
		}
		

		fclose(fpout);
		
	
	}else{
		printf("Usage: movafilter [float alpha] [float beta] [int starting value] [source filepath] [output filepath]\n");
		printf("To run the testcases: movafilter runtest\n");
	}
	
 }
 
 
 

 
