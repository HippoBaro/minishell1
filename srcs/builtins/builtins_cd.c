/*
** builtins_cd.c for minishell1 in /home/barrau_h/Desktop/minishell1/srcs/builtins
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Thu Jan 29 01:06:46 2015 Hippolyte Barraud
** Last update Mon Feb  9 21:10:33 2015 Hippolyte Barraud
*/

#include <unistd.h>
#include <stdlib.h>
#include "../../includes/minishell1.h"

int	my_cd(char **arr)
{
  if (arr[1] != NULL)
    {
      if (access(arr[1], F_OK) == -1)
	{
	  my_error(ERROR_404, "cd");
	  (void)write(2, arr[1], my_strlen(arr[1]));
	  (void)write(2, "\n", 1);
	  return (0);
	}
      if (access(arr[1], R_OK) == -1)
	{
	  my_error(ERROR_ACCES_DENIED, "cd");
	  (void)write(2, arr[1], my_strlen(arr[1]));
	  (void)write(2, "\n", 1);
	  return (0);
	}
      if (chdir(arr[1]) == -1)
	{
	  my_error(ERROR_DIR_LOCKED, "cd");
	  return (0);
	}
      return (1);
    }
  my_error(CD_USAGE, "cd");
  return (0);
}
