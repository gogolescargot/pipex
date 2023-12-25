/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
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
	pid_t	pid;
	int		fd[2];

	if (argc != 5)
		(handle_error("Bad number of parameters", 1), exit(1));
	if (pipe(fd) < 0)
		(handle_error("Pipe", errno), exit(1));
	pid = fork();
	if (pid < 0)
		(handle_error("Fork", errno), exit(1));
	if (pid == 0)
	{
		file(fd, argv[1], true);
		exec(argv[2], envp);
	}
	waitpid(pid, NULL, 0);
	file(fd, argv[4], false);
	exec(argv[3], envp);
	exit(0);
}
