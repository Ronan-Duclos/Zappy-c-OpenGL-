#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>

void	load_file_2(char *name, char **data, int *len)
{
	void	*file;
	int		l;
	int		fd;

	fd = open(name, O_RDONLY);
	l = lseek(fd, 0, SEEK_END);
	file = mmap(0, l, PROT_READ, MAP_PRIVATE, fd, 0);
	*data = file;
	*len = l;
	close(fd);
}

void	*load_file(char *filename)
{
	void	*file;
	int		len;
	int		fd;

	fd = open(filename, O_RDONLY);
	len = lseek(fd, 0, SEEK_END);
	file = mmap(0, len, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);
	return (file);
}
