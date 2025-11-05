/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhallad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:51:34 by mkhallad          #+#    #+#             */
/*   Updated: 2025/10/24 17:51:37 by mkhallad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char *whatsleft;
	char		*l; // l = line

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	whatsleft = read_file(fd, whatsleft);
	if (!whatsleft)
		return (NULL);
	l = extract(whatsleft);
	whatsleft = update_whatsleft(whatsleft);
	return (l);
}

char	*read_file(int fd, char *whatsleft)
{
	char	*buffer;
	char	*temp;
	int		b; //bytes read

	buffer = malloc(BUFFER_SIZE + 1)
	if (!buffer)
		return (NULL);
	b = 1;
	while (b > 0 && !ft_strchr(whatsleft, '\n'))
	{
		b = read(fd, buffer, BUFFER_SIZE);
		if (b == -1)
		{
			free (buffer);
			return (NULL);
		}
		buffer[b] = '\0';
		temp = ft_strjoin(whatsleft, buffer);
		free (whatsleft);
		whatsleft = temp;
	}
	free(buffer);
	return (whatsleft);
}

char	*extract(char *whatsleft)
{
	char	*l; // l:line
	int		i;

	i = 0;
	if (!whatsleft[i])
		return (NULL);
	while (whatsleft[i] && whatsleft[i] != '\n')
		i++;
	if (whatsleft[i] == '\n')
		i++;
	l = ft_substr(whatsleft, 0, i);
	return (l);
}

char	*update_whatsleft(char *whatsleft)
{
	char	*new; //new whatsleft
	int		i;

	i = 0;
	while (whatsleft[i] && whatsleft[i] != '\n')
		i++;
	if (!whatsleft[i])
	{
		free (whatsleft);
		return (NULL);
	}
	new = ft_substr(whatsleft, i + 1, ft_strlen(whatsleft) - i);
	free (whatsleft);
	return (new);
}
