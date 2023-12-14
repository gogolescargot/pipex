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

char	*ft_strndup(char *src, size_t start, size_t end)
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

char	*get_command(char *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	while (s[i + j] && s[i + j] != 32 && (s[i + j] < 9 || s[i + j] > 13))
		j++;
	return (ft_strndup(s, i, i + j));
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