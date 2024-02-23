NAME	= fdf
CFLAGS	= -Wall -Werror -Wextra

FDF_H	= ./include/fdf.h

LMLXDIR	= ./MLX42
LIBMLX	= $(LMLXDIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
LFTDIR	= ./libft
LIBFT	= $(LFTDIR)/libft.a

HEADERS	= -I ./include -I $(LMLXDIR)/include
LIBS	= $(LIBMLX) $(LIBFT)
SRCDIR	= ./src
SRC		=	$(SRCDIR)/fdf_draw.c \
			$(SRCDIR)/main.c \
			$(SRCDIR)/map_project.c \
			$(SRCDIR)/map_read.c \
			$(SRCDIR)/menu_draw.c \
			$(SRCDIR)/user_inputs.c \
			$(SRCDIR)/utils_calc.c \
			$(SRCDIR)/utils_init.c \
			$(SRCDIR)/utils_misc.c \
			$(SRCDIR)/utils_test.c
OBJS	= ${SRC:.c=.o}

all: $(LIBS) $(NAME)

$(LIBFT):
	make -C $(LFTDIR) all

$(LIBMLX):
	cmake $(LMLXDIR) -B $(LMLXDIR)/build && make -C $(LMLXDIR)/build -j4

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS) $(FDF_H)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	make -C $(LFTDIR) clean
	rm -rf $(OBJS)
	rm -rf $(LMLXDIR)/build

fclean: clean
	rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re