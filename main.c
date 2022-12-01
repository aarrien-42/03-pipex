#include "pipex.h"

int	main()
{
	char *path_cmd[] = {"/bin/ls", "ls", "-l", "-a", NULL};
	execve(path_cmd[0], &path_cmd[1], NULL);
	return (0);
}
