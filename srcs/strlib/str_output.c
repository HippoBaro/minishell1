/*
** str_output.c for minishell1 in /home/barrau_h/Desktop/minishell1/srcs/strlib
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Thu Jan 29 00:59:01 2015 Hippolyte Barraud
** Last update Mon Feb  9 21:22:33 2015 Hippolyte Barraud
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "../../includes/minishell1.h"
#include "../../includes/get_next_line.h"

void	write_colored(const char *str, const char *color)
{
  (void)write(0, color, my_strlen(color));
  (void)write(0, str, my_strlen(str));
  (void)write(0, "\033[0m", my_strlen("\033[0m"));
}

void	writetxt(const char *str)
{
  (void)write(0, str, my_strlen(str));
}

void	print_header(int argc, char **argv)
{
  char	*data;
  int	filedesc;

  (void)argc;
  (void)argv;
  if (ENABLE_CLAR_CONSOLE)
    system("clear");
  if ((filedesc = open("./miscs/header", O_RDONLY)) < 0)
    {
      write_colored(ERROR_HEADER_MISSING, RED);
      return;
    }
  while ((data = get_next_line(filedesc)))
    {
      write_colored(data, GREEN);
      writetxt("\n");
    }
}
