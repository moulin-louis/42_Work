# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 10:25:58 by loumouli          #+#    #+#              #
#    Updated: 2023/03/20 13:50:58 by loumouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: clean build

user:
	@sudo cp ./srcs/hosts /etc/hosts

build:
	@sudo mkdir -p /home/loumouli/data/wordpress
	@sudo mkdir -p /home/loumouli/data/mariadb
	@cd ./srcs/ && docker compose up --build

clean:
	@sudo rm -rf /home/loumouli/data
	@echo cleaning all docker related stuff
	@sudo rm -rf /home/loumouli/data
	@docker stop $$(docker ps -qa) > /dev/null 2> /dev/null ;\
	docker rm $$(docker ps -qa) > /dev/null 2> /dev/null;\
	docker rmi -f $$(docker images -qa) > /dev/null 2> /dev/null;\
	docker volume rm $$(docker volume ls -q) > /dev/null 2> /dev/null;\
	docker network prune -f > /dev/null 2> /dev/null;
	@yes | docker system prune -a

.PHONY: all clean user build
