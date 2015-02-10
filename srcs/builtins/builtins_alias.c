/*
** builtins_alias.c for minishell1 in /minishell1/srcs/builtins/builtins_alias.c
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Feb 8, 2015 Feb 8, 2015 2015 Hippolyte Barraud
** Last update Tue Feb 10 14:56:15 2015 Hippolyte Barraud
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "../../includes/minishell1.h"
#include "../../includes/get_next_line.h"

t_list 		*get_my_alias(t_list *env)
{
  char 		*data;
  int  		filedesc;
  char 		*tmp[BUFF];
  int  		i;
  static int   	loaded = 0;
  static t_list	*lst = NULL;

  i = 0;
  if (get_my_var(env, "HOME") == NULL || loaded)
    return (lst);
  if ((filedesc = open(concat_path(get_my_var(env, "HOME"),
				   ".bashrc"), O_RDONLY)) < 0)
    my_puterror(ERROR_BASHRC_MISSING);
  while ((data = get_next_line(filedesc)))
    {
      if (strncmp(data, "alias ", 6) == 0)
	tmp[i++] = (data += 6);
      else
	free(data);
    }
  tmp[i] = NULL;
  close(filedesc);
  lst = alias_create_list(&tmp[0]);
  return (lst);
}

int    	get_alias_name(char *alias)
{
  int	i;

  i = 0;
  while (alias[i] != '=')
    i++;
  return (i);
}

int    	parse_aliases(t_list *tmp, char **arr)
{
  char 	**command;
  char	*str;
  int 	i;

  i = 0;
  if (strcmp(arr[0], str = strndup(tmp->data, get_alias_name(tmp->data))) == 0)
    {
      tmp->data += get_alias_name(tmp->data) + 2;
      while ((tmp->data)[i] != '\0')
	i++;
      (tmp->data)[i - 1] = '\0';
      command = my_str_to_wordtab(tmp->data, ' ', '\t');
      arr[0] = command[0];
      append_to_wordtab(arr, &command[1]);
      free(str);
      return (1);
    }
  free(str);
  return (0);
}

void		apply_alias(char **arr, t_list *env)
{
  t_list	*tmp;
  t_list	*aliases;

  if ((aliases = get_my_alias(env)) == NULL)
	return;
  tmp = aliases->next;
  while (tmp != aliases)
    {
      if (parse_aliases(tmp, arr) == 1)
	break;
      tmp = tmp->next;
    }
}

void		my_alias(t_list *env)
{
  t_list	*aliases;

  aliases = get_my_alias(env);
  alias_display_list(aliases, 0);
}
