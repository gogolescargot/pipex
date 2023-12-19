/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:59:46 by ggalon            #+#    #+#             */
/*   Updated: 2023/12/14 17:59:46 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

bool	exec_command(int *fd, char *s, char **envp)
{
	char	*args[3];

	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	args[0] = "/bin/which";
	args[1] = s;
	args[2] = NULL;
	if (access(args[0], F_OK) == -1)
	{
		perror("No such file or directory");
		return (false);
	}
	else if (access(args[0], X_OK) == -1)
	{
		perror("Permission denied");
		return (false);
	}
	execve(args[0], args, envp);
	perror("Exec");
	exit(127);
}

char	*get_command(char *s, char **envp)
{
	int		fd[2];
	char	*line;
	pid_t	pid1;

	if (pipe(fd) == -1)
		return (NULL);
	pid1 = fork();
	if (pid1 < 0)
		return (NULL);
	if (pid1 == 0 && exec_command(fd, s, envp) == false)
		return (NULL);
	close(fd[1]);
	line = get_next_line(fd[0]);
	get_next_line(-1);
	close(fd[0]);
	if (!line || !line[0])
		return (NULL);
	return (line[ft_strlen(line) - 1] = 0, line);
}

void	print_output(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_printf("%s", line);
		free(line);
	}
	get_next_line(-1);
}
