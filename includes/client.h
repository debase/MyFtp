/*
** client.h for client in /home/debas_e/Project/System_Unix/PSU_2013_myftp
**
** Made by Etienne
** Login   <debas_e@epitech.net>
**
** Started on  Tue Apr  8 14:12:36 2014 Etienne
** Last update Sun Apr 13 16:26:50 2014 Etienne
*/

#ifndef _CLIENT_H_
# define _CLIENT_H_

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <stdio.h>
# include <netdb.h>
# include "com.h"

# define PROMPT_SIZE	256

typedef struct	s_client
{
  char		prompt[PROMPT_SIZE];
  int		sockfd;
  char		command_line[CMD_SIZE];
  char		*arg[2];
}		t_client;

typedef struct	s_client_asso_func
{
  char		*cmd;
  int		(*func)(t_client *, t_cmd *);
}		t_client_asso_func;

void		epur_str(char *str);
int		exec_cmd(t_client *client);
int		my_getline(t_client *client);
void		put_in_tab(t_client *client);
int		get_client(t_client *client, t_cmd *cmd);
int		put_client(t_client *client, t_cmd *cmd);
int		other_func(t_client *client, t_cmd *cmd);
int		help_func(t_client *client, t_cmd *cmd);
int		send_cmd_serv(int sockfd, t_cmd *cmd);
int		create_socket_client(const char *host, const char *port);
int		get_data(int fd, void *data, size_t size);

#endif /* !_CLIENT_H_ */
