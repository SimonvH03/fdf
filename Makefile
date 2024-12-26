NAME			=	fdf

CC				=	cc
CFLAGS			=	-Wall -Werror -Wextra -O3
CFLAGS			=	-g

FDF_H			=	fdf.h

LMLXDIR			=	MLX42
LIBMLX			=	$(LMLXDIR)/build/libmlx42.a -ldl -lglfw -pthread -lm

LFTDIR			=	libft
LIBFT			=	$(LFTDIR)/libft.a

LIBS			=	$(LIBMLX) $(LIBFT)
HEADERS			=	-I $(LMLXDIR)/include -I $(LFTDIR) -I ./

INIT_DIR		=	initialise
INIT_SRC		=	fdf_init.c \
					map_init.c \
					map_read_utils.c \
					map_read.c

INPUT_DIR		=	user_input
INPUT_SRC		=	keypress_scroll.c \
					projection_presets.c \
					user_inputs.c

MAP_DIR			=	map_data
MAP_SRC			=	map_colour.c \
					map_cycle_palettes.c \
					map_iteration.c \
					map_toggle_squish.c \
					utils.c

FDF_DIR			=	fdf_projection
FDF_SRC			=	rotate_optimized.c \
					rotate.c \
					scale.c \
					project.c \
					utils.c

RENDER_DIR		=	render
RENDER_SRC		=	draw_line_init.c \
					draw_line.c \
					draw.c \
					menu_draw.c \
					over_the_horizon.c \
					utils_calc.c \
					utils.c

SOURCE_DIR		=	src
SOURCE			=	$(SOURCE_DIR)/main.c \
					$(addprefix $(SOURCE_DIR)/$(INIT_DIR)/, $(INIT_SRC)) \
					$(addprefix $(SOURCE_DIR)/$(INPUT_DIR)/, $(INPUT_SRC)) \
					$(addprefix $(SOURCE_DIR)/$(MAP_DIR)/, $(MAP_SRC)) \
					$(addprefix $(SOURCE_DIR)/$(FDF_DIR)/, $(FDF_SRC)) \
					$(addprefix $(SOURCE_DIR)/$(RENDER_DIR)/, $(RENDER_SRC)) \

OBJECTS_DIR		=	objects
OBJECTS			=	$(SOURCE:$(SOURCE_DIR)/%.cpp=$(OBJECTS_DIR)/%.o)

all: $(NAME)

$(LIBFT):
	make -C $(LFTDIR) all

$(LIBMLX):
	cmake $(LMLXDIR) -B $(LMLXDIR)/build && make -C $(LMLXDIR)/build -j4 -s

$(OBJECTS_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(LIBS) $(OBJECTS) $(FDF_H)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@if [ -n "$(OBJECTS_DIR)" ] && [ "$(OBJECTS_DIR)" != "/" ] && [ -d "$(OBJECTS_DIR)" ]; then \
		rm -rf $(OBJECTS_DIR); \
	else \
		echo "Error: OBJECTS_DIR is undefined or invalid"; \
	fi
	make -C $(LFTDIR) clean

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LMLXDIR)/build

re: clean all

.PHONY: all, clean, fclean, re