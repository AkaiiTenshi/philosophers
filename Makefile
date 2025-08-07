include make/srcs.mk
include make/colors.mk

TERM_WIDTH := $(shell tput cols)
SHELL = /bin/bash

vpath %.c ${SRCS_PATH}

INC = -I includes/ 

OBJS = ${patsubst %.c, ${OBJS_PATH}/%.o, ${SRCS}}
OBJS_PATH = ./objs/

CC = cc
CFLAGS += -g3
CFLAGS += -Wall -Wextra -Werror
NAME = philo

default: help all

all: ${NAME}

help:
	@	echo -ne "\r\033[2K" $(WHITE) "--------------------------------------------------------------------"${NC}"\n"
	@	echo -ne "\r\033[2K" $(LIGHTPURPLE) "all       →  "${NC}"Compile the program.\n"
	@	echo -ne "\r\033[2K" $(LIGHTPURPLE) "clean     →  "${NC}"Removes temporary files.\n"
	@	echo -ne "\r\033[2K" $(LIGHTPURPLE) "fclean    →  "${NC}"Deletes all generated files.\n"
	@	echo -ne "\r\033[2K" $(LIGHTPURPLE) "re        →  "${NC}"Rebuilds the project.\n"
	@	echo -ne "\r\033[2K" $(LIGHTPURPLE) "formule pair →  "${NC}"time_to_die >= 2 * time_to_eat + 10\n"
	@	echo -ne "\r\033[2K" $(LIGHTPURPLE) "formule impair →  "${NC}"time_to_die >= 2 * time_to_eat * N / (N - 1) + 10\n"
	@	echo -ne "\r\033[2K" $(WHITE) "--------------------------------------------------------------------"${NC}"\n"

${OBJS_PATH}/%.o: %.c Makefile includes/philo.h
	@	mkdir -p ${OBJS_PATH}
	@	$(COLORCOMPIL)
	@	${CC} ${CFLAGS} -c $< -o $@ ${INC}

${NAME}: ${OBJS}
	@	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${INC}
	@	echo -ne "\r\033[2K" $(LIGHTGREEN) "→ $(NAME) OK!\n"$(NC)

clean:	
	@	rm -rf ${OBJS_PATH}
	@	echo -ne "\r\033[2K" $(LIGHTRED) "→ objs cleaned\n"$(NC)

fclean: clean
	@	rm -f ${NAME}
	@	echo -ne "\r\033[2K" $(LIGHTRED) "→ $(NAME) cleaned\n"$(NC)

re: fclean all

.PHONY: default all clean fclean re help

