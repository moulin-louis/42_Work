# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 08:34:51 by loumouli          #+#    #+#              #
#    Updated: 2023/03/20 08:34:54 by loumouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM alpine:3.15

RUN apk upgrade; apk add mariadb mariadb-client
COPY conf/50-server.cnf	/etc/my.cnf

RUN chown -R mysql:mysql /var/lib/mysql; mysql_install_db --user=mysql;
COPY ./script/mariadb.sh /tmp/setup.sh

ENTRYPOINT ["/bin/sh", "/tmp/setup.sh"]
CMD [ "/usr/bin/mysqld", "-u", "mysql" ]
