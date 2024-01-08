/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_old.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:49:18 by drenassi          #+#    #+#             */
/*   Updated: 2024/01/05 18:40:23 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/****************************** Full process ********************************/
/* 1. Check if there is a here_doc or not.									*/
/* 2. If there is a here_doc, open the output file and call ft_here_doc.	*/
/* 3. Else, open the input and the output files and duplicate the input 	*/
/*	  file on the standard input.											*/
/* 4. Call the ft_pipe function, which will operate all the pipes.			*/
/* 5. Duplicate the output file on the standard output.						*/
/****************************************************************************/
// static void	ft_process(int ac, char **av, char **env)
// {
// 	int		input_fd;
// 	int		output_fd;
// 	int		i;

// 	if (!ft_strcmp(av[1], "here_doc"))
// 	{
// 		i = 3;
// 		output_fd = ft_open(av[ac - 1], -STDOUT_FILENO);
// 		ft_here_doc(ac, av);
// 	}
// 	else
// 	{
// 		i = 2;
// 		input_fd = ft_open(av[1], STDIN_FILENO);
// 		output_fd = ft_open(av[ac - 1], STDOUT_FILENO);
// 		dup2(input_fd, STDIN_FILENO);
// 		close(input_fd);
// 	}
// 	while (i < ac - 2)
// 		ft_pipe(av[i++], env);
// 	dup2(output_fd, STDOUT_FILENO);
// 	close(output_fd);
// 	if (!ft_exec(av[ac - 2], env))
//		exit(EXIT_FAILURE);
//	exit(EXIT_SUCCESS);
// }

/****************************** Main function *******************************/
/* 1. Check if there are enough arguments.									*/
/* 2. Create a pipe array: pipe_fd[0] = Write end ; pipe_fd[1] = Read end.	*/
/* 3. Create a child process with fork.										*/
/* 4. If pid = 0, we're in the child process.								*/
/* 5. If pid > 0, we're in the parent process.								*/
/****************************************************************************/
// int	main(int ac, char **av, char **env)
// {
// 	if (ac < 5)
// 	{
// 		ft_putstr("Too few parameters. ", STDERR_FILENO);
// 		ft_putstr("Usage: ./pipex file1 cmd1 ... cmdN file2\n", STDERR_FILENO);
// 		exit(EXIT_SUCCESS);
// 	}
// 	ft_process(ac, av, env);
// 	return (0);
// }
