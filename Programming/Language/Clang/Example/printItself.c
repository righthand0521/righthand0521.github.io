// print itself
#include <stdio.h>
int main(int argc, char **argv)
{
	char str[] = "// print itself%c#include <stdio.h>%cint main(int argc, char **argv)%c{%c%cchar str[] = %c%s%c%c%c%cprintf(str,10,10,10,10,9,34,str,34,59,10,9,10,9,10,10,10);%c%creturn 0;%c}%c%c";
	printf(str,10,10,10,10,9,34,str,34,59,10,9,10,9,10,10,10);
	return 0;
}

