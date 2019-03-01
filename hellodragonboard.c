
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>

#define LED_GPIO 120
#define NUM_BLINKS 10
#define LED_CFG_BASE 0x01000000 + (0x1000 * LED_GPIO)
#define LED_STATUS_OFFSET 0x4

int main(int argc, char** argv){
	int n_blinks;
	int fd_mem;
	void *leds_base;
	unsigned int *led_cfg;
	unsigned int *led_status;
	
	//getting argument
	if(argc>1){
		sscanf(argv[1],"%d",&n_blinks);
	}else{
		return 0;
	}
	//open mem to access physical mem
	fd_mem = open("/dev/mem", O_RDWR | O_SYNC);
	//aiming to the physical address with offset
	leds_base = mmap(NULL, 32, PROT_READ | PROT_WRITE, MAP_SHARED, fd_mem, LED_CFG_BASE);
	//set base of led for configuration
	led_cfg=leds_base;
	//set base of led for status
	led_status=leds_base+LED_STATUS_OFFSET;
	
	printf("Hello\n");
	printf("Blink times=%d\n",n_blinks);
	
	//Enable output enable.
	*led_cfg|=(1<<9);
	//Blink on board LED
	while(n_blinks>0){
		* led_status=* led_status ^ 0x02;//toggle led
		usleep(100000);
		n_blinks--;
	}
	
	
	
	return 0;
}

