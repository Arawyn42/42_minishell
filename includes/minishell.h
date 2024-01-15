/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:15:02 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/15 18:34:40 by nsalles          ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>

# define BUFFER_SIZE 42

/********************************* STRUCTURES *********************************/
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
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strclean(char *str, char *charset);
int			count_double_quotes(char *str);
int			count_single_quotes(char *str);
char		**get_operators_array(char *str);
void		input_handler(t_data *data);
/* LISTS */
t_export	*lst_new_node(char *content);
void		lst_add_front(t_export **lst, t_export *new);
t_export	*lst_get_last(t_export *lst);
void		lst_add_back(t_export **lst, t_export *new);
/* MEMORY */
void		*ft_calloc(size_t n, size_t size);
void		free_double_array(char **array);
void		free_export(t_export **lst);
void		free_all(t_data *data);
/* ERRORS */
void		exit_error(const char *msg);
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

/****************************** EXECUTE COMMANDS ******************************/
int			builtin_launcher(t_data *data);
char		*ft_get_path_env(char **env);
char		*ft_get_path(char *cmd, char **env);
void		ft_fork_exec(char *cmds, char **env);
void		ft_exec(char *cmds, char **env);
/* PWD */
void		refresh_prompt(t_data *data);
void		set_pwd(t_data *data);
void		set_old_pwd(t_data *data);
void		ft_pwd(void);
/* ECHO */
void		ft_echo(t_data *data);
/* CD */
void		ft_cd(t_data *data);
/* ENV */
void		ft_print_env(t_data *data);
/* EXPORT */
void		init_export(t_data *data);
char		*convert_env_export(char *env_line);
void		sort_export(t_data *data);
void		print_export(t_data *data);
void		ft_export(t_data *data);
/* EXIT */
void		ft_exit(t_data *data);

/*********************************** PIPES ************************************/
int			ft_open(char *file, int in_out);
void		ft_close(int *pipe_fd);
void		ft_error_exit(int *pipe_fd, const char *msg);
char		*get_next_line(int fd);
void		ft_pipe(char *cmd, t_data *data);

/*********************************** REDIRECTION ******************************/
void		output_redirection(char **cmds, int *index, int oflags, t_data *data);
void		input_redirection(char **cmds, int *index, t_data *data);
void		here_doc(char **cmds, int *index, t_data *data);

#endif