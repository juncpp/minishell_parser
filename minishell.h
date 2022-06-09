#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

# define SEP 0
# define WORD 1
# define FIELD 2
# define EXP_FIELD 3
# define REDIR_OUT 4
# define REDIR_IN 5
# define REDIR_APPEND 6
# define REDIR_INSOLUSION 7
# define PIPE 8

extern char **environ;

# define NOTMALLOC -1


typedef struct s_list
{
	char			*key;
	char			*value;
	struct s_list	*next;
}	t_list;

typedef struct s_token
{
	int				token;
	struct s_token	*next;
}	t_token;

typedef	struct s_command
{
	char				*str;
	int					flag;
	struct s_command	*next;
}	t_command;

typedef	struct s_errors
{
	int	flag;
	int	error;
}	t_errors;

// typedef int (*t_builtin_ptr)(t_list *list, struct s_info *info);

typedef struct s_info
{
	char			*res_word[7];	// ключевые слова
	char			**envp;     	// переменная окружения
	t_list			*envp_list;		// переменная окружения в листe
	t_token			*token;			// лист токенов
	int				envp_f;			// флаг на изменение envp. изменяется, если зменился envp_list
	int				exit_f;			// флаг на выход из программы
	int				status;			// когда вызываем $?
}	t_info;

//typedef int (*t_builtin_ptr)(t_list *list, struct s_info *info);
//
//t_builtin_ptr	builtins[7];

// typedef int (*t_builtin_ptr)(t_list *list, struct s_info *info);

// t_builtin_ptr	builtins[7];	// массив функций ключевых слов

int			ft_strlen(char *str);
int			mem_lists(t_list **envp_list, char *str);
char		*key_value_cpy(char *dest, char *src, int flag);
int			key_value_mem(char *str, int flag);
int			start_lists(t_list **envp_list, char **envp);
void		print_error(t_info *info, int flag);
void		*ft_free_list(t_list **envp_list);
void		**ft_free_array(char **envp);
int			init(t_info *info, char **env);
void		ft_strcopy(char *dest, char *src);
void		free_token(t_token **token);
void		ft_free_command(t_command **command);

int			lexer(t_info *info, char *line);
void		all_free(t_info *info, int flag, t_command **command);
int			is_token(char c);
int			check_fields(t_token **token);
int			skip_field(t_token **token, int x);
int			sub_check(int token, char *p, int *i);

int			parser_next(t_command **command, t_info *info);
int			is_not_word(int x);
char		**parser(t_command **command);
int			all_check(t_info *info, char *p);
int 		count_status(int status);
void		ft_itoa(char *dst, int status, int *j);
int			is_not_word(int x);
int			ft_strcmp_v2(char *cmp, char *str);

char		*check_env_var(t_list *envp_list, char *str);
char		*ft_copy(char *dst, char *src, char *env);
int			run_str(int token, char *p, t_command **command, int *i);
#endif