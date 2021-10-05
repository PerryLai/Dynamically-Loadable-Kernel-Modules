#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define init_module(module_image, len, param_values) syscall(__NR_init_module, module_image, len, param_values)
#define finit_module(fd, param_values, flags) syscall(__NR_finit_module, fd, param_values, flags)
#define delete_module(name, flags) syscall(__NR_delete_module, name, flags)

long addition (int input1, int input2, char* sum);
long substraction (int input1, int input2, char* sub);
long multiplication (int input1, int input2, char* mul);

// StudentID = 0616087

int main() {
	char operator;
	char *operation;

	int input1=0;
	int input2=0;
	long result = 0;

	while(1)
	{
		input1=0;
		input2=0;
		result = 0;

		printf("=======================\n");
		
		printf("Enter operation [sum - sub - mul - exit]: ");
		scanf("%s",operation);

		if(strcmp(operation,"exit")==0){
			break;
		}

		printf("Enter two operands (space separated): ");
		scanf("%d %d", &input1, &input2);
		
		if(strcmp(operation,"sum")==0){
			result = addition (input1, input2, operation);
			printf("Operation: [%s] - Operands [%d %d] - Result:[%ld]\n",operation, input1, input2, result);
		}else if(strcmp(operation,"sub")==0){
			result = substraction (input1, input2, operation);
			printf("Operation: [%s] - Operands [%d %d] - Result:[%ld]\n",operation, input1, input2, result);
		}else if(strcmp(operation,"mul")==0){
			result = multiplication (input1, input2, operation);
			printf("Operation: [%s] - Operands [%d %d] - Result:[%ld]\n",operation, input1, input2, result);
		}else{
			printf("Invalid option\n");
		}
	}
	return 0;
}

long addition (int input1, int input2, char* sum)
{
	long result = 0;

	const char *moduleName = "calculatorModule.ko";
	const char *moduleNameNoExtension = "calculatorModule";

	int fd, use_finit;
	size_t image_size;
	struct stat st;
	void *image;

	char paramsNew[500];
	sprintf(paramsNew, "operationParam=%s firstParam=%d secondParam=%d", sum, input1, input2 );

	fd = open(moduleName, O_RDONLY);
	fstat(fd, &st);
	image_size = st.st_size;
	image = malloc(image_size);
	read(fd, image, image_size);

	if (init_module(image, image_size, paramsNew) != 0) {
		perror("init_module");
		return EXIT_FAILURE;
	}

	FILE *fPtr;
	fPtr = fopen("/sys/module/calculatorModule/parameters/resultParam", "r");
	if (!fPtr) {
		printf("open failed...\n");
		exit(1);
	}
	fscanf(fPtr, "%ld", &result);
	fclose(fPtr);


	if (delete_module(moduleNameNoExtension, O_NONBLOCK) != 0) {
        	perror("delete_module");
        	return EXIT_FAILURE;
	}

	close(fd);
	free(image);
	
	return result;
}

long substraction (int input1, int input2, char* sub)
{
	long result = 0;

	const char *moduleName = "calculatorModule.ko";
	const char *moduleNameNoExtension = "calculatorModule";

	int fd, use_finit;
	size_t image_size;
	struct stat st;
	void *image;

	char paramsNew[500];
	sprintf(paramsNew, "operationParam=%s firstParam=%d secondParam=%d", sub, input1, input2 );

	fd = open(moduleName, O_RDONLY);
	fstat(fd, &st);
	image_size = st.st_size;
	image = malloc(image_size);
	read(fd, image, image_size);

	if (init_module(image, image_size, paramsNew) != 0) {
		perror("init_module");
		return EXIT_FAILURE;
	}

	FILE *fPtr;
	fPtr = fopen("/sys/module/calculatorModule/parameters/resultParam", "r");
	if (!fPtr) {
		printf("open failed...\n");
		exit(1);
	}
	fscanf(fPtr, "%ld", &result);
	fclose(fPtr);


	if (delete_module(moduleNameNoExtension, O_NONBLOCK) != 0) {
        	perror("delete_module");
        	return EXIT_FAILURE;
	}

	close(fd);
	free(image);
	
	return result;
}

long multiplication (int input1, int input2, char* mul)
{
	long result = 0;

	const char *moduleName = "calculatorModule.ko";
	const char *moduleNameNoExtension = "calculatorModule";

	int fd, use_finit;
	size_t image_size;
	struct stat st;
	void *image;

	char paramsNew[500];
	sprintf(paramsNew, "operationParam=%s firstParam=%d secondParam=%d", mul, input1, input2 );

	fd = open(moduleName, O_RDONLY);
	fstat(fd, &st);
	image_size = st.st_size;
	image = malloc(image_size);
	read(fd, image, image_size);

	if (init_module(image, image_size, paramsNew) != 0) {
		perror("init_module");
		return EXIT_FAILURE;
	}

	FILE *fPtr;
	fPtr = fopen("/sys/module/calculatorModule/parameters/resultParam", "r");
	if (!fPtr) {
		printf("open failed...\n");
		exit(1);
	}
	fscanf(fPtr, "%ld", &result);
	fclose(fPtr);


	if (delete_module(moduleNameNoExtension, O_NONBLOCK) != 0) {
        	perror("delete_module");
        	return EXIT_FAILURE;
	}

	close(fd);
	free(image);
	
	return result;
}