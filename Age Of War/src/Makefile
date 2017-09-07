# Makefile for project

COMPILER_TYPE = gnu

CC = gcc

PROG = project
SRCS = main.c
SRCS +=  vbe.c video_gr.c timer.c keyboard.c mouse.c
SRCS += AgeOfWar.c bitmap.c game.c bullet.c defense.c menu.c special.c tower.c player.c unit.c terrain.c number.c
SRCS += test_animation.c slot.c font.c rtc.c
CCFLAGS= -Wall
 
DPADD += ${LIBDRIVER} ${LIBSYS}
LDADD += -llm -ldriver -lsys

LDFLAGS += -L.

MAN=

.include <bsd.prog.mk>
.include <bsd.gcc.mk>