/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adconsta <adconsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:51:20 by adconsta          #+#    #+#             */
/*   Updated: 2021/01/28 15:49:41 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# define BUFFER_SIZE 32

int		get_next_line(int fd, char **line);
char	*ft_gnljoin(char *storage, char *s2);
void	ft_strncpy(char *dest, char *src, int n);
int		look_for_newline(char *str);

#endif
