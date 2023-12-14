/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:22:49 by ggalon            #+#    #+#             */
/*   Updated: 2023/12/14 15:22:49 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int main(int argc, char **argv)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	(void)argc;
	(void)argv;

	if (pipe(fd) < 0)
		return (1);

	pid1 = fork();
	if (pid1 < 0)
		return (1);
	if (pid1 == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		char *cat_args[] = {get_command(argv[2]), argv[1], NULL};
		execve(get_command(argv[2]), cat_args, NULL);
	}

	// ft_printf("%s - %s", get_command("/bin/cat -e"), get_param("/bin/cat -e"));

	pid2 = fork();
	if (pid2 < 0)
		return (1);
	if (pid2 == 0)
	{
		int output_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC);
		dup2(output_file, 1);
		close(output_file);
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		char *grep_args[] = {get_command(argv[3]), get_param(argv[3]), NULL};
		execve(get_command(argv[3]), grep_args, NULL);
	}
	
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return (0);
}
