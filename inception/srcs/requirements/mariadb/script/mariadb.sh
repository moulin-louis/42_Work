# #!/bin/sh

mysqld -u root --bind-address=localhost --silent-startup > /tmp/mariastart.log 2>&1 &
PID=$!
until tail "/tmp/mariastart.log" | grep -qi "Version:"; do
	sleep 0.2
done

mysql <<EOF
create database \`${SQL_DATABASE}\`;
grant all privileges on \`${SQL_DATABASE}\`.* to  \`${SQL_USER}\`@'%' identified by '${SQL_PASSWORD}';
alter user 'root'@'localhost' identified by '${SQL_ROOT_PASSWORD}';
flush privileges;
EOF

kill -TERM ${PID}
chown -R mysql:mysql /var/lib/mysql;
sleep 2
exec $@
