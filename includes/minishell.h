/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:15:02 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/08 18:11:39 by nsalles          ###   ########.fr       */
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
typedef struct s_data
{
	char	**env;
	char	*line;
}			t_data;

/*********************************** UTILS ************************************/
/* STRINGS UTILS */
void	ft_putstr(char *s, int fd);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(char const *s, int c);
char	*ft_strdup(char const *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char *charset);
int		count_double_quotes(char *str);
int		count_single_quotes(char *str);
int		ft_is_operator(char c);
void	input_handler(t_data *data);
/* MEMORY UTILS */
void	*ft_calloc(size_t n, size_t size);
void	free_double_array(char **array);
/* ERRORS */
void	exit_error(const char *msg);

/********************************** PARSING ***********************************/
void	in_or_out_quotes(char *line, int *singleq, int *doubleq, int i);
void	new_line_len(t_data *data, int *len);
char 	*get_dollar_var(t_data *data, int *i, int *j);
int		parse_conditions(char *line, int i, int insq, int indq);
void	parse_line(t_data *data);

/****************************** EXECUTE COMMANDS ******************************/
void	command_launcher(t_data *data);
char	*ft_get_path_env(char **env);
char	*ft_get_path(char *cmd, char **env);
void	ft_exec(char *cmds, char **env);
/* ECHO */
void	echo(t_data *data);
/* CD */
void	cd(t_data *data);
/* EXIT */
void	ft_exit(t_data *data);

/*********************************** PIPES ************************************/
int		ft_open(char *file, int in_out);
void	ft_close(int *pipe_fd);
void	ft_error_exit(int *pipe_fd, const char *msg);
void	ft_here_doc(int ac, char **av);
char	*get_next_line(int fd);

#endif