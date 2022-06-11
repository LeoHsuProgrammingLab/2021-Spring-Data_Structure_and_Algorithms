#include <stdio.h>
int main()
{
	int a, b;
	//Finally get
	scanf("%d%d", &a, &b);
	printf("%d\n", a + b);

	const char *here = "a";
	char *there;
	there = "j";
	here = there;
	printf("%c\n", *here);

		return 0;
}
