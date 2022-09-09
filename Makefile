server:
	g++ util.cpp server.cpp Epoll.cpp InterAddress.cpp Socket.cpp FileDes.cpp -g -o server

clean:
	rm server 