/*
** main.c for main in /home/debas_e/Project/System_Unix/PSU_2013_myftp
**
** Made by Etienne
** Login   <debas_e@epitech.net>
**
** Started on  Mon Apr  7 23:39:28 2014 Etienne
** Last update Fri Apr 11 22:44:39 2014 Etienne
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
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

void             epur_str(char *str)
{
  int           i;
  int           j;

  i = 0;
  j = 0;
  while (str[i] == ' ' || str[i] == '\t')
    i++;
  while (str[i])
    if (str[i] != ' ' && str[i] != '\t')
      str[j++] = str[i++];
    else
      {
	str[j++] = ' ';
        while (str[i] == ' ' || str[i] == '\t')
          i++;
      }
  str[j] = 0;
  if (str[j - 1] == ' ')
    str[j - 1] = '\0';
}

int		my_getline(t_client *client)
{
  int		ret;

  memset(client->command_line, 0, CMD_SIZE);
  ret = read(0, client->command_line, CMD_SIZE - 1);
  if (ret < 0)
    {
      perror("read");
      return (EXIT_FAILURE);
    }
  else if (ret == 0)
    return (EXIT_FAILURE);
  client->command_line[ret - 1] = '\0';
  return (EXIT_SUCCESS);
}

void		put_in_tab(t_client *client)
{
  char		*saveptr;
  char		*subtoken;

  subtoken = strtok_r(client->command_line, " ", &saveptr);
  client->arg[0] = subtoken;
  subtoken = strtok_r(NULL, " ", &saveptr);
  client->arg[1] = subtoken;
}

int		send_cmd_serv(int sockfd, t_cmd *cmd)
{
  int		ret;

  ret = write(sockfd, cmd, sizeof(*cmd));
  if (ret < 0)
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

int		help_func(__attribute__((unused)) t_client *client,
			  __attribute__((unused)) t_cmd *cmd)
{
  printf("%sHelp :%s\n", COLOR_RED, COLOR_RESET);
  printf("%sls%s              : list all files of the "
	 "current server working directory\n", COLOR_BLUE, COLOR_RESET);
  printf("%spwd%s             : display the current "
	 "serveur working directory\n", COLOR_BLUE, COLOR_RESET);
  printf("%scd  <directory>%s : change server "
	 "working directory\n", COLOR_BLUE, COLOR_RESET);
  printf("%sget <file>%s      : transfert server file "
	 "to the current local working directory\n", COLOR_BLUE, COLOR_RESET);
  printf("%sput <file>%s      : transfert local file "
	 "to the current server working directory\n", COLOR_BLUE, COLOR_RESET);
  return (EXIT_SUCCESS);
}

int		other_func(t_client *client, t_cmd *cmd)
{
  int		ret;
  t_data	data;

  memset(&data, 0, sizeof(data));
  if (send_cmd_serv(client->sockfd, cmd) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  ret = read(client->sockfd, &data, sizeof(data));
  while (ret > 0 && ret == sizeof(data))
    {
      printf("%s\n", data.data);
      if (data.flags == MSG_END)
	break;
      ret = read(client->sockfd, &data, sizeof(data));
    }
  if (ret < 0 || ret != sizeof(data))
    {
      perror("read error");
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

int		main(int ac, char *argv[])
{
  t_client	cstruct;

  if (ac != 3)
    return (1);
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
