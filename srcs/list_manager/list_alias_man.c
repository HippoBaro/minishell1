/*
** list_alias_man.c for minishell1 in /minishell1/srcs/list_manager/list_alias_man.c
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Feb 9, 2015 Feb 9, 2015 2015 Hippolyte Barraud
** Last update Mon Feb  9 21:17:49 2015 Hippolyte Barraud
*/

#include <unistd.h>
#include <stdlib.h>
#include "../../includes/minishell1.h"

void		alias_add_node(t_list **list, char *val, char *start)
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

t_list		*alias_create_list(char **env)
{
  t_list	*root;
  int		i;

  if ((root = malloc(sizeof(*root))) == NULL)
    my_puterror(ERROR_MALLOC);
  root->next = root;
  root->prec = root;
  i = -1;
  while (env[++i])
    alias_add_node(&root, env[i], NULL);
  return (root);
}

void	append_to_wordtab(char **arr, char **append)
{
  int	max;
  char 	**tmp;

  max = 0;
  tmp = arr;
  while (*tmp != NULL)
    {
      max++;
      tmp++;
    }
  while (*append != NULL)
    arr[max++] = *append++;
  arr[max] = NULL;
}

void		alias_display_list(t_list *lst, char type)
{
  t_list	*tmp;

  tmp = lst->next;
  while (tmp != lst)
    {
      write_colored("alias ", GREEN);
      (void)write(1, tmp->data, my_strlen(tmp->data));
      if ((type != 1 && tmp->next != lst) || type == 0)
	(void)write(1, "\n", 1);
      tmp = tmp->next;
    }
}
