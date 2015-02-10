/*
** my_exec.c for minishell1 in /home/barrau_h/Desktop/minishell1/srcs/core
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Thu Jan 29 01:03:32 2015 Hippolyte Barraud
** Last update Mon Feb  9 21:16:40 2015 Hippolyte Barraud
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../../includes/minishell1.h"

static char    	**list_to_chararr(t_list *env)
{
  t_list       	*tmp;
  char 		**arr;
  int		i;
  int  		count;

  count = 0;
  if (env == NULL)
    return (NULL);
  tmp = env->next;
  while (tmp != env)
    {
      ++count;
      tmp = tmp->next;
    }
  if ((arr = malloc(sizeof(char *) * (count + 1))) == NULL)
    my_puterror(ERROR_MALLOC);
  i = -1;
  tmp = env->next;
  while (tmp != env)
    {
      arr[++i] = my_strdup(tmp->data);
      tmp = tmp->next;
    }
  arr[++i] = NULL;
  return (arr);
}

char	*concat_path(char *path, char *exec)
{
  char	*res;
  int  	len;
  int  	size;

  len = my_strlen(path);
  size = (path[len - 1] == '/') ? len : len + 1;
  if ((res = malloc(sizeof(char) * (size + my_strlen(exec) + 1))) == NULL)
    my_puterror(ERROR_MALLOC);
  res[0] = '\0';
  res = my_strcat(res, path);
  if (len != size)
    res[len] = '/';
  res[size] = '\0';
  res = my_strcat(res, exec);
  return (res);
}

static char	get_binmame(char *str)
{
  int		i;
  char		path_bin;

  i = -1;
  path_bin = 0;
  while (str[++i] && path_bin == 0)
    if (str[i] == '/')
      path_bin = 1;
  return (path_bin);
}

static char	*access_path(char *str, char *path)
{
  char		**arr;
  int		i;
  char		*exec;

  if (get_binmame(str))
    return ((access(str, F_OK | X_OK) == -1) ? NULL : str);
  arr = my_str_to_wordtab(path, ':', ':');
  i = -1;
  while (arr[++i] != NULL)
    {
      exec = concat_path(arr[i], str);
      if (access(exec, F_OK | X_OK) != -1)
	{
	  free_array(arr);
	  return (exec);
	}
      free(exec);
    }
  return (NULL);
}

char	execute_command(t_list *env, char **exec_opt, char *path)
{
  pid_t	pid;
  int	statut;
  char	**my_env;
  char	*exec;

  my_env = list_to_chararr(env);
  pid = fork();
  if (pid == -1)
	{
	  my_error(ERROR_FORK, "ERREUR");
	  return (1);
	}
  else if (pid == 0)
	{
	  if ((exec = access_path(exec_opt[0], path)) == NULL ||
		  execve(exec, exec_opt, my_env) == -1)
		{
		  free_array(my_env);
		  return (print_unknow_cmd((exec == NULL) ? exec_opt[0] : exec));
		}
	}
  else
	  wait(&statut);
  free_array(my_env);
  return (0);
}
