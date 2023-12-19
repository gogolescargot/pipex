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

void	input_fd(int *fd, char **argv)
{
	int	input_file;

	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	if (access(argv[1], F_OK) == -1)
		(perror("No such file or directory"), exit(1));
	else if (access(argv[1], R_OK) == -1)
		(perror("Permission denied"), exit(1));
	input_file = open(argv[1], O_RDONLY);
	if (input_file < 0)
		(perror("Error Open"), exit(1));
	dup2(input_file, 0);
	close(input_file);
}

void	output_fd(int *fd, char **argv)
{
	int	output_file;

	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
	if (access(argv[1], F_OK) == -1)
		(perror("No such file or directory"), exit(1));
	else if (access(argv[1], R_OK) == -1)
		(perror("Permission denied"), exit(1));
	output_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC);
	if (output_file < 0)
		(perror("Output file"), exit(1));
	dup2(output_file, 1);
	close(output_file);
}
