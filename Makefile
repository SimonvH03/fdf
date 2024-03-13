NAME	= fdf
# CFLAGS	= -Wall -Werror -Wextra
CFLAGS	= -O3

FDF_H	= ./include/fdf.h

LMLXDIR	= ./MLX42
LIBMLX	= $(LMLXDIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
LFTDIR	= ./libft
LIBFT	= $(LFTDIR)/libft.a

HEADERS	= -I ./include -I $(LMLXDIR)/include
LIBS	= $(LIBMLX) $(LIBFT)
SRCDIR	= ./src
SRC		=	$(SRCDIR)/fdf_draw_line.c \
			$(SRCDIR)/fdf_draw.c \
			$(SRCDIR)/fdf_project_optimized.c \
			$(SRCDIR)/fdf_project.c \
			$(SRCDIR)/main.c \
			$(SRCDIR)/map_colour.c \
			$(SRCDIR)/map_cycle_stuff.c \
			$(SRCDIR)/map_iteration.c \
			$(SRCDIR)/map_mods.c \
			$(SRCDIR)/map_read.c \
			$(SRCDIR)/menu_draw.c \
			$(SRCDIR)/over_the_horizon.c \
			$(SRCDIR)/user_inputs_keyscroll.c \
			$(SRCDIR)/user_inputs_presets.c \
			$(SRCDIR)/user_inputs.c \
			$(SRCDIR)/utils_calc.c \
			$(SRCDIR)/utils_draw.c \
			$(SRCDIR)/utils_fdf.c \
			$(SRCDIR)/utils_init.c \
			$(SRCDIR)/utils_map.c
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