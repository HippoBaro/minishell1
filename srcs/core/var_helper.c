/*
** my_set_var.c for minishell1 in /home/barrau_h/Desktop/minishell1/srcs/core
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Thu Jan 29 01:02:27 2015 Hippolyte Barraud
** Last update Thu Jan 29 01:02:28 2015 Hippolyte Barraud
*/

#include <stdlib.h>
#include "../../includes/minishell1.h"

char	*get_my_var(t_list *env, char *code)
{
  char	*var;

  var = find_element(env, code);
  return (var);
}

char	*get_my_pwd(t_list *env)
{
  char	*pwd;

  pwd = my_pwd();
  set_env_list(env, "PWD", pwd);
  return (pwd);
}

void	init_env(t_list *lst)
{
  char	*path;

  set_env_list(lst, "_", ENV);
  path = get_my_var(lst, "PATH");
  if (path == NULL)
    {
      set_env_list(lst, "PATH", PATH);
      path = PATH;
    }
}
