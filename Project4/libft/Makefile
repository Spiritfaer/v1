NAME = libft.a
HEADER = *.h
SOURCE = *.c
OBJECT = *.o
FLAG_G = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	gcc $(FLAG_G) -c $(SOURCE)
	ar crs $(NAME) $(OBJECT)

clean:
	rm -Rf *.o
fclean: clean
	rm -Rf *.a

re: fclean all