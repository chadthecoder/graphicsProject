cc = g++

ip = 127.0.0.1

both: $(dotO)
	$(cc) client.cpp -o bin/client -Iasio-1.28.0/include -DASIO_STANDALONE=1
	$(cc) server.cpp -o bin/server -Iasio-1.28.0/include -DASIO_STANDALONE=1

runServer:
	sudo bin/server

#run client to local, to run for non local server-"make runClient ip=0.0.0.0"
runClient:
	bin/client $(ip)

clean:
	rm bin/client
	rm bin/server