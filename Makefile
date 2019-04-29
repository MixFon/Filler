NAME = widraugr.filler

FILE_C = \
		 source/add_list.c\
		 source/infill_perimetr.c\
		 source/search_sharp.c\
		 source/infill_arr.c\
		 source/main.c\
		 source/source.c

FILE_O =\
	   	add_list.o\
	   	infill_perimetr.o\
	   	main.o\
	   	search_sharp.o\
		infill_arr.o\
		source.o

FILE_LIB =  -L libft/ -lftprintf

FILE_INCLUDE = -I ./include/

FLSGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME):
	make re -C libft
	make re -C visual
	gcc $(FLAGS) $(HFILES) -c $(FILE_C) 
	gcc $(FLAFS) $(FILE_C) $(FILE_LIB) -o $(NAME)
	make clean -C libft
	make clean -C visual
	
clean:
	/bin/rm -f $(FILE_O) 	

fclean: clean 
	/bin/rm -f $(NAME) 	

re: fclean all 
