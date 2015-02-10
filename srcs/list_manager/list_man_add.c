/*
** list_man_add.c for minishell1 in /home/barrau_h/Desktop/minishell1/srcs/list_manager
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Thu Jan 29 01:01:28 2015 Hippolyte Barraud
** Last update Thu Jan 29 01:01:29 2015 Hippolyte Barraud
*/

#include <stdlib.h>
#include "../../includes/minishell1.h"

char		*find_element(t_list *lst, char *value)
{
  t_list	*tmp;

  tmp = lst->next;
  while (tmp != lst && !my_strcmp(tmp->data, value, 1))
    tmp = tmp->next;
  if (tmp == lst)
    return (NULL);
  return (&tmp->data[my_strlen(value) + 1]);
}

void	set_env_list(t_list *lst, char *var, char *value)
{
  remove_node(&lst, var);
  add_node(&lst, value, var);
}
