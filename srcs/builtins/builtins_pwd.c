/*
** my_pwd.c for minishell1 in /home/barrau_h/Desktop/minishell1/srcs/core
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Thu Jan 29 01:02:42 2015 Hippolyte Barraud
** Last update Thu Jan 29 01:03:01 2015 Hippolyte Barraud
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include "../../includes/minishell1.h"

static char		*try_find_dir(DIR *dir, struct stat *cur)
{
  struct dirent		*dirent;
  struct stat		tmp;
  int			found;
  char			*foundDir;

  found = 0;
  while (!found && (dirent = readdir(dir)) != NULL)
    {
      if (lstat(dirent->d_name, &tmp) != 0)
	my_puterror(ERROR_LSTAT);
      if ((tmp.st_dev == cur->st_dev) && (tmp.st_ino == cur->st_ino))
	found = 1;
    }
  if ((foundDir = my_strdup(dirent->d_name)) == NULL)
    my_puterror(ERROR_MALLOC);
  if (closedir(dir) == -1)
    my_puterror(ERROR_CLOSEDIR);
  if (!found)
    my_puterror(ERROR_PWD);
  return (foundDir);
}

static DIR	*init_dirstruct(struct stat *cur, struct stat *parent)
{
  DIR		*dir;

  if (lstat(".", cur) != 0)
    my_puterror(ERROR_LSTAT);
  chdir("..");
  if (lstat(".", parent) != 0)
    my_puterror(ERROR_LSTAT);
  if (!(dir = opendir(".")))
    my_puterror(ERROR_OPENDIR);
  return (dir);
}

static char	*get_new_strdir(char *foundDir, char *curDir)
{
  int		len;
  int		len2;

  len = my_strlen(curDir);
  if (len != 1)
    curDir = my_strcat(curDir, "/");
  if (foundDir)
    {
      len2 = my_strlen(foundDir);
      if ((len + len2 + 1) > 256)
	my_puterror(ERROR_PATH_TOO_LONG);
      curDir = my_strcat(curDir, foundDir);
      free(foundDir);
    }
  return (curDir);
}

static char	*get_pwd()
{
  struct stat	cur;
  struct stat	parent;
  DIR		*dir;
  char		*curDir;
  char		*foundDir;

  dir = init_dirstruct(&cur, &parent);
  if ((cur.st_dev == parent.st_dev) && (cur.st_ino == parent.st_ino))
    {
      if ((curDir = malloc(sizeof(char) * 256)) == NULL)
	my_puterror(ERROR_MALLOC);
      curDir[0] = '\0';
      foundDir = NULL;
    }
  else
    {
      foundDir = try_find_dir(dir, &cur);
      curDir = get_pwd();
    }
  return (get_new_strdir(foundDir, curDir));
}

char	*my_pwd()
{
  char	*pwd;

  pwd = get_pwd();
  if (chdir(pwd) == -1)
    my_error(ERROR_404, "error");
  return (pwd);
}
