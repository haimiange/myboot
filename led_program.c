#include "led/led.h"
#include "sleep/sleep.h"

int main()
{
    int i = 0;
    
    led_init();
    while(1){
	for(i = 0;i < 4;i++){
	    led_on(i);
	    sleep(100);
	}
	for(i = 0;i < 4;i++){
	    led_off(i);
	    sleep(100);
	}
    }
    return 0;
}
