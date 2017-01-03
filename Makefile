NAME := WEsort
SRCS := $(wildcard *.c)
OBJS := ${SRCS:.c=.o}
all: $(NAME)

$(NAME): $(OBJS)
	$(LINK.cc) $(OBJS) -o $(NAME)

clean:
	@- $(RM) $(NAME)
	@- $(RM) $(OBJS)

