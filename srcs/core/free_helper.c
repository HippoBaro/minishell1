/*
** my_free.c for minishell1 in /home/barrau_h/Desktop/minishell1/srcs/core
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Thu Jan 29 01:03:11 2015 Hippolyte Barraud
** Last update Thu Jan 29 01:03:21 2015 Hippolyte Barraud
*/

#include <stdlib.h>
#include "../../includes/minishell1.h"

void	free_array(char **arr)
{
  int	i;

  i = -1;
  if (arr != NULL)
    {
      while (arr[++i] != NULL)
	free(arr[i]);
      free(arr);
    }
}

void		free_list(t_list *list)
{
  t_list	*tmp;
  t_list	*next;

  tmp = list->next;
  while (tmp != list)
    {
      next = tmp->next;
      free(tmp->data);
      free(tmp);
      tmp = next;
    }
  free(list);
}
