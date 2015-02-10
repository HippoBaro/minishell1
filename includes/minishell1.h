/*
** minishell1.h for minishell1 in /home/barrau_h/Desktop/minishell1/includes
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Thu Jan 29 01:08:00 2015 Hippolyte Barraud
** Last update Mon Feb  9 21:24:02 2015 Hippolyte Barraud
*/

#ifndef		MINISHELL1_H_
# define	MINISHELL1_H_

#include "my_str_to_wordtab.h"

/*
** If enabled, will try to clear the console at start.
** Deactivated by default.
*/
# define ENABLE_CLAR_CONSOLE	1

# define ERROR_SIGNAL		"Error sending signal !\n"
# define ERROR_CMD_TOO_LONG	"Error : command too long.\n"
# define ERROR_PATH_TOO_LONG	"Error : path exceed 255 characters.\n"
# define ERROR_HEADER_MISSING	"Unable to locate/open header file !\n"
# define ERROR_BASHRC_MISSING	"Unable to locate/open .bashrc file !\n"
# define ERROR_MALLOC		"Error trying to malloc memory segment.\n"
# define ERROR_FORK		"Unable to fork process.\n"
# define ERROR_ENV_INVALIDARG	"Invalid param --"
# define ERROR_ENV_MIS_ARG	"Missing param for option -- 'u'.\n"
# define ERROR_ENV_UNVALID_ARG	"Error : unvalid argument for env.\n"
# define ERROR_UNKNOW_ARG	" Unknow option.\n"
# define ERROR_404		"No such file or directory : "
# define ERROR_ACCES_DENIED	"Permission denied : "
# define ERROR_DIR_LOCKED	"Acces to this directory is restricted.\n"
# define ERROR_LSTAT		"Error while retriving metadata using lstat.\n"
# define ERROR_CLOSEDIR		"Error while trying to close folder.\n"
# define ERROR_PWD		"Error : Unable to find the current \
directory.\n"
# define ERROR_OPENDIR		"Error while trying to open directory.\n"

# define CD_USAGE		"Usage : cd [directory]. Example : cd .\n"
# define SETENV_USAGE		"Usage : setenv [variable] [value].\n"
# define UNSETENV_USAGE		"Usage : unsetenv [variable].\n"

# define GOODBYE		"Goodbye. You'll be back soon enough.\n"

# define UNKNOW_CMD_MESSAGE1	"If '"
# define UNKNOW_CMD_MESSAGE2	"' is not a typo you can use \
command-not-found to lookup"
# define UNKNOW_CMD_MESSAGE3	" the package that contains it, like \
this:\n\tcnf "

# define BUFF			512

# define RED			"\033[1;31m"
# define GREEN			"\033[1;32m"
# define CYAN			"\033[1;36m"
# define BLUE			"\033[1;34m"
# define YELLOW			"\033[1;33m"

# define PATH			"/bin:/sbin:/usr/bin:/usr/sbin"
# define ENV			"/usr/bin/env"

# define ID_IGNORE		0
# define ID_NULL		1
# define ID_UN			2
# define ID_HELP		3
# define ID_VER			4

# define UNSET(c)		(c != '\0' && c != '\'')

typedef struct			s_list
{
  char				*data;
  struct s_list			*next;
  struct s_list			*prec;
}				t_list;

t_list				*envptr;
int				*changeptr;

void		add_node(t_list **list, char *val, char *start);
t_list		*create_list(char **env);
void		remove_node(t_list **lst, char *value);
void		display_list(t_list *lst, char type);
char		*find_element(t_list *lst, char *value);
void		set_env_list(t_list *lst, char *var, char *value);

char		my_exit(t_list *env, char **arr);
int		my_cd(char **arr);
void		my_setenv(t_list *env, char **arr);
void		my_unsetenv(t_list *env, char **arr);
void		my_env(t_list *env, char **options);

char		my_strcmp(const char *s1, const char *s2, char equal);
int		my_strlen(const char *str);
char		*my_strdup(const char *str);
char		*my_strcat(char *dest, const char *src);
char		*revstr(char *s);
char		*_get_last_folder(char *URI);

char		*get_my_var(t_list *env, char *code);
char		*get_my_pwd(t_list *env);
void		init_env(t_list *lst);

char		*my_pwd();

void		my_alias(t_list *env);

void		write_colored(const char *str, const char *color);
void		writetxt(const char *str);

void		free_array(char **arr);
void		free_list(t_list *list);

char		execute_command(t_list *env, char **exec_opt, char *path);

void		my_puterror(const char *error);
void		my_error(const char *error, const char *var);
char		my_env_error(char *env, char type, int pos);
char		print_unknow_cmd(char *cmd);

char		my_env_opt(t_list *env, char **var);

int		cmd_interpret(char *str, t_list *env);

void		print_header(int argc, char **argv);

char		*concat_path(char *path, char *exec);
void		apply_alias(char **arr, t_list *env);
t_list		*alias_create_list(char **env);
void		alias_display_list(t_list *lst, char type);
void		append_to_wordtab(char **arr, char **append);

#endif		/* !MINISHELL1_H_ */
