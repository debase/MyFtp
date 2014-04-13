/*
** main.c for main in /home/debas_e/Project/System_Unix/PSU_2013_myftp
**
** Made by Etienne
** Login   <debas_e@epitech.net>
**
** Started on  Mon Apr  7 23:39:28 2014 Etienne
** Last update Sun Apr 13 14:21:26 2014 Etienne
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "client.h"

int		main(int ac, char *argv[])
{
  t_client	cstruct;

  if (ac != 3)
    {
      printf("%sUsage%s : %s <host> <port>\n",
	     COLOR_RED, COLOR_RESET, argv[0]);
      return (1);
    }
  memset(&cstruct, 0, sizeof(cstruct));
  if ((cstruct.sockfd = create_socket_client(argv[1], argv[2])) < 0)
    return (EXIT_FAILURE);
  snprintf(cstruct.prompt, PROMPT_SIZE, "%s::%s > ", argv[1], argv[2]);
  while (write(1, cstruct.prompt, sizeof(cstruct.prompt))
	 && (!my_getline(&cstruct)) && strcmp(cstruct.command_line, "quit"))
    {
      epur_str(cstruct.command_line);
      if (exec_cmd(&cstruct))
	break;
    }
  close(cstruct.sockfd);
  return (0);
}
