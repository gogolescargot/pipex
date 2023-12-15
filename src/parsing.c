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

static char	*ft_strndup(char *src, size_t start, size_t end)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc((end - start + 1) * sizeof(char));
	if (!dest || !src)
		return (NULL);
	while (src[start] && start < end)
	{
		dest[i] = src[start];
		i++;
		start++;
	}
	dest[i] = 0;
	return (dest);
}

char* get_command(char *s)
{
	int		fd[2];
	char	*line;
	pid_t	pid1;

	if (pipe(fd) == -1)
		return (NULL);
	pid1 = fork();
	if (pid1 < 0)
		return (NULL);
	if (pid1 == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		char* args[] = {"/bin/which", s, NULL};
		execve(args[0], args, NULL);
		perror("Exec");
		exit(1);
    }
	else
	{
		close(fd[1]);
		line = get_next_line(fd[0]);
		get_next_line(-1);
		close(fd[0]);
		waitpid(pid1, NULL, 0);
    }
	if (!line || !line[0])
		return (NULL);
	line[ft_strlen(line) - 1] = 0;
	if (access(line, (F_OK | X_OK)) < 0)
		return (free(line), NULL);
    return (line);
}

char	*get_param(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	while (s[i] && s[i] != 32 && (s[i] < 9 || s[i] > 13))
		i++;
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	return (ft_strndup(s, i, ft_strlen(s)));
}