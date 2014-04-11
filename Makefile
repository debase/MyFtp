##
## Makefile for Makefile in /home/debas_e/Project/System_Unix/PSU_2013_myftp
## 
## Made by Etienne
## Login   <debas_e@epitech.net>
## 
## Started on  Mon Apr  7 21:12:01 2014 Etienne
## Last update Sat Apr 12 00:04:12 2014 Etienne
##

SRVNAME	= serveur

NAMECLI	= client

SRV	= srv

CLI	= clt

SRVSRC	=	$(SRV)/main.c			\
		$(SRV)/socket_serveur.c		\
		$(SRV)/handle_client.c		\
		$(SRV)/get_serveur.c		\
		$(SRV)/basic_func_server.c	\
		$(SRV)/exec_cmd_client.c	\
		$(SRV)/put_serveur.c

SRCCLT	=	$(CLI)/main.c			\
		$(CLI)/socket_client.c		\
		$(CLI)/parse_line.c		\
		$(CLI)/exec_cmd_client.c	\
		$(CLI)/basic_func_client.c	\
		$(CLI)/get_client.c		\
		$(CLI)/put_client.c

INC	=	includes/

SRVOBJ	=	$(SRVSRC:.c=.o)

CLTOBJ	=	$(SRCCLT:.c=.o)

CC	=	gcc

RM	=	rm -rf

CFLAGS	=	-W -Wall

all:		$(SRVNAME) $(NAMECLI)

$(SRVNAME):	$(SRVOBJ)
		$(CC) -o $(SRVNAME) $(SRVOBJ)

$(NAMECLI):	$(CLTOBJ)
		$(CC) -o $(NAMECLI) $(CLTOBJ)

.c.o:
		$(CC) $(CFLAGS) -I$(INC) -c $< -o $(<:.c=.o)

clean:
		$(RM) $(SRVOBJ) $(CLTOBJ)

fclean:		clean
		$(RM) $(SRVNAME) $(NAMECLI)

re:		fclean all
