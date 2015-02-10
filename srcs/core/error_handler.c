/*
** my_error.c for minishell1 in /home/barrau_h/Desktop/minishell1/srcs/core
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Thu Jan 29 01:04:20 2015 Hippolyte Barraud
** Last update Thu Jan 29 01:04:38 2015 Hippolyte Barraud
*/

#include <unistd.h>
#include <stdlib.h>
#include "../../includes/minishell1.h"

void	my_puterror(const char *error)
{
  write_colored(error, RED);
  exit(EXIT_FAILURE);
}

void	my_error(const char *error, const char *var)
{
  (void)write(2, var, my_strlen(var));
  (void)write(2, ": ", 3);
  (void)write(2, error, my_strlen(error));
}

char	my_env_error(char *env, char type, int pos)
{
  if (type == 0)
    {
      writetxt(ERROR_ENV_INVALIDARG);
      (void)write(2, env, my_strlen(env));
      (void)write(2, "'", 1);
    }
  else if (type == 1)
    {
      writetxt(ERROR_ENV_INVALIDARG);
      (void)write(2, &env[pos], 1);
      (void)write(2, "'", 1);
    }
  else if (type == 2)
    writetxt(ERROR_ENV_MIS_ARG);
  else
    writetxt(ERROR_ENV_UNVALID_ARG);
  if (type != 3)
    writetxt(ERROR_UNKNOW_ARG);
  return (-1);
}

char	print_unknow_cmd(char *cmd)
{
  writetxt(UNKNOW_CMD_MESSAGE1);
  (void)write(2, cmd, my_strlen(cmd));
  writetxt(UNKNOW_CMD_MESSAGE2);
  writetxt(UNKNOW_CMD_MESSAGE3);
  (void)write(2, cmd, my_strlen(cmd));
  (void)write(2, "\n", 1);
  exit(EXIT_SUCCESS);
}
