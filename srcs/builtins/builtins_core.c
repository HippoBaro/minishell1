/*
** builtins_core.c for minishell1 in /home/barrau_h/Desktop/minishell1/srcs/builtins
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Thu Jan 29 01:06:24 2015 Hippolyte Barraud
** Last update Thu Jan 29 01:06:25 2015 Hippolyte Barraud
*/

#include <unistd.h>
#include <stdlib.h>
#include "../../includes/minishell1.h"

char	my_exit(t_list *env, char **arr)
{
  free_array(arr);
  free_list(env);
  write_colored(GOODBYE, GREEN);
  exit(EXIT_SUCCESS);
  return (EXIT_SUCCESS);
}

void	my_setenv(t_list *env, char **arr)
{
  if (arr[1] != NULL && arr[2] != NULL)
    set_env_list(env, arr[1], arr[2]);
  else
    my_error(SETENV_USAGE, "setenv");
}

void	my_unsetenv(t_list *lst, char **arr)
{
  if (arr[1] != NULL)
    remove_node(&lst, arr[1]);
  else
    my_error(UNSETENV_USAGE, "unsetenv");
}

void	my_env(t_list *env, char **options)
{
  my_env_opt(env, options);
}
