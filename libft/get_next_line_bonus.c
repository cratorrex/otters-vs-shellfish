/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:21:34 by thtay             #+#    #+#             */
/*   Updated: 2025/12/19 21:21:36 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// read, malloc, free
//
// Basic idea is:
// ssize_t read(int fd, void *buf, size_t nbyte);
//
// if (nbyte == 0) >> maybe error or return (0);
// Nothing left or error, return (NULL);
//
// ! while read will constantly increment the read-head per each
// ! successive call of read().
//
// [     n  ] 
//        >>>[        ][        ][    E<<<]
//        ^stashed                    ^EOF
// -D BUFFER_SIZE=10
//

// buffer is declared upon compilation and is thus not a VLA

#include "libft.h"

//can finally free stash if needed
//n+1 to skip the \n into stash
static char	*gnl_trim_stash(char *stash)
{
	ssize_t	start;
	char	*new;
	int		i;

	i = 0;
	start = gnl_memnchr(stash, gnl_strlen(stash)) + 1;
	if (start > gnl_strlen(stash) || stash[start] == '\0')
	{
		free(stash);
		return (NULL);
	}
	new = malloc((gnl_strlen(stash) - start) + 1);
	if (new == NULL)
		return (NULL);
	while (stash[start + i])
	{
		new[i] = stash[start + i];
		i++;
	}
	new[i] = '\0';
	free(stash);
	return (new);
}

static char	*gnl_get_return(char *stash)
{
	ssize_t	len;
	int		i;
	char	*ret;

	i = 0;
	len = 0;
	len = gnl_memnchr(stash, gnl_strlen(stash)) + 1;
	ret = malloc(len + 1);
	if (ret == NULL)
		return (NULL);
	while (i < len)
	{
		ret[i] = stash[i];
		i++;
	}
	ret[len] = '\0';
	return (ret);
}

static char	*gnl_read_loop(char *fdstr, int fd, char *buffer)
{
	ssize_t		r_idx;

	r_idx = read(fd, buffer, BUFFER_SIZE);
	if (r_idx == -1)
	{
		free(fdstr);
		return (NULL);
	}
	while (r_idx > 0 && fdstr != NULL)
	{
		fdstr = gnl_strljoin(fdstr, buffer);
		if (gnl_memnchr(buffer, BUFFER_SIZE) < BUFFER_SIZE)
		{
			return (fdstr);
		}
		while (r_idx > 0)
			buffer[--r_idx] = 0;
		r_idx = read(fd, buffer, BUFFER_SIZE);
	}
	if (r_idx == 0 && *fdstr != '\0')
		return (fdstr);
	free(fdstr);
	return (NULL);
}

//stash set to 1025 due to fd soft limit.. just in case..
//read into buffer
//something was read (&& !error)
//dup (join) into stash
//return all until \n. any remaining buffer, store into stash
char	*get_next_line(int fd)
{
	static char		*stash[1025];
	char			*buffer;
	char			*ret;
	int				i;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 1024)
		return (NULL);
	i = 0;
	buffer = malloc (BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (i <= BUFFER_SIZE)
		buffer[i++] = 0;
	if (stash[fd] == NULL)
		stash[fd] = gnl_strdup("");
	stash[fd] = gnl_read_loop(stash[fd], fd, buffer);
	free(buffer);
	if (stash[fd] == NULL)
		return (NULL);
	ret = gnl_get_return(stash[fd]);
	stash[fd] = gnl_trim_stash(stash[fd]);
	return (ret);
}
