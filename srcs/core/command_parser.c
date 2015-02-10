/*
** my_check.c for minishell1 in /home/barrau_h/Desktop/minishell1/srcs/core
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Thu Jan 29 01:05:07 2015 Hippolyte Barraud
** Last update Mon Feb  9 21:13:03 2015 Hippolyte Barraud
*/

#include <unistd.h>
#include <stdlib.h>
#include "../../includes/minishell1.h"

static int	check_command(char **arr, t_list *env)
{
  char		*pwd;

  if (my_strcmp(arr[0], "exit", 0))
    return (my_exit(env, arr));
  else if (my_strcmp(arr[0], "env", 0))
    my_env(env, arr);
  else if (my_strcmp(arr[0], "alias", 0))
    my_alias(env);
  else if (my_strcmp(arr[0], "cd", 0))
    return (my_cd(arr) + 1);
  else if (my_strcmp(arr[0], "pwd", 0))
    {
      pwd = find_element(env, "PWD");
      writetxt(pwd);
      writetxt("\n");
      return (1);
    }
  else if (my_strcmp(arr[0], "setenv", 0))
    my_setenv(env, arr);
  else if (my_strcmp(arr[0], "unsetenv", 0))
    my_unsetenv(env, arr);
  else
    return (0);
  return (1);
}

int	cmd_interpret(char *str, t_list *env)
{
  char	**arr;
  char	res;

  arr = my_str_to_wordtab(str, ' ', '\t');
  if (arr == NULL || arr[0] == NULL)
    return (0);
  if ((res = check_command(arr, env)) != 0)
    {
      free_array(arr);
      return (res - 1);
    }
  else
    {
      apply_alias(arr, env);
      (void)execute_command(env, arr, find_element(env, "PATH"));
    }
  free_array(arr);
  return (0);
}
