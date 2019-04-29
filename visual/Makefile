NAME = visual

FILE_C = \
		 source/crea_color_map.c\
		 source/init.c\
		 source/main.c\
		 source/put_square.c\
		 ../source/infill_arr.c\
		 source/score.c

FILE_O = crea_color_map.o init.o main.o put_square.o score.o infill_arr.o

FILE_LIB = -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit  -L ../libft/ -lftprintf

FILE_INCLUDE = -I /usr/local/include -I ./include/

FLSGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME):
	gcc $(FLAGS) $(HFILES) -c $(FILE_C) 
	gcc $(FLAFS) $(FILE_C) $(FILE_LIB) -o $(NAME)
	
clean:
	/bin/rm -f $(FILE_O) 
	
fclean: clean 
	/bin/rm -f $(NAME)
	
re: fclean all 
