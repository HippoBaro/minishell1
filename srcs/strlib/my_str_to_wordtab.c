/*
** my_str_to_wordtab.c for my_str_to_wrdtab in /home/barrau_h/Desktop/minishell1/srcs/strlib
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Thu Jan 29 00:59:22 2015 Hippolyte Barraud
** Last update Sun Feb  8 03:45:57 2015 Hippolyte Barraud
*/

#include <stdlib.h>
#include "../../includes/minishell1.h"

static int	_my_strlen(const char *str, char end, char end1)
{
  int		i;

  i = -1;
  while (str[++i] && str[i] != end && str[i] != end1);
  return (i);
}

static int	_my_nbr_words(const char *str, char end, char end1)
{
  int		i;
  int		count;

  i = 0;
  count = 0;
  while (str[i] != '\0')
    {
      while (str[i] && (str[i] == end || str[i] == end1))
	++i;
      count = (str[i] && str[i] != end && str[i] != end1) ? count + 1 : count;
      while (str[i] && str[i] != end && str[i] != end1)
	++i;
      i = str[i] == '\0' ? i : i + 1;
    }
  return (count);
}

static int	_my_strdup(char *cpy, const char *src, char end, char end1)
{
  int		i;
  int		j;

  i = -1;
  j = 0;
  while (src[j] && (src[j] == end || src[j] == end1))
    ++j;
  while (src[j] && src[j] != end && src[j] != end1)
    {
      cpy[++i] = src[j];
      j++;
    }
  cpy[++i] = '\0';
  return (j);
}

char	**my_str_to_wordtab(char *path, char end, char end1)
{
  char	**array;
  int	size;
  int	i;
  int	j;

  size = _my_nbr_words(path, end, end1);
  if (size == 0)
    return (NULL);
  if ((array = malloc(sizeof(char *) * (99))) == NULL)
    my_puterror(ERROR_MALLOC);
  i = 0;
  j = -1;
  while (path[i])
    {
      if ((array[++j] = malloc(sizeof(char) * _my_strlen(&path[i], end, end1)))
	  == NULL)
	my_puterror(ERROR_MALLOC);
      i += _my_strdup(array[j], &path[i], end, end1);
      i = (path[i] == '\0') ? i : i + 1;
    }
  array[++j] = NULL;
  return (array);
}
