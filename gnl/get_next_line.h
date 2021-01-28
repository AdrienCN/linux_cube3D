/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adconsta <adconsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:51:20 by adconsta          #+#    #+#             */
/*   Updated: 2021/01/26 12:08:52 by adconsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

int		get_next_line(int fd, char **line);
int		ft_strlen(char *str);
void	ft_strncpy(char *dest, char *src, int n);
char	*ft_strjoin(char *storage, char *s2);
char	*ft_strdup(char *str);
int		look_for_newline(char *str);

#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif
