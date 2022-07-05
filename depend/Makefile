SRCS = src/main.c src/test.c
OBJS = $(addprefix obj/, $(notdir $(SRCS:.c=.o)))
DEPS = $(addprefix dep/, $(notdir $(SRCS:.c=.c.d)))

PROG = hello

CC = gcc
CFLAGS = -I./inc

$(shell mkdir -p dep obj)

all : dep obj prog

prog : $(PROG)

$(PROG) : $(OBJS)
	$(CC) -o $@ $(OBJS)

dep : $(DEPS)

dep/%.c.d : src/%.c
	@set -e; \
	if [ -f "$<" ]; then \
	  rm -f $@; \
	  echo "generate $@"; \
	  $(CC) $(CFLAGS) -M $< > $(@).tmp; \
	  sed 's|^\(.*\)\.o: |obj/\1.o: |g' < $(@).tmp > $@; \
	  rm -f $(@).tmp; \
	fi

obj : $(OBJS)

obj/%.o :
	@if [ -z "$<" ]; then \
	    echo "no dependency for $@"; \
	    exit 1; \
	fi
	$(CC) $(CFLAGS) -c -o $@ $<

debug :
	@echo DEPS is $(DEPS)

test :
	./$(PROG)

clean :
	rm -f $(OBJS) $(PROG)
	rm -f $(DEPS)

mclean :
	$(MAKE) clean
	rm -rf obj dep

-include $(DEPS)

.PHONY : \
    all clean test obj prog debug depend dep

