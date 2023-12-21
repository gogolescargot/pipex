/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:16:19 by ggalon            #+#    #+#             */
/*   Updated: 2023/12/19 20:16:19 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	handle_error(char *str, int exit_code)
{
	if (exit_code == -1)
	{
		str = ft_strjoin(str, ": Command not found\n");
		ft_putstr_fd(str, 2);
		free(str);
	}
	else
	{
		errno = exit_code;
		perror(str);
	}
}

void	free_array(char **array)
{
	size_t	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
