##
## Makefile for Makefile in /home/debas_e/Project/System_Unix/PSU_2013_myftp
## 
## Made by Etienne
## Login   <debas_e@epitech.net>
## 
## Started on  Mon Apr  7 21:12:01 2014 Etienne
## Last update Wed Apr  9 13:34:56 2014 Etienne
##

SRVNAME	= serveur

NAMECLI	= client

SRV	= srv

CLI	= clt

SRVSRC	=	$(SRV)/main.c		\
		$(SRV)/socket_serveur.c

SRCCLT	=	$(CLI)/main.c		\
		$(CLI)/socket_client.c

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
