/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 03:38:40 by ggalon            #+#    #+#             */
/*   Updated: 2023/12/22 03:38:40 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	put_here_doc(char *limiter, int *fd)
{
	char	*line;

	close(fd[0]);
	while (1)
	{
		line = get_next_line(0);
		if (!ft_strncmp(line, limiter, ft_strlen(limiter))
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			exit(0);
		}
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
}

void	here_doc(char **argv)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) < 0)
		(handle_error("Pipe", errno), exit(1));
	pid = fork();
	if (pid < 0)
		(handle_error("Fork", errno), exit(1));
	if (pid == 0)
		put_here_doc(argv[2], fd);
	else
	{
		dup2(fd[0], 0);
		waitpid(pid, NULL, 0);
		close(fd[0]);
		close(fd[1]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	state;

	state = 1;
	if (argc < 5)
		(handle_error("Bad number of parameters", 1), exit(1));
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		i = 3;
		if (argc < 6)
			(handle_error("Bad number of parameters", 1), exit(1));
		state = 2;
		here_doc(argv);
	}
	else
		i = 2;
	pipex_bonus(argv[i], envp, argv[1], state * -1);
	while (++i < argc - 2)
		pipex_bonus(argv[i], envp, argv[1], 0);
	pipex_bonus(argv[argc - 2], envp, argv[argc - 1], state);
	exit(0);
}
