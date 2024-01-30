/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:15:02 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/30 13:32:04 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define BUFFER_SIZE 42
# define PROMPT_HOME "\001\e[34m\002minishell\001\e[0m\002:\001\e[36m\002~"
# define PROMPT_ROOT "\001\e[34m\002minishell\001\e[0m\002:\001\e[36m\002"

/****************************** GLOBAL VARIABLES ******************************/
extern int	g_exit_status;
extern int	g_sigint;
extern int	g_pid;

/********************************* STRUCTURES *********************************/

// enum e_type
// {
// 	command,
// 	file,
// 	limiter
// };

typedef struct s_export
{
	char			*content;
	struct s_export	*next;
}				t_export;

typedef struct s_data
{
	char		*prompt;
	char		**env;
	t_export	*export;
	char		*line;
}				t_data;

// typedef struct s_command
// {
// 	char	*command;
// 	enum	e_type type;
// }			t_command;

char	**split_commands(char *line);

/*********************************** UTILS ************************************/
/* STRINGS */
void		ft_putstr(char *s, int fd);
size_t		ft_strlen(const char *s);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strchr(char const *s, int c);
char		*ft_strdup(char const *src);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char *charset);
int			ft_atoi(const char *s);
char		*ft_itoa(int n);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strclean(char *str, char *charset);
int			count_double_quotes(char *str);
int			is_in_quote(char *str, int pos);
int			ft_quote(int *in_quote, char c);
int			count_single_quotes(char *str);
char		**get_operators_array(char *str);
/* LISTS */
t_export	*lst_new_node(char *content);
void		lst_add_front(t_export **lst, t_export *new);
t_export	*lst_get_last(t_export *lst);
void		lst_add_back(t_export **lst, t_export *new);
/* MEMORY */
void		ft_bzero(void *dest, size_t n);
void		*ft_calloc(size_t n, size_t size);
void		free_double_array(char **array);
void		free_export(t_export **lst);
void		free_all(t_data *data);
/* ERRORS */
void		exit_error(const char *msg);
void		syntax_error_message(char *token_name, int len);
void		redirection_error_message(void);
/* ENV */
char		**cpy_env(char **base_env);
char		*get_pwd(t_data *data);
char		*get_oldpwd(t_data *data);
char		*get_home_path(t_data *data);

/********************************** PARSING ***********************************/
void		in_or_out_quotes(char *line, int *singleq, int *doubleq, int i);
void		new_line_len(t_data *data, int *len,
				int in_singleq, int in_doubleq);
char		*get_dollar_var(t_data *data, int *i, int *j);
int			parse_conditions(char *line, int i, int insq, int indq);
void		parse_spaces(char *line, int *i);
char		*parse_line(char *line, char **env);
void		parse_logic_operators(t_data *data);
/* UNCLOSED QUOTES */
char		*unclosed_quotes(t_data *data);
int			is_unclosed_quotes(t_data *data);
/* WILDCARD */
char		*get_start_path(char *line, int *i);
char		*get_full_start_path(char *start_path, char *end_path, int slash);
char		*get_slash_path(char *start_path, char *end_path);
void		wildcard_len(t_data *data, int *i, int *len);
void		parse_wildcard(char *line, char *new_line, int *i, int *j);

/****************************** EXECUTE COMMANDS ******************************/
void		command_launcher(t_data *data);
int			builtin_launcher(t_data *data);
char		*ft_get_path_env(char **env);
char		*ft_get_path(char *cmd, char **env);
void		ft_fork_exec(char *cmds, char **env);
void		ft_exec(char *cmds, char **env);
/* PWD */
void		refresh_prompt(t_data *data);
void		set_pwd(t_data *data);
void		set_old_pwd(t_data *data, char *path);
void		ft_pwd(void);
/* ECHO */
void		ft_echo(t_data *data);
/* CD */
void		ft_cd(t_data *data);
/* ENV */
void		ft_print_env(t_data *data);
t_export	*convert_env_list(t_data *data);
void		refresh_env(t_data *data, t_export *env);
void		add_env_var(t_data *data, char *var);
/* EXPORT */
void		init_export(t_data *data);
char		*get_var_name(char *export_line, int i);
char		*convert_env_export(char *env_line);
void		sort_export(t_data *data);
void		print_export(t_data *data);
void		ft_export(t_data *data);
/* UNSET */
void		ft_unset(t_data *data);
/* EXIT */
int			is_exit(t_data *data);
void		ft_exit(t_data *data);

/*********************************** PIPES ************************************/
int			ft_open(char *file, int in_out);
void		ft_close(int *pipe_fd);
void		ft_error_exit(int *pipe_fd, const char *msg);
char		*get_next_line(int fd);
void		ft_pipe(char *cmd, t_data *data);

/*********************************** REDIRECTION ******************************/
void		output_redirection(char **cmds, int *index,
				int oflags, t_data *data);
void		input_redirection(char **cmds, int *index, t_data *data);
void		here_doc(char **cmds, int *index, t_data *data);

/************************************ LOGIC OPERATORS ************************/
int			is_logic_operators_broken(char *line);
int			is_open_parentheses(char *line);

/*********************************** SIGNALS *********************************/
void		sigquit_handler(void);
void		signals_handler(int signum);

#endif
