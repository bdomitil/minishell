# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bdomitil <bdomitil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/22 19:13:25 by bdomitil          #+#    #+#              #
#   Updated: 2021/10/23 04:20:26 by                  ###   ########.fr       # #
#                                                                              #
# **************************************************************************** #

files.c = parser/double_link_lst.c parser/test_utils.c \
		 parser/parse_main.c parser/string_end.c parser/quotes_release.c parser/screen_chars.c \
		 parser/get_var_mean.c parser/general_utils.c parser/split_out_quotes.c parser/deviding.c \
		 parser/deviding_utils.c parser/redir_fill.c parser/clean_utils.c parser/redir_utils.c \
		 parser/parse_env.c parser/env_utils.c parser/path_find.c engine/main.c \
		 engine/rd.c engine/exec.c engine/pipe.c engine/clean_main_list.c \
		 engine/arr_join.c engine/here_doc.c engine/bi_calling.c engine/bi_utils.c \
		 engine/cd.c engine/echo.c engine/export.c engine/unset.c engine/pwd.c \
		 engine/signal.c engine/exit.c engine/error.c engine/cd_extra.c engine/export_extra.c\
		 engine/env.c engine/wait.c engine/signal_redefinition.c engine/exit_print.c

#CFLAGS = -g -Wall -Wextra -Werror
CFLAGS = -g
HEADERS = headers/parse.h

files.o = $(files.c:.c=.o)

NAME = minishell


all :	lib_compil $(NAME)

$(NAME) : $(files.o) 
		@gcc $(CFLAGS) -L/Users/$(USER)/.brew/Cellar/readline/8.1.1/lib/ -I/Users/$(USER)/.brew/Cellar/readline/8.1.1/include -lreadline $(files.o) libft/libft.a  -o $(NAME) # ?
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