/*
** builtins_env.c for minishell1 in /home/barrau_h/Desktop/minishell1/srcs/builtins
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Thu Jan 29 01:05:57 2015 Hippolyte Barraud
** Last update Mon Feb  9 21:11:51 2015 Hippolyte Barraud
*/

#include <unistd.h>
#include <stdlib.h>
#include "../../includes/minishell1.h"

static char	env_option_check_concat(char *opt, char *str)
{
  char		little[3];
  int		i;
  int		j;

  opt[ID_UN] = 0;
  little[ID_IGNORE] = 'i';
  little[ID_NULL] = '0';
  little[ID_UN] = 'u';
  i = 0;
  while (str[++i])
    {
      j = -1;
      while (++j < 3 && little[j] != str[i]);
      if (j == 3)
	return (my_env_error(str, 1, i));
      else
	opt[j] = 1;
    }
  return (0);
}

static char	env_option_check_explicit(char *opt, char *str)
{
  int		i;
  char		**big;

  if ((big = malloc(sizeof(char *) * 5)) == NULL)
    my_puterror(ERROR_MALLOC);
  opt[ID_UN] = 0;
  big[ID_IGNORE] = "ignore-environment";
  big[ID_NULL] = "null";
  big[ID_UN] = "unset";
  big[ID_HELP] = "help";
  big[ID_VER] = "version";
  i = -1;
  while (++i < 5)
    {
      if ((i != 2 && my_strcmp(str, big[i], 0)) ||
	  (i == 2 && my_strcmp(str, big[i], 1)))
	{
	  opt[i] = 1;
	  i = 5;
	}
    }
  if (i == 5)
    return (my_env_error(str, 0, 0));
  return (0);
}

static char	env_option_check(t_list *env, char **var, char *opt,
				 char ret)
{
  int		i;

  i = -1;
  while (ret == 0 && ++i >= 0 && var[i] != NULL)
    {
      if (var[i][0] == '-' && var[i][1] != '-' && var[i][1] != '\0')
	{
	  ret = env_option_check_concat(&opt[0], var[i]);
	  if (opt[ID_UN] && ret == 0 && var[++i] != NULL)
	    remove_node(&env, var[i++]);
	  else if (opt[ID_UN] && ret == 0 && var[i] == NULL)
	    return (my_env_error(NULL, 2, 0));
	}
      else if (var[i][0] == '-' && var[i][1] == '-' && var[i][2] != '\0')
	{
	  ret = env_option_check_explicit(&opt[0], &var[i][2]);
	  if (opt[ID_UN] && ret == 0 && UNSET(var[i][8]) && UNSET(var[i][9]))
	    remove_node(&env, &var[i][my_strlen("--unset=")]);
	  else if (opt[ID_UN] && ret == 0)
	    return (my_env_error(NULL, 3, 0));
	}
      if (opt[ID_HELP] || opt[ID_VER] || (var[i] != NULL && var[i][0] != '-'))
	return ((var[i][0] != '-') ? ++i : 0);
    }
  return (ret);
}

char	my_env_opt(t_list *env, char **var)
{
  char	opt[5];
  int	i;
  int	out;

  i = -1;
  while (++i < 5)
    opt[i] = 0;
  out = env_option_check(env, &var[1], &opt[0], 0);
  if (out == -1)
    return (-1);
  else if (out > 0)
    execute_command((opt[ID_IGNORE] == 1) ? NULL : env, &var[out],
		    find_element(env, "PATH"));
  else if (out <= 0 && !opt[ID_IGNORE])
    display_list(env, opt[ID_NULL]);
  return (0);
}
