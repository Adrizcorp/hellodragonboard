# hellodragonboard from scratch using Docker

the docker container at hand prints a message on console
"Hello DragonBoard... Blinking Led "
and blinks LED 10 times

## To build the source code for the binary file
gcc -static hellodragonboard.c -o hellodragonboard -lpthread

## To pull it on docker:

docker pull adrizcorp/hellodragonboard:latest

## To run it

docker run --privileged -t adrizcorp/hellodragonboard:latest

### Enjoy cheers!


