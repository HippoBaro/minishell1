##
## Makefile for minishell in /home/barrau_h/Desktop/minishell1
## 
## Made by Hippolyte Barraud
## Login   <barrau_h@epitech.net>
## 
## Started on  Thu Jan 29 01:40:22 2015 Hippolyte Barraud
## Last update Tue Feb 10 19:38:16 2015 Hippolyte Barraud
##

CC		= gcc

RM		= rm -f

CFLAGS		= -Wall -Wextra -Werror -pedantic 

LDFLAGS		+= -I.

NAME		= mysh

SRCPATH		= ./srcs/

LISTMANPATH	= $(SRCPATH)list_manager/

STRLIBPATH	= $(SRCPATH)strlib/

BUILTINSPATH	= $(SRCPATH)builtins/

COREPATH	= $(SRCPATH)core/

SRCS		= $(SRCPATH)main.c			\
		  $(COREPATH)error_handler.c		\
		  $(COREPATH)path_manager.c		\
		  $(COREPATH)var_helper.c		\
	          $(COREPATH)command_parser.c		\
		  $(COREPATH)free_helper.c		\
		  $(LISTMANPATH)list_man.c		\
		  $(LISTMANPATH)list_man_add.c		\
		  $(LISTMANPATH)list_alias_man.c	\
		  $(BUILTINSPATH)builtins_env.c		\
		  $(BUILTINSPATH)builtins_core.c	\
		  $(BUILTINSPATH)builtins_cd.c		\
		  $(BUILTINSPATH)builtins_pwd.c		\
		  $(BUILTINSPATH)builtins_alias.c	\
		  $(STRLIBPATH)my_str1.c		\
		  $(STRLIBPATH)my_str2.c		\
		  $(STRLIBPATH)str_output.c		\
		  $(STRLIBPATH)get_next_line.c		\
		  $(STRLIBPATH)my_str_to_wordtab.c

OBJS		= $(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
