/*
** list_man.c for minishell1 in /home/barrau_h/Desktop/minishell1/srcs/list_manager
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Thu Jan 29 01:01:48 2015 Hippolyte Barraud
** Last update Sun Feb  8 03:43:05 2015 Hippolyte Barraud
*/

#include <unistd.h>
#include <stdlib.h>
#include "../../includes/minishell1.h"

void		add_node(t_list **list, char *val, char *start)
{
  t_list	*new;
  int		i;
  int		j;
  int		size;

  if ((new = malloc(sizeof(*new))) == NULL)
    my_puterror(ERROR_MALLOC);
  size = (start != NULL) ? my_strlen(start) : 0;
  if ((new->data = malloc(size + my_strlen(val) + 1)) == NULL)
    my_puterror(ERROR_MALLOC);
  j = -1;
  i = -1;
  while (start != NULL && start[++i])
    new->data[++j] = start[i];
  i = -1;
  if (j != -1)
    new->data[++j] = '=';
  while (val[++i])
    new->data[++j] = val[i];
  new->data[++j] = '\0';
  new->prec = (*list)->prec;
  new->next = (*list);
  (*list)->prec->next = new;
  (*list)->prec = new;
}

t_list		*create_list(char **env)
{
  t_list	*root;
  int		i;

  if ((root = malloc(sizeof(*root))) == NULL)
    my_puterror(ERROR_MALLOC);
  root->next = root;
  root->prec = root;
  i = -1;
  while (env[++i])
    add_node(&root, env[i], NULL);
  envptr = root;
  return (root);
}

void		remove_node(t_list **lst, char *value)
{
  t_list	*tmp;

  tmp = (*lst)->next;
  while (tmp != (*lst) && !my_strcmp(tmp->data, value, 1))
    tmp = tmp->next;
  if (tmp != (*lst))
    {
      tmp->prec->next = tmp->next;
      tmp->next->prec = tmp->prec;
      free(tmp);
    }
}

void		display_list(t_list *lst, char type)
{
  t_list	*tmp;

  tmp = lst->next;
  while (tmp != lst)
    {
      (void)write(1, tmp->data, my_strlen(tmp->data));
      if ((type != 1 && tmp->next != lst) || type == 0)
	(void)write(1, "\n", 1);
      tmp = tmp->next;
    }
}
