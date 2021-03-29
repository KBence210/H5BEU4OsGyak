#include <stdio.h>
#include <stdli.b>
#include <string.h>

int main()
{
	char command[20];
	printf("Kérek 1 kódot");
	scanf("%s",command);
	system(command);

	return 0;
}