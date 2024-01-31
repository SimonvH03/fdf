NAME		=	fdf
CFLAGS		=	-Wall -Werror -Wextra
LIBMLX		=	./MLX42

HEADERS		=	$(LIBMLX)/MLX42.h
ARCHIVES	=	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -lm -pthread
SRC			=	
OBJS		=	$(SRC:.c=.0)

all: libmlx42 $(NAME)

libmlx42:
	cmake -C $(LIBMLX) -B $(LIBMLX)/build && cmake -C $(LIBMLX) -B $(LIBMLX)/build -j4

%.o: %.c
	cc $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	cc $(OBJS) $(ARCHIVES) -o $(NAME) -I $(HEADERS)

clean:
	rm -rf $(OBJS)
	rm -rf $(LIBMLX)/build

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all, libmlx42, clean, fclean, re