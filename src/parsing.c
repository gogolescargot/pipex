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

char	*get_path_line(char **envp)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		str = ft_substr(envp[i], 0, j);
		if (ft_strncmp(str, "PATH", ft_strlen(str)) == 0)
		{
			free(str);
			return (envp[i] + j + 1);
		}
		free(str);
		i++;
	}
	return (NULL);
}

char	*get_path_cmd(char *cmd, char **envp)
{
	char	**all_path;
	char	*path;
	char	*exec;
	int		i;

	i = -1;
	all_path = ft_split(get_path_line(envp), ':');
	while (all_path[++i])
	{
		path = ft_strjoin(all_path[i], "/");
		exec = ft_strjoin(path, cmd);
		free(path);
		if (access(exec, (F_OK | X_OK)) == 0)
		{
			free_array(all_path);
			return (exec);
		}
		free(exec);
	}
	free_array(all_path);
	return (NULL);
}

int	check_path_cmd(char *cmd, char **envp)
{
	char	**all_path;
	char	*path;
	char	*exec;
	int		i;
	bool	status;

	i = -1;
	status = false;
	all_path = ft_split(get_path_line(envp), ':');
	while (all_path[++i])
	{
		path = ft_strjoin(all_path[i], "/");
		exec = ft_strjoin(path, cmd);
		free(path);
		if (access(exec, F_OK) == 0)
		{
			if (access(exec, X_OK) == 0)
			{
				free(exec);
				free_array(all_path);
				return (0);
			}
			else
				status = true;
		}
		free(exec);
	}
	free_array(all_path);
	if (status)
		return (2);
	return (1);
}
