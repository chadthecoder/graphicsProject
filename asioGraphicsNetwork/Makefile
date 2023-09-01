cc = g++

ip = 127.0.0.1

both: $(dotO)
	$(cc) client.cpp -o bin/client
	$(cc) server.cpp -o bin/server

runServer:
	sudo bin/server

#run client to local, to run for non local server-"make runClient ip=0.0.0.0"
runClient:
	bin/client $(ip)

clean:
	rm bin/*.o
	rm bin/client
	rm bin/server