NAME	= fdf
CFLAGS	= -Wextra -Wall -Werror #-Wunreachable-code -Ofast

LMLXDIR	= ./MLX42
LIBMLX	= $(LMLXDIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
LFTDIR	= ./libft
LIBFT	= $(LFTDIR)/libft.a

HEADERS	= -I ./include -I $(LIBMLX)/include
LIBS	= $(LIBMLX) $(LIBFT)
SRCDIR	= ./src
SRC		=	main.c \
			read_map.c
OBJS	= $(SRCDIR)/${SRC:.c=.o}

all: $(LIBS) $(NAME)

$(LIBFT):
	make -C $(LFTDIR) all

$(LIBMLX):
	cmake $(LMLXDIR) -B $(LMLXDIR)/build && make -C $(LMLXDIR)/build -j4

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	rm -rf $(OBJS)
	rm -rf $(LMLXDIR)/build

fclean: clean
	rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re