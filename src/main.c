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
	int	fd[2];
	int	pid1;

	if (argc != 5)
		(perror("Bad number of parameters"), exit(1));
	if (pipe(fd) < 0)
		(perror("Pipe"), exit(1));
	pid1 = fork();
	if (pid1 < 0)
		(perror("Fork"), exit(1));
	if (pid1 == 0)
	{
		input_fd(fd, argv);
		exec_child(argv, envp);
	}
	output_fd(fd, argv);
	exec_parent(argv, envp);
	close(fd[0]);
	exit(0);
}
