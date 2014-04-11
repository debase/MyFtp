/*
** serveur.h for serveur in /home/debas_e/Project/System_Unix/PSU_2013_myftp/srv
**
** Made by Etienne
** Login   <debas_e@epitech.net>
**
** Started on  Tue Apr  8 13:33:10 2014 Etienne
** Last update Fri Apr 11 20:30:33 2014 Etienne
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
#include <unistd.h>
#include <netdb.h>
#include "com.h"

# ifndef PATH_MAX
#  define PATH_MAX	4096
# endif

typedef struct		s_serveur
{
  int			sockfd;
  struct sockaddr_in	*cli_addr;
  char			base_pwd[PATH_MAX];
  char			current_pwd[PATH_MAX];
}			t_serveur;

typedef struct	s_serveur_asso_func
{
  char		*cmd;
  char		*(*func)(t_serveur *, t_cmd *);
}		t_serveur_asso_func;

char			*ls_serveur(t_serveur *, t_cmd *cmd);
char			*cd_serveur(t_serveur *, t_cmd *cmd);
char			*pwd_serveur(t_serveur *, t_cmd *cmd);
char			*get_serveur(t_serveur *, t_cmd *cmd);
char			*put_serveur(t_serveur *, t_cmd *cmd);
int			create_socket_server(const char *port);

#endif /* !_SERVEUR_H_ */
