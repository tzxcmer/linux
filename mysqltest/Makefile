mysqlClient:mysqlclient.cc
	g++ -o $@ $^ -std=c++11 -L /lib64/mysql -lmysqlclient
.PHONY:clean
clean:
	rm -rf mysqlClient