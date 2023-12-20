/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:57:23 by ggalon            #+#    #+#             */
/*   Updated: 2023/12/18 18:57:23 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	child_process(int *fd, char **argv, char **envp)
{
	int	input_file;

	input_file = open(argv[1], O_RDONLY);
	if (input_file < 0)
		(handle_error(argv[1], errno), close(fd[0]), close(fd[1]), exit(1));
	dup2(input_file, STDIN_FILENO);
	close(input_file);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	if (access(argv[1], F_OK) == -1)
		(handle_error(argv[1], 2), exit(1));
	else if (access(argv[1], R_OK) == -1)
		(handle_error(argv[1], 13), exit(1));
	exec_child(argv, envp);
}

void	parent_process(int *fd, char **argv, char **envp)
{
	int	output_file;

	output_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (output_file < 0)
		(handle_error(argv[4], errno), close(fd[0]), close(fd[1]), exit(1));
	dup2(output_file, STDOUT_FILENO);
	close(output_file);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	exec_parent(argv, envp);
}
