NAME	= fdf
# CFLAGS	= -Wall -Werror -Wextra -O3
CFLAGS	= -g

FDF_H	= ./include/fdf.h

LMLXDIR	= ./MLX42
LIBMLX	= $(LMLXDIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
LFTDIR	= ./libft
LIBFT	= $(LFTDIR)/libft.a

HEADERS	= -I ./include -I $(LMLXDIR)/include
LIBS	= $(LIBMLX) $(LIBFT)
SRCDIR	= ./src
SRC		=	$(SRCDIR)/draw_line_init.c \
			$(SRCDIR)/draw_line.c \
			$(SRCDIR)/draw_utils.c \
			$(SRCDIR)/draw.c \
			$(SRCDIR)/fdf_init.c \
			$(SRCDIR)/fdf_rotate_optimized.c \
			$(SRCDIR)/fdf_rotate.c \
			$(SRCDIR)/fdf_scale.c \
			$(SRCDIR)/fdf_utils.c \
			$(SRCDIR)/main.c \
			$(SRCDIR)/map_colour.c \
			$(SRCDIR)/map_cycle_palettes.c \
			$(SRCDIR)/map_init.c \
			$(SRCDIR)/map_iteration.c \
			$(SRCDIR)/map_read.c \
			$(SRCDIR)/map_read_utils.c \
			$(SRCDIR)/map_utils.c \
			$(SRCDIR)/menu_draw.c \
			$(SRCDIR)/over_the_horizon.c \
			$(SRCDIR)/project.c \
			$(SRCDIR)/user_inputs_keyscroll.c \
			$(SRCDIR)/user_inputs_presets.c \
			$(SRCDIR)/user_inputs.c \
			$(SRCDIR)/utils_calc.c

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

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LMLXDIR)/build

re: clean all

.PHONY: all, clean, fclean, re