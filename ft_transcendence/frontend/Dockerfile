FROM node:alpine
WORKDIR /app
# COPY package.json ./
# COPY package-lock.json ./
# COPY ./ ./
COPY ./start.sh ./
# RUN npm install -s && npm update -s
# ENTRYPOINT ["/bin/sh"]
ENTRYPOINT ["/bin/sh", "start.sh"]
# CMD ["npm", "run", "start"]