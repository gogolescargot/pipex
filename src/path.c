/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
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
	while (envp && envp[i])
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
	while (all_path && all_path[++i])
	{
		path = ft_strjoin(all_path[i], "/");
		exec = ft_strjoin(path, cmd);
		free(path);
		if (access(exec, (F_OK | X_OK)) == 0)
		{
			ft_arrayclear(all_path);
			return (exec);
		}
		free(exec);
	}
	ft_arrayclear(all_path);
	return (NULL);
}

int	check_path_cmd_utils(char **exec, char **a_p, int ret_v, bool st)
{
	ft_arrayclear(a_p);
	if (ret_v == -1)
	{
		if (st)
			return (2);
		return (1);
	}
	free(*exec);
	return (ret_v);
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
	while (all_path && all_path[++i])
	{
		path = ft_strjoin(all_path[i], "/");
		exec = ft_strjoin(path, cmd);
		free(path);
		if (!ft_strncmp(cmd, ".", 2) || !ft_strncmp(cmd, "..", 3))
			return (check_path_cmd_utils(&exec, all_path, 1, false));
		if (access(exec, (F_OK | X_OK)) == 0)
			return (check_path_cmd_utils(&exec, all_path, 0, false));
		else if (access(exec, F_OK) == 0)
			status = true;
		free(exec);
	}
	return (check_path_cmd_utils(NULL, all_path, -1, status));
}

bool	check_folder(char *path)
{
	int	fd;

	fd = open(path, O_WRONLY);
	if (errno == 21)
	{
		if (fd != -1)
			close(fd);
		return (true);
	}
	if (fd != -1)
		close(fd);
	return (false);
}
