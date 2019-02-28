# hellodragonboard from scratch using Docker

Prints message on console
"Hello DragonBoard... Blinking Led "
and blinks LED 10 times

## build the source code for the binary file
gcc -static hellodragonboard.c -o hellodragonboard -lpthread

## Pull it on docker:

docker pull adrizcorp/hellodragonboard:latest

## Run it

docker run --privileged -t adrizcorp/hellodragonboard:latest

### cheers!


