/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adconsta <adconsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:51:20 by adconsta          #+#    #+#             */
/*   Updated: 2021/03/13 12:00:43 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

int		get_next_line(int fd, char **line, char **security);
int		ft_gnlstrlen(char *str);
void	ft_gnlstrncpy(char *dest, char *src, int n);
char	*ft_gnlstrjoin(char *storage, char *s2);
char	*ft_gnlstrdup(char *str);
int		look_for_newline(char *str);
int		read_file(char **storage, char **line, char *buf, int fd);
char	*ft_update_storage(char *storage);
char	*ft_make_line(char *storage);

#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif
