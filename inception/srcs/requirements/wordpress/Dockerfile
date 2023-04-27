# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 13:42:55 by loumouli          #+#    #+#              #
#    Updated: 2023/03/20 13:42:57 by loumouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM alpine:3.17

RUN set -x && adduser -u 82 -D -S -G www-data www-data

RUN echo "http://mirrors.ircam.fr/pub/alpine/edge/testing" >> /etc/apk/repositories \
	&&	apk update \
	&& apk add --no-cache php8 \
    mariadb\
    mariadb-client\
    php8-common \
	php8-session\
	php8-gd\
	php8-pecl-mcrypt\
	php8-soap\
	php8-gettext\
	php8-ldap\
	php8-mysqli\
	php8-ctype\
	php8-posix\
	php8-cgi\
	php8-pecl-xmlrpc\
	php8-imap\
    php8-fpm \
	fcgi\
    php8-pdo \
    php8-opcache \
    php8-zip \
    php8-phar \
    php8-iconv \
    php8-cli \
    php8-curl \
    php8-openssl \
    php8-mbstring \
    php8-tokenizer \
    php8-fileinfo \
    php8-json \
    php8-xml \
    php8-xmlwriter \
    php8-simplexml \
    php8-dom \
    php8-pdo_mysql \
    php8-pdo_sqlite \
    php8-tokenizer \
    php8-pecl-redis \
	curl \
	wget \
	&& ln /usr/bin/php8 /usr/bin/php

RUN wget https://fr.wordpress.org/wordpress-6.0-fr_FR.tar.gz -P /var/www
RUN cd /var/www && tar -xzf wordpress-6.0-fr_FR.tar.gz && rm wordpress-6.0-fr_FR.tar.gz
RUN chown -R root:root /var/www/wordpress
COPY conf/www.conf /etc/php8/php-fpm.d/www.conf

RUN	curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar &&\
	chmod +x wp-cli.phar &&\
	mv wp-cli.phar /usr/local/bin/wp

COPY script/setup_wp.sh /tmp/setup_wp.sh
RUN chmod +x /tmp/setup_wp.sh

ENTRYPOINT [ "/bin/sh", "/tmp/setup_wp.sh" ]
CMD [ "/usr/sbin/php-fpm8", "-F" ]
