#include "pipex.h"

void	read_file1(char *buffer, char *file1, int size)
{
	int	fd;
	char	*ret;

	fd = open (file1, O_RDONLY);
	if (fd < 0)
	{
		write (2, strerror(errno), ft_strlen(strerror(errno)));
		write (2, "\n", 1);
		exit (1);
	}
	read (fd, buffer, size);
	close (fd);
}

char	*file1_size(char *str) //file1 읽어오고 그만큼 할당해서 읽기.
{
	int		size;
	int		read_size;
	char	*temp[10];
	char	*buffer;
	int		fd;

	fd = open (str, O_RDWR);
	if (fd < 0)
	{
		write (2, strerror(errno), ft_strlen(strerror(errno)));
		write (2, "\n", 1);
		exit (0);
	}
	read_size = read(fd, temp, 10);
	size = 0;
	while (read_size > 0)
	{
		size += read_size;
		read_size = read (fd, temp, 10);
	}
	buffer = (char *)malloc(sizeof(char) * (size + 1));
	if (buffer == 0)
		return (NULL);
	close (fd);
	read_file1(buffer, str, size);
	return (buffer);
}