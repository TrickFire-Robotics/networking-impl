#include "Server.h"
#include <iostream>
#include <unistd.h>
#include "Logger.h"

using namespace std;

namespace trickfire {

Server::Server() :
		port(DEFAULT_PORT) {
	if (Start() != 0) {
		Logger::Log(Logger::LEVEL_ERROR_CRITICAL, "Failed to start server.");
	} else {
		Logger::Log(Logger::LEVEL_INFO, "Server started");
		pthread_create(&messageThread, NULL, _ServerMessageLoopWrapper,
				(void *) this);
	}
}

Server::Server(int port) :
		port(port) {
	if (Start() != 0) {
		Logger::Log(Logger::LEVEL_ERROR_CRITICAL, "Failed to start server.");
	} else {
		Logger::Log(Logger::LEVEL_INFO, "Server started");
		pthread_create(&messageThread, NULL, _ServerMessageLoopWrapper,
				(void *) this);
	}
}

void * Server::ServerMessageLoop() {
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

			Packet tr;
			tr << val;

			if (connection.send(tr) != Socket::Done) {
				Logger::Log(Logger::LEVEL_ERROR, "Error sending packet");
			}
		}
	}

	pthread_exit((void*) messageThread);
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

int Server::Start() {
	Logger::Log(Logger::LEVEL_INFO,
			"Starting server at port " + to_string(port));
	if (ServerListen() != 0) {
		Logger::Log(Logger::LEVEL_ERROR_CRITICAL,
				"Error listening on port " + to_string(port));
		return 1;
	}
	Logger::Log(Logger::LEVEL_INFO_FINE,
			"Server listening on port " + to_string(port));
	if (ServerAccept() != 0) {
		Logger::Log(Logger::LEVEL_ERROR_CRITICAL, "Error accepting connection");
		return 1;
	}

	return 0;
}

void * Server::_ServerMessageLoopWrapper(void * server) {
	return ((Server *) server)->ServerMessageLoop();
}

void Server::Join() {
	pthread_join(messageThread, NULL);
}
}
