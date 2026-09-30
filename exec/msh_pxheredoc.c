/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pxheredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 18:18:31 by thtay             #+#    #+#             */
/*   Updated: 2026/09/08 18:18:34 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*mhd_expand_heredoc(char *string /*, env*/)
// {
// 	return string;
// }

//if delim has quotes there should be a notice of it.
//mode0 means we expand environment
//mode1 means the delim was quoted 
// ret_fd = open("/tmp", __O_TMPFILE | O_RDWR , 0777);

// int	msh_pxheredoc(char *delimiter, int mode /*, env*/)
// {
// 	char	*ptr;
// 	int		ret_fd;

// 	ret_fd = open(".tmp", O_CREAT | O_RDWR | O_TRUNC, 0777);
// 	while (ret_fd > 2)
// 	{
// 		ptr = get_next_line(0);
// 		if (!ptr || ft_strncmp(ptr, delimiter, ft_strlen(delimiter)) == 0)
// 		{
// 			if (!ptr)
// 				printf("msh: warning: here-document delimited by end-of-file\
// (wanted `%s')\n", delimiter);
// 			if (!ptr || ft_strlen(ptr) - 1 == ft_strlen(delimiter))
// 				break ;
// 		}
// 		if (mode == 0)
// 			ptr = mhd_expand_heredoc(ptr);
// 		ft_putstr_fd(ptr, ret_fd);
// 		free(ptr);
// 	}
// 	if (ptr != NULL)
// 		free(ptr);
// 	close(ret_fd);
// 	ret_fd = open(".tmp", O_RDWR);
// 	return (ret_fd);
// }


#include "minishell.h"
#include <unistd.h>

static char	*append_text(char *result, const char *text)
{
	char	*joined;

	joined = ft_strjoin(result, text);
	free(result);
	return (joined);
}

static char	*expand_heredoc_line(char *line, t_shell *shell)
{
	char	*result;
	char	*expanded;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			expanded = expand_variable(line, &i, shell);
			if (!expanded)
				return (free(result), NULL);
			result = append_text(result, expanded);
			free(expanded);
		}
		else
		{
			expanded = ft_substr(line, i, 1);
			if (!expanded)
				return (free(result), NULL);
			result = append_text(result, expanded);
			free(expanded);
			i++;
		}
		if (!result)
			return (NULL);
	}
	return (result);
}

static int	write_all(int fd, const char *text)
{
	size_t	offset;
	size_t	len;
	ssize_t	written;

	offset = 0;
	len = ft_strlen(text);
	while (offset < len)
	{
		written = write(fd, text + offset, len - offset);
		if (written < 0)
			return (-1);
		offset += (size_t)written;
	}
	return (0);
}

static int	line_matches_delimiter(char *line, const char *delimiter)
{
	size_t	line_len;
	size_t	delimiter_len;

	line_len = ft_strlen(line);
	delimiter_len = ft_strlen(delimiter);
	if (line_len > 0 && line[line_len - 1] == '\n')
		line_len--;
	return (line_len == delimiter_len
		&& ft_strncmp(line, delimiter, delimiter_len) == 0);
}

static int	create_heredoc_temp_fd(void)
{
	static unsigned int	counter;
	char				*pid_text;
	char				*count_text;
	char				*name;
	int					fd;

	while (1)
	{
		pid_text = ft_itoa((int)getpid());
		count_text = ft_itoa((int)counter++);
		if (!pid_text || !count_text)
			return (free(pid_text), free(count_text), -1);
		name = ft_strjoin(".msh_heredoc_", pid_text);
		free(pid_text);
		if (!name)
			return (free(count_text), -1);
		pid_text = ft_strjoin(name, "_");
		free(name);
		if (!pid_text)
			return (free(count_text), -1);
		name = ft_strjoin(pid_text, count_text);
		free(pid_text);
		free(count_text);
		if (!name)
			return (-1);
		fd = open(name, O_CREAT | O_EXCL | O_RDWR, 0600);
		if (fd >= 0)
		{
			unlink(name);
			free(name);
			return (fd);
		}
		free(name);
		if (errno != EEXIST)
			return (-1);
	}
}

/*
 * Returns a readable, rewound FD on success, or -1 on failure.
 * expand_content is 0 when the delimiter was quoted, 1 otherwise.
 * The caller owns the returned FD and must close it after dup2().
 */
int	create_heredoc_fd(const char *delimiter, int expand_content,
		t_shell *shell)
{
	char	*line;
	char	*content;
	int		fd;

	if (!delimiter || !shell)
		return (-1);
	fd = create_heredoc_temp_fd();
	if (fd == -1)
		return (perror("minishell: heredoc"), -1);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document ended by EOF\n",
				STDERR_FILENO);
			break ;
		}
		if (line_matches_delimiter(line, delimiter))
			return (free(line), lseek(fd, 0, SEEK_SET), fd);
		content = line;
		if (expand_content)
		{
			content = expand_heredoc_line(line, shell);
			free(line);
			if (!content)
				return (close(fd), -1);
		}
		if (write_all(fd, content) == -1)
		{
			perror("minishell: heredoc write");
			free(content);
			close(fd);
			return (-1);
		}
		free(content);
	}
	if (lseek(fd, 0, SEEK_SET) == -1)
		return (perror("minishell: heredoc seek"), close(fd), -1);
	return (fd);
}
