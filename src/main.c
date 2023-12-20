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

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status2;
	int		fd[2];

	if (argc != 5)
		(handle_error("Bad number of parameters", 1), exit(1));
	if (pipe(fd) < 0)
		(handle_error("Pipe", errno), exit(1));
	pid1 = fork();
	if (pid1 < 0)
		(handle_error("Fork", errno), exit(1));
	if (pid1 == 0)
		child_process(fd, argv, envp);
	pid2 = fork();
	if (pid2 < 0)
		(handle_error("Fork", errno), exit(1));
	if (pid2 == 0)
		parent_process(fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status2, 0);
	exit(WEXITSTATUS(status2));
}
