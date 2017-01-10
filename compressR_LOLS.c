//Needs more code
//Ask and you shall receive..

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	//need to check if we have permission to access file
	FILE * fp;
	fp = fopen(argv[1], "r");
	
	//get size of text in file
	size_t pos = ftell(fp);
	fseek(fp, 0, SEEK_END);
	size_t fsize = ftell(fp);
	fseek(fp, pos, SEEK_SET);
	
	
	int numParts = atoi(argv[2]);
	
	//is user asking for more parts than there are characters?
	if(numParts > fsize){
		printf("ERROR: Too many parts requested\n");
		return -1;
	}
	
	//find size of parts
	
	int sizePart = fsize/numParts;
	int offset = fsize % numParts;
	
	//here we should store the indeces to start and how much to do for each process
	//fork() "parts" number of parts
	pid_t pids[numParts];
	int i;
	for(i=0; i<numParts; i++)
	{
		//first part size is largest
		//includes any leftover characters
		pids[i] = fork();
		
		if(pids[i] == 0){
			printf("PROCESS %d:\n\t", i);
			
			char sp[32];
			sprintf(sp, "%d", sizePart);
			
			char is[32];
			sprintf(is, "%d", i);
			
			
			
			if(i == 0){		//if its the first part, increment by offset
				char off[32];
				sprintf(off, "%d", 0);
				printf("Look at off: %s\n", off);
				
				char* command = "./workerProc nmn.txt 2 4 4";
				execl("/bin/sh", "/bin/sh", "-c", command, NULL);
				//continue; 	<---not necessary
			}
			char off[32];
			sprintf(off, "%d", ((i * sizePart) + offset));
			printf("Look at off: %s\n", off);
			
			char* command = "./workerProc nmn.txt 2 4 4";
			execl("/bin/sh", "/bin/sh", "-c", command, NULL);
			//char *my_args[64] = {"/compressR_worker_LOLS.c", fp, sizePart + offset, i};
			//execl("/compressR_worker_LOLS.c", fp, sizePart + offset, i);
			//execv("/compressR_worker_LOLS.c", my_args);
		}
		else{
			continue;
		}
	}
	
	//now we need to wait for each child process to finish working
	for(i=0; i<numParts; i++){
		int status;
		while ((pids[i] = wait(&status)) > 0)
		{
			printf("Exit status of %d was %d (%s)\n", (int)pids[i], status,
				   (status > 0) ? "accept" : "reject");
		}
	}
	return EXIT_SUCCESS;
}

/*char *intToString(int num){
	char parameter[32];
	sprintf(parameter, "%d", num);
	
	return (char *)parameter;
}*/
