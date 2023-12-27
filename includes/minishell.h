/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:15:02 by drenassi          #+#    #+#             */
/*   Updated: 2023/12/27 23:35:27 by drenassi         ###   ########.fr       */
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

/*********************************** UTILS ************************************/
/* STRINGS UTILS */
void	ft_putstr(char *s, int fd);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(char const *s, int c);
char	*ft_strdup(char const *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(const char *s, char c);
/* MEMORY UTILS */
void	*ft_calloc(size_t n, size_t size);
/* ERRORS */
void	exit_error(const char *msg);

/****************************** EXECUTE COMMANDS ******************************/
char	*ft_get_path_env(char **env);
char	*ft_get_path(char *cmd, char **env);
void	ft_exec(char *cmds, char **env);

/*********************************** PIPES ************************************/
int		ft_open(char *file, int in_out);
void	ft_close(int *pipe_fd);
int		ft_quotes(const char c, int *quotes);
void	ft_error_exit(int *pipe_fd, const char *msg);
void	ft_free(char **array);
void	ft_here_doc(int ac, char **av);
void	ft_pipe(char *cmd, char **env);
char	*get_next_line(int fd);

#endif