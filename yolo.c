#include "filler.h"

int		main(int ac, char **av)
{
	char *line;
	int		fd = open("/Users/cgarrot/filler/info.log", O_WRONLY | O_APPEND);

while (get_next_line(0, &line))
{
	dprintf(fd, "%s\n", line);

}
	return (0);
}