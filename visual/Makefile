
NAME = visual

FILE_C = \
		 source/crea_color_map.c\
		 source/init.c\
		 source/main.c\
		 source/put_square.c\
		 ../indill_arr.c\
		 source/score.c

FILE_O = crea_color_map.o init.o main.o put_square.o score.o indill_arr.o

FILE_LIB = -L /usr/X11/lib -lmlx -lXext -lX11  -L ../libft/ -lftprintf

FILE_INCLUDE = -I /usr/local/include -I ./include/
FLSGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME):
	gcc $(FLAGS) $(FILE_INCLUDE) -g $(FILE_C) $(FILE_LIB) -o $(NAME)

clean:
	/bin/rm -f $(FILE_O) 
	
fclean: clean 
	/bin/rm -f $(NAME)
	
re: fclean all 
