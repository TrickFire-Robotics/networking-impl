#include "Server.h"
#include <iostream>
#include <unistd.h>
#include "Logger.h"

using namespace std;

namespace trickfire {

Server::Server() :
		port(DEFAULT_PORT) {
	Start();
}

Server::Server(int port) :
		port(port) {
	Start();
}

void * Server::MainServerLoop() {
	Logger::Log(Logger::LEVEL_INFO, "Starting server at port " + to_string(port));
	Logger::Log(Logger::LEVEL_INFO_FINE, "Server listening on port " + to_string(port));
	if (ServerListen() != 0) {
		Logger::Log(Logger::LEVEL_ERROR_CRITICAL,
				"Error listening on port " + to_string(port));
		pthread_exit((void*) mainThread);
	}
	if (ServerAccept() != 0) {
		Logger::Log(Logger::LEVEL_ERROR_CRITICAL, "Error accepting connection");
		pthread_exit((void*) mainThread);
	}

	Logger::Log(Logger::LEVEL_INFO_FINE, "Server accepted connection");

	while (true) {
		Packet received;

		if (connection.receive(received) != Socket::Done) {
			Logger::Log(Logger::LEVEL_ERROR, "Error receiving packet");
			break;
		}

		Logger::Log(Logger::LEVEL_INFO_VERY_FINE, "Received packet");

		while (!received.endOfPacket()) {
			int val;
			received >> val;
			cout << val << endl;
		}
	}

	pthread_exit((void*) mainThread);
}

int Server::ServerListen() {
	if (listener.listen(port) != Socket::Done) {
		return 1;
	}
	return 0;
}

int Server::ServerAccept() {
	if (listener.accept(connection) != Socket::Done) {
		return 1;
	}
	return 0;
}

void Server::Start() {
	pthread_create(&mainThread, NULL, _ServerLoopWrapper, (void *) this);
}

void * Server::_ServerLoopWrapper(void * server) {
	return ((Server *) server)->MainServerLoop();
}

void Server::Join() {
	pthread_join(mainThread, NULL);
}
}
