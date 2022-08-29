server:
	g++ util.cpp server.cpp Epoll.cpp InterAddress.cpp Socket.cpp -o server

clean:
	rm server 