# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/22 19:13:25 by bdomitil          #+#    #+#              #
#    Updated: 2021/10/04 16:04:27 by bdomitil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

files.c = parser/double_link_lst.c parser/test_utils.c \
		 parser/parse_main.c parser/string_end.c parser/quotes_release.c parser/screen_chars.c \
		 parser/get_var_mean.c parser/general_utils.c parser/split_out_quotes.c parser/deviding.c \
		 parser/deviding_utils.c parser/redir_fill.c parser/clean_utils.c parser/redir_utils.c \
		 parser/parse_env.c parser/env_utils.c parser/path_find.c engine/main.c \
		 engine/rd.c engine/exec.c engine/pipe.c engine/clean_main_list.c\

CFLAGS = -g -Wall -Wextra -Werror

HEADERS = headers/parse.h

files.o = $(files.c:.c=.o)

NAME = a.out


all :	lib_compil $(NAME)

$(NAME) : $(files.o) 
		@gcc -lreadline $(files.o) libft/libft.a  -o a.out
		@echo "\033[7m PROGRAM IS READY TO BE USED!\033[0m"

lib_compil: 
		@make -C libft/


%.o : %.c libft/*.c $(HEADERS)
		@gcc $(CFLAGS)  -c  $<  -o $@
		@echo  "\033[36m$<\033[0m \033[35m is compiled!\033[0m" 

clean :  
		@rm -f $(files.o)
		@rm -rf $(NAME).dSYM
		@make -C libft/ clean
		@echo "\033[7mclean is done!\033[0m"

fclean : clean
		@rm  -f $(NAME)
		@make -C libft/ fclean
		@echo "\033[7mfclean is done!\033[0m"

re	:  fclean all	


.PHONY : all clean  fclean lib_compil
