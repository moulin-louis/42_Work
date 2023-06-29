FROM node:latest

COPY frontend frontend
COPY backend backend
COPY .env ./frontend

RUN npm install --prefix frontend \
	&& npm run build --prefix frontend \
	&& npm install --prefix backend \
	&& npm run build --prefix backend

CMD npm run start:prod --prefix backend
