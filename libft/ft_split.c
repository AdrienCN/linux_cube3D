/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adconsta <adconsta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:19:25 by adconsta          #+#    #+#             */
/*   Updated: 2020/11/22 15:11:39 by adconsta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_word_count(char const *str, char c)
{
	int i;
	int	word_count;

	i = 0;
	word_count = 0;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			word_count++;
		i++;
	}
	return (word_count);
}

static	void	ft_free_split(char **tab, int word_count)
{
	int i;

	i = 0;
	while (i < word_count)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static	int		ft_word_size(char **tab, char const *str, char c)
{
	int w_size;
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			w_size = 0;
			while (str[i] != c && str[i])
			{
				w_size++;
				i++;
			}
			if (!(tab[j] = malloc(sizeof(char) * (w_size + 1))))
				return (0);
			j++;
		}
	}
	return (1);
}

static	void	ft_strcpy(char **tab, char const *str, char c)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	while (str[i])
	{
		k = 0;
		if (str[i] == c)
			i++;
		else
		{
			while (str[i] != c && str[i])
			{
				tab[j][k] = str[i];
				i++;
				k++;
			}
			tab[j][k] = '\0';
			j++;
		}
	}
}

char			**ft_split(char const *str, char c)
{
	char	**tab;
	int		word_count;

	if (!str)
		return (NULL);
	word_count = ft_word_count(str, c);
	if (!(tab = malloc(sizeof(*tab) * (word_count + 1))))
		return (NULL);
	tab[word_count] = NULL;
	if (ft_word_size(tab, str, c) == 0)
	{
		ft_free_split(tab, word_count);
		return (NULL);
	}
	ft_strcpy(tab, str, c);
	return (tab);
}
