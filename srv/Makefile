##
## Makefile for Makefile in /home/debas_e/Project/System_Unix/PSU_2013_myftp
## 
## Made by Etienne
## Login   <debas_e@epitech.net>
## 
## Started on  Mon Apr  7 21:12:01 2014 Etienne
## Last update Sun Apr 13 18:47:12 2014 Etienne
##

BINDIR	=	../

NAME	=	$(addprefix $(BINDIR), serveur)

CC	=	gcc

RM	=	rm -rf

INCDIR	=	../includes/

SRCDIR	=	./

SRCS	=	main.c			\
		socket_serveur.c	\
		handle_client.c		\
		get_serveur.c		\
		basic_func_server.c	\
		exec_cmd_client.c	\
		put_serveur.c

OBJDIR	=	../obj/serveur/

OBJS	=	$(addprefix $(OBJDIR), $(SRCS:.c=.o))

CFLAGS	=	-W -Wall

dummy   :=	$(shell test -d $(OBJDIR) || mkdir $(OBJDIR)) \
		$(shell test -d $(BINDIR) || mkdir $(BINDIR))

$(OBJDIR)%.o: 	$(SRCDIR)%.c
	        $(CC) -I$(INCDIR) $(CFLAGS) -o $@ -c $<

$(NAME):	$(OBJS)
	        $(CC) -o $(NAME) $(OBJS)

all:		$(NAME)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all
