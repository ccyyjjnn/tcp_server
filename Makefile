server:
	g++ util.cpp server.cpp  InterAddress.cpp Socket.cpp -o server
clean:
	rm server 