/*
** exec_cmd_client.c for exec_cmd in /home/debas_e/Project/System_Unix/PSU_2013_myftp/clt
**
** Made by Etienne
** Login   <debas_e@epitech.net>
**
** Started on  Fri Apr 11 23:26:56 2014 Etienne
** Last update Sun Apr 13 19:15:33 2014 Etienne
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "client.h"

static t_client_asso_func	g_assofunc[] =
  {
    {"get", get_client},
    {"put", put_client},
    {"ls", other_func},
    {"cd", other_func},
    {"pwd", other_func},
    {"help", help_func},
    {NULL, NULL}
  };

int		send_cmd_serv(int sockfd, t_cmd *cmd)
{
  int		ret;

  ret = write(sockfd, cmd, sizeof(*cmd));
  if (ret <= 0)
    {
      perror("write");
      return (EXIT_FAILURE);
    }
  if (ret != sizeof(*cmd))
    {
      fprintf(stderr, "Error sending data to server\n");
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}

int		exec_cmd(t_client *client)
{
  t_cmd		cmd;
  int		i;

  i = 0;
  memset(&cmd, 0, sizeof(cmd));
  put_in_tab(client);
  if (client->arg[0] == NULL)
    return (EXIT_SUCCESS);
  strncpy(cmd.arg1, client->arg[0], CMD_SIZE - 1);
  (client->arg[1] == NULL ? memset(cmd.arg2, 0, CMD_SIZE - 1) :
   strncpy(cmd.arg2, client->arg[1], CMD_SIZE));
  while (g_assofunc[i].cmd != NULL)
    {
      if (!strcmp(g_assofunc[i].cmd, client->arg[0]))
	{
	  return (g_assofunc[i].func(client, &cmd));
	}
      i++;
    }
  printf("%s : command not found.\n", client->arg[0]);
  return (EXIT_SUCCESS);
}
