COMMON_OBJECTS  =
CPU 		= msp430g2553
CFLAGS		= -mmcu=${CPU} -I../h -L/opt/ti/msp430_gcc/include

CC		= msp430-elf-gcc
AS		= msp430-elf-as -mcpu=msp430 --traditional-format -mP

all: project2.elf

project2.elf: ${COMMON_OBJECTS} stateMachine.o buzz.o interrupts.o led.o switches.o main.o shapeStates.o ../lib/libTimer.a ../circleLib/**/*.o ../lcdLib/**/*.o ../shapeLib/**/*.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: project2.elf
	msp430loader.sh project2.elf

clean:
	rm -f *.o *.elf
	rm -rf lib h

buzz.o: buzz.c buzz.h

led.o: led.c led.h switches.h

switches.o: switches.c led.h switches.h buzz.h

stateMachine.o: stateMachine.h led.h switches.h shapeStates.h

shapeStates.o: shapeStates.h

main.o: main.c buzz.h led.h switches.h

interrupts.o: interrupts.c
