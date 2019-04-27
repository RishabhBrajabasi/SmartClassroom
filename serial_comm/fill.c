#include <stdio.h>
#include <stdlib.h>
#include <signal.h> 
int mask = 64;

  
/* Signal Handler for SIGINT */
void sigintHandler(int sig_num) 
{ 
    /* Reset handler to catch SIGINT next time. 
       Refer http://en.cppreference.com/w/c/program/signal */
    signal(SIGINT, sigintHandler); 
    printf("\n Answers Filled and You are ready to roll the quiz \n"); 
    exit(0);
} 
int main(int argc, char const *argv[])
{
	int index = 1;
	FILE *fp;
    signal(SIGINT, sigintHandler); 
    printf("Please Enter 1 or 0 for each option and cntr + c to terminate\n");
	while(1){
		int ans = 0, temp = 0;
		char write_f[3];
		fp = fopen("answers.csv", "a+");
		printf("Question %d:\n", index);

		printf("A: ");
		A:
		scanf("%d", &temp);
		if(temp != 0 && temp != 1) {
			printf("Incorrect Entry Please try again!!!\n");
			goto A;
		}
		ans |= (temp << 3);
		printf("B: ");
		B:
		scanf("%d", &temp);
		if(temp != 0 && temp != 1) {
			printf("Incorrect Entry Please try again!!!\n");
			goto B;
		}
		ans |= (temp << 2);
		printf("C: ");
		C:
		scanf("%d", &temp);
		if(temp != 0 && temp != 1) {
			printf("Incorrect Entry Please try again!!!\n");
			goto C;
		}
		ans |= (temp << 1);
		printf("D: ");
		D:
		scanf("%d", &temp);
		if(temp != 0 && temp != 1) {
			printf("Incorrect Entry Please try again!!!\n");
			goto D;
		}
		ans |= (temp << 0);
		ans |= mask;
		printf("Ans filled: %d\n", ans);
		index++; 
		fprintf(fp, "%d\n", ans);
		fclose(fp);
	}
	return 0;
}