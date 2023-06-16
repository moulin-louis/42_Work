FROM node:alpine

RUN apk add curl
WORKDIR /app

COPY start.sh ./

ENTRYPOINT ["/bin/sh", "start.sh"]