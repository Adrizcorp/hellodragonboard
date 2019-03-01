# hellodragonboard from scratch using Docker

the docker container at hand prints a message on console
"Hello DragonBoard... Blinking Led "
and blinks LED 10 times

## To build the source code for the binary file
gcc -static hellodragonboard.c -o hellodragonboard 

## To pull it on docker:

docker pull adrizcorp/hellodragonboard:latest

## To run it

docker run --privileged -t adrizcorp/hellodragonboard:latest /hellodragonboard 10

### output will be
Hello
Blink times=10


### Enjoy cheers!


