/*
** main.c for minishell1 in /home/barrau_h/Desktop/minishell1/srcs
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Thu Jan 29 01:07:07 2015 Hippolyte Barraud
** Last update Sun Feb  8 03:39:28 2015 Hippolyte Barraud
*/

#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include "../includes/minishell1.h"

static void	initialize(char *str)
{
  int		i;

  i = -1;
  while (++i <= BUFF)
    str[i] = '\0';
}

void		print_prompt(t_list *env, char change)
{
  char		*pwd;
  char		*user;

  user = get_my_var(env, "USER");
  if (change)
    pwd = get_my_pwd(env);
  else
    pwd = get_my_var(env, "PWD");
  write_colored("(", CYAN);
  if (user != NULL)
    {
      write_colored(user, CYAN);
      write_colored("@", BLUE);
    }
  write_colored(revstr(_get_last_folder(pwd)), CYAN);
  write_colored(") ", CYAN);
}

void	print_prompt_alias()
{
  writetxt("\n\r");
  print_prompt(envptr, (int)*changeptr);
}

static char	signal_process()
{
  if (signal(SIGINT, print_prompt_alias) == SIG_ERR)
    my_puterror(ERROR_SIGNAL);
  writetxt("\r");
  print_prompt(envptr, (int)*changeptr);
  return (0);
}

int		main(int argc, char **argv, char **env)
{
  char		buff[BUFF + 1];
  t_list	*lst;
  int		len;
  int		ret;

  print_header(argc, argv);
  changeptr = &ret;
  lst = create_list(env);
  init_env(lst);
  initialize(&buff[0]);
  ret = signal_process();
  while ((len = read(0, buff, BUFF)) > 0)
    {
      if (len == BUFF)
    	my_puterror(ERROR_CMD_TOO_LONG);
      buff[len != 0 ? len - 1 : len] = '\0';
      ret = cmd_interpret(buff, lst);
      (void)signal_process();
      initialize(&buff[0]);
    }
  return (len == -1 ? EXIT_FAILURE : EXIT_SUCCESS);
}
