NAME	= fdf
CFLAGS	= -Wextra -Wall -Werror

LMLXDIR	= ./MLX42
LIBMLX	= $(LMLXDIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
LFTDIR	= ./libft
LIBFT	= $(LFTDIR)/libft.a

HEADERS	= -I ./include -I $(LMLXDIR)/include
LIBS	= $(LIBMLX) $(LIBFT)
SRCDIR	= ./src
SRC		=	$(SRCDIR)/map_project.c \
			$(SRCDIR)/map_read.c \
			$(SRCDIR)/test_utils.c \
			$(SRCDIR)/utils.c \
			$(SRCDIR)/main.c
OBJS	= ${SRC:.c=.o}

all: $(LIBS) $(NAME)

$(LIBFT):
	make -C $(LFTDIR) all

$(LIBMLX):
	cmake $(LMLXDIR) -B $(LMLXDIR)/build && make -C $(LMLXDIR)/build -j4

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	make -C $(LFTDIR) clean
	rm -rf $(OBJS)
	rm -rf $(LMLXDIR)/build

fclean: clean
	rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re