#include <stdio.h>
#include <stdlib.h>

void function() {	
	int buffer[5];
	buffer[0] = 12;

	buffer[5] = 13;
	int *ret;
	ret = &buffer[0] + 12;
	*ret += 4;
}

int main(int argc, char* argv)
{	
	printf("%ld\n", sizeof(int));
	int temp;
	temp = 3;
	function();
	temp = 4;
	printf("%d\n", temp);
}
