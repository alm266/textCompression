//child process code to be exec'd

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	char* fileName = argv[1];
	int sizePart = atoi(argv[2]);
	int orderNum = atoi(argv[3]);
	int totalOffset = atoi(argv[4]);
	printf("WORKER BEGAN\n");
	
	FILE *fp;
	fp = fopen(fileName, "r");
	
	fseek(fp, totalOffset, SEEK_SET);
	
	//int sizePart = strsizePart(argv[1]);
	//printf("sizePart: %d\n", sizePart);
	
	if(sizePart < 3){
		printf("NEED TO WRITE AS IS TO FILE\n");	//change to writing to file
		return 0;
	}
	
	char input[sizePart];
	fgets(input, sizePart, fp);
	//strcpy(input, argv[1]);
	
	char output[sizePart];
	char arrtmp[sizePart];
	
	char tmp;
	int num = 1;
	
	int i;
	for(i=0;i < sizePart ;i++)
	{
		if(input[i] == input[i+1] && input[i] == input[i+2])
		{
			tmp = input[i];
			num=3;
	
			for(i=i+2;i< sizePart;i++)
			{
				
				if(input[i] == input[i+1])
					num++;
				else
				{
					memset(&arrtmp[0], 0, sizePart);
					snprintf(arrtmp, sizePart, "%d%c", num, tmp);
					strcat(output, arrtmp);
					break;
				}
			}
			
		}
		else
		{
			tmp = input[i];
			memset(&arrtmp[0], 0, sizePart);
			snprintf(arrtmp, sizePart, "%c", tmp);
			strcat(output, arrtmp);
		}
	}
	printf("Look at the output: %s\n", output);
	//success status is returned
	exit(EXIT_SUCCESS);	//when would this process fail though?
	return 0;
}
