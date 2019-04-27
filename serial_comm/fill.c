#include <stdio.h>
#include <stdlib.h>

int mask = 64;
int main(int argc, char const *argv[])
{
	int index = 1;
	FILE *fp;
	
	while(1){
		int ans = 0, temp = 0;
		char write_f[3];
		fp = fopen("sakthi.txt", "a+");
		printf("Question %d:\n", index);
		printf("A: ");
		scanf("%d", &temp);
		ans |= (temp << 3);
		printf("B: ");
		scanf("%d", &temp);
		ans |= (temp << 2);
		printf("C: ");
		scanf("%d", &temp);
		ans |= (temp << 1);
		printf("D: ");
		scanf("%d", &temp);
		ans |= (temp << 0);
		ans |= mask;
		printf("Ans filled: %d\n", ans);
		index++; 
		fprintf(fp, "%d\n", ans);
		fclose(fp);
	}
	return 0;
}