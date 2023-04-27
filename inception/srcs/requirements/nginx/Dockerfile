# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/20 13:42:53 by loumouli          #+#    #+#              #
#    Updated: 2023/03/20 13:42:54 by loumouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM alpine:3.17

RUN set -x && adduser -u 82 -D -S -G www-data www-data

RUN apk update && apk add --no-cache nginx openssl && mkdir -p /etc/ssl/private && mkdir -p /etc/ssl/certs

RUN openssl req -x509 -nodes -days 365 -newkey rsa:4096 -keyout /etc/ssl/private/nginx.key -out /etc/ssl/certs/nginx.crt -subj "/C=FR/ST=Paris/L=Paris/O=loulouCorp/CN=loumouli.42.fr"

RUN mkdir -p /var/www/html && mkdir -p /var/run/nginx

COPY ./conf/nginx.conf /etc/nginx/nginx.conf

EXPOSE 443

RUN chmod 755 /var/www/html
RUN chown -R www-data:www-data /var/www/html

CMD ["nginx", "-g", "daemon off;"]
# CMD ["nginx", "-t"]