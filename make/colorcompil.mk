ifndef COLORCOMPIL
ifeq ($(shell test $(TERM_WIDTH) -gt 86; echo $$?), 0)
COLORCOMPIL = \
	if [ "$(shell test $P -lt 33; echo $$?)" = "0" ]; then \
    	echo -ne "\r\033[2K" $(LIGHTRED) "[$(P)%] "$(LIGHTRED) "Compiling ${NAME}" $(WHITE) "$<"; \
	else \
		if [ "$(shell test $P -lt 66; echo $$?)" = "0" ]; then \
    		echo -ne "\r\033[2K" $(YELLOW) "[$(P)%]" $(YELLOW) "Compiling ${NAME}" $(WHITE) "$<"; \
		else \
       		echo -ne "\r\033[2K" $(LIGHTGREEN) "[$(P)%]" $(LIGHTGREEN) "Compiling ${NAME}" $(WHITE) "$<"; \
		fi \
	fi
else
COLORCOMPIL = \
	if [ "$(shell test $P -lt 33; echo $$?)" = "0" ]; then \
    	echo -ne "\r\033[2K" $(LIGHTRED) "[$(P)%] "$(LIGHTRED) "Compiling ${NAME}"; \
	else \
		if [ "$(shell test $P -lt 66; echo $$?)" = "0" ]; then \
    		echo -ne "\r\033[2K" $(YELLOW) "[$(P)%]" $(YELLOW) "Compiling ${NAME}"; \
		else \
       		echo -ne "\r\033[2K" $(LIGHTGREEN) "[$(P)%]" $(LIGHTGREEN) "Compiling ${NAME}"; \
		fi \
	fi
endif
T := $(words $(SRCS))
N := x
C = $(words $N)$(eval N := x $N)
P = `expr $C '*' 100 / $T / 5`
endif

