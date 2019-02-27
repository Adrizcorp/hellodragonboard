
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>


typedef struct
{
	unsigned int cfg;            /*place holder for configuration register*/
	unsigned int in_out;				 /*place holder for IO register*/
}db_gpio_type_s;

int abort_program = 0;
#define GPIO_n 120
/*GPIOn physical address = 0x01000004 + (0x1000 * n); ref: e peripherals programming guide*/
unsigned int GPIO_120_CFG_ADDR = 0x01000000 + (0x1000 * GPIO_n);
unsigned int GPIO_120_IO_ADDR = 0x01000004 + (0x1000 * GPIO_n);


int main(int argc, char *argv[])
{

	db_gpio_type_s *gpio_120;
	int fd_mem;

	fd_mem = open("/dev/mem", O_RDWR | O_SYNC);

	if (fd_mem < 0)
	{
		printf("Failed to open /dev/mem. Aborting\n");
	}

	gpio_120 = (db_gpio_type_s *)(mmap(0, sizeof(db_gpio_type_s), PROT_READ | PROT_WRITE, MAP_SHARED, fd_mem, GPIO_120_CFG_ADDR));

	if (gpio_120 == (void *)-1)
	{
		printf("Failed to map GPIO address. Aborting\n");
		close(fd_mem);
	}
    
	printf("Hello DragonBoard... Blinking Led\n");
	int counter=10;
    while(counter>0){
		gpio_120->in_out = gpio_120->in_out | 0x02;
		usleep(500000);
		gpio_120->in_out = gpio_120->in_out & ~0x02;
		usleep(500000);
		counter--;
	}
	
	/*clean up and exit*/
	gpio_120->in_out = gpio_120->in_out & ~0x02;

	if (munmap(gpio_120, sizeof(int)) == -1)
	{
		printf("Failed to unmap GPIO address. Aborting\n");
		close(fd_mem);
	}

	printf("Contents of physical address 0x%X is 0x%X\n", GPIO_120_IO_ADDR, gpio_120->in_out);

	close (fd_mem);
	printf("\nProgram exiting\n");
	return 0;
}

