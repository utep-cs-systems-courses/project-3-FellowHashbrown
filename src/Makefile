COMMON_OBJECTS  = 
CPU 		= msp430g2553
CFLAGS		= -mmcu=${CPU} -I../h -L/opt/ti/msp430_gcc/include

CC		= msp430-elf-gcc
AS		= msp430-elf-as -mcpu=msp430 --traditional-format -mP

all: project3.elf

project3.elf: ${COMMON_OBJECTS} stateMachine.o buzz.o interrupts.o led.o switches.o main.o shapeStates.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: project3.elf
	msp430loader.sh project3.elf

clean:
	rm -f *.o *.elf
	rm -rf lib h

buzz.o: buzz.c buzz.h

led.o: led.c led.h switches.h

switches.o: switches.c led.h switches.h buzz.h

stateMachine.o: stateMachine.h led.h switches.h shapeStates.h

shapeStates.o: shapeStates.h ../lcdLib/lcdutils.h ../lcdLib/lcddraw.h ../shapeLib/shape.h ../circleLib/abCircle.h

main.o: main.c buzz.h led.h switches.h

interrupts.o: interrupts.c
