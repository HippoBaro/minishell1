/*
** my_str2.c for minishell1 in /home/barrau_h/Desktop/minishell1/srcs/strlib
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Thu Jan 29 01:00:01 2015 Hippolyte Barraud
** Last update Mon Feb  9 21:21:25 2015 Hippolyte Barraud
*/

#include "../../includes/minishell1.h"

char		*revstr(char *s)
{
  char		*i1;
  char		*i2;
  char		*m;
  int		len;
  char		c;

  len = my_strlen(s);
  i1 = s;
  i2 = i1 + len - 1;
  m = i1 + len / 2;
  while (i1 < m)
    {
      c = *i1;
      *i1++ = *i2;
      *i2-- = c;
    }
  return (s);
}

char		*_get_last_folder(char *URI)
{
  int		len;
  int		i;
  int		o;
  static char	out[BUFF];

  len = my_strlen(URI);
  i = len - 1;
  o = 0;
  while (i >= 0)
    {
      if (URI[i] == '/')
	break;
      else
	out[o++] = URI[i];
      i--;
    }
  out[o] = '\0';
  return ((char*)&out);
}
