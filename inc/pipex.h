/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalon <ggalon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:22:58 by ggalon            #+#    #+#             */
/*   Updated: 2023/12/14 15:22:58 by ggalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/inc/libft.h"

char	*get_command(char *s);
char	*get_param(char *s);
void	free_array(char **array);

#endif