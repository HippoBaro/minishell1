/*
** my_str1.c for minishell1 in /home/barrau_h/Desktop/minishell1/srcs/strlib
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Thu Jan 29 01:00:18 2015 Hippolyte Barraud
** Last update Thu Jan 29 01:00:38 2015 Hippolyte Barraud
*/

#include <stdlib.h>
#include "../../includes/minishell1.h"

char	my_strcmp(const char *s1, const char *s2, char equal)
{
  int	i;

  i = -1;
  while (s1[++i] && s2[i] && s1[i] == s2[i]);
  if (equal)
    return (s1[i] == '=' && s2[i] == '\0');
  return ((s1[i] == s2[i] || s1[i] == ' ' || s1[i] == '\t') && s2[i] == '\0');
}

int	my_strlen(const char *str)
{
  int	i;

  i = -1;
  if (str == NULL)
    return (0);
  while (str[++i]);
  return (i);
}

char    *my_strdup(const char *str)
{
  int   i;
  char  *cpy;

  if ((cpy = malloc(sizeof(char) * my_strlen(str) + 1)) == NULL)
    my_puterror(ERROR_MALLOC);
  i = 0;
  while (str[i])
    {
      cpy[i] = str[i];
      ++i;
    }
  cpy[i] = '\0';
  return (cpy);
}

char	*my_strcat(char *dest, const char *src)
{
  int	i;
  int	j;

  i = my_strlen(dest);
  j = -1;
  while (src[++j])
    {
      dest[i] = src[j];
      ++i;
    }
  dest[i] = '\0';
  return (dest);
}
