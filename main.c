#include <stdio.h>
#include "uart/uart.h"

int main()
{
    int a,b,c;

    uart_init();
    while(1){
	printf("\nInput 2 integer: ");
	scanf("%d%d",&a,&b);
	printf("The sum of the 2 integer is: %d\n",c);
    }
    return 0;
}
