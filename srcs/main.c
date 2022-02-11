/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucferna <lucferna@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 21:36:57 by lucferna          #+#    #+#             */
/*   Updated: 2022/02/09 14:18:22 by lucferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	check_file(char *str, char *ber)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (str[i] != ber[i])
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int	fd;

	if (argc != 2)
		printf("Error\nWrong number of arguments\n");
	else
	{
		if (ft_strlen(argv[1]) < 4
			|| check_file(argv[1] + ft_strlen(argv[1]) - 4, ".ber"))
		{
			printf("Error\nInvalid file\n");
			return (0);
		}
		fd = open(argv[1], O_RDWR);
		if (fd < 0)
			printf("Error\nSomething is wrong with your file\n");
		else
			so_long(fd);
	}
	return (0);
}
