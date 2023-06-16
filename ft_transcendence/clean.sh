echo cleaning all docker related stuff
docker stop $(docker ps -qa) > /dev/null 2> /dev/null ;\
docker rm $(docker ps -qa) > /dev/null 2> /dev/null;\
docker rmi -f $(docker images -qa) > /dev/null 2> /dev/null;\
docker volume rm $(docker volume ls -q) > /dev/null 2> /dev/null;\
docker network prune -f > /dev/null 2> /dev/null;
yes | docker system prune -a