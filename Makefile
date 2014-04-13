##
## Makefile for Makefile in /home/sinet_l/Documents/project/cpp_nibbler
## 
## Made by luc sinet
## Login   <sinet_l@epitech.net>
## 
## Started on  Tue Mar 18 23:11:50 2014 luc sinet
## Last update Sun Apr 13 14:43:18 2014 Etienne
##

NAME	= myftp

PATHS	= clt/ \
	  srv/

BINDIR	= ./
OBJDIR	= ./obj/

dummy	:= $(shell test -d $(OBJDIR) || mkdir $(OBJDIR)) \
	   $(shell test -d $(BINDIR) || mkdir $(BINDIR))

$(NAME):
	@for dir in $(PATHS); do \
	echo -e "\e[30m [\e[34mCompiling: \e[31m$$dir\e[30m]\e[0m"; make --no-print-directory -C $$dir; \
	done

all: $(NAME)

clean:
	@for dir in $(PATHS); do \
	echo -e "\e[30m [\e[34mCleaning: \e[31m$$dir\e[30m]\e[0m"; make --no-print-directory -C $$dir clean; \
	done

fclean:
	@for dir in $(PATHS); do \
	echo -e "\e[30m [\e[34mRemoving: \e[31m$$dir\e[30m]\e[0m"; make --no-print-directory -C $$dir fclean; \
	done

re:	fclean all
