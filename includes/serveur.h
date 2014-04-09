/*
** serveur.h for serveur in /home/debas_e/Project/System_Unix/PSU_2013_myftp/srv
**
** Made by Etienne
** Login   <debas_e@epitech.net>
**
** Started on  Tue Apr  8 13:33:10 2014 Etienne
** Last update Wed Apr  9 16:05:38 2014 Etienne
*/

#ifndef _SERVEUR_H_
#define _SERVEUR_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netdb.h>
#include "com.h"

typedef struct	s_serveur_asso_func
{
  char		*cmd;
  char		*(*func)(int, t_cmd *);
}		t_serveur_asso_func;

char			*ls_serveur(int sockfd, t_cmd *cmd);
int			create_socket_server(const char *port);

#endif /* !_SERVEUR_H_ */
