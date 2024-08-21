/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqaroot <oqaroot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:23:22 by omaimaqaroo       #+#    #+#             */
/*   Updated: 2024/08/21 15:26:05 by oqaroot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*create_line(char *stack_line)
{
	char	*line;
	int		i;

	if (!stack_line || !*stack_line)
		return (NULL);
	i = 0;
	while (stack_line[i] != '\n' && stack_line[i] != '\0')
		i++;
	if (stack_line[i] == '\n')
		i++;
	line = malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (stack_line[i] != '\n' && stack_line[i] != '\0')
	{
		line[i] = stack_line[i];
		i++;
	}
	if (stack_line[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*update_stack(char *stack)
{
	char	*aux;
	char	*p;
	int		i;

	p = ft_strchr(stack, '\n');
	if (!p)
	{
		free(stack);
		return (NULL);
	}
	p++;
	aux = malloc(sizeof(char) * (ft_strlen(p) + 1));
	i = 0;
	while (*p != '\0')
	{
		aux[i] = *p;
		i++;
		p++;
	}
	aux[i] = '\0';
	free(stack);
	return (aux);
}

char	*join_and_free(char *stack, char *tmp)
{
	char	*aux;

	if (!stack)
	{
		stack = malloc(1);
		stack[0] = 0;
	}
	if (!stack)
		return (NULL);
	aux = ft_strjoin(stack, tmp);
	if (!aux)
		return (free(stack), NULL);
	if (stack)
		free(stack);
	return (aux);
}

char	*get_next_line(int fd)
{
	static char	*stack = NULL;
	char		tmp[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		readbytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	readbytes = 1;
	while (!(ft_strchr(stack, '\n')) && readbytes > 0)
	{
		readbytes = read(fd, tmp, BUFFER_SIZE);
		if (readbytes < 0)
			return (free(stack), stack = NULL, NULL);
		tmp[readbytes] = '\0';
		stack = join_and_free(stack, tmp);
		if (!stack)
			return (NULL);
	}
	line = create_line(stack);
	stack = update_stack(stack);
	return (line);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char	*str;
// 	int		fd;
// 	fd = open("file.txt", O_RDONLY);
// 	str = get_next_line(fd);

// 	while (str)
// 	{
// 		printf("%s", str);
// 		free(str);
// 		str = get_next_line(fd);
// 	}
// 	close(fd);
// }