#include "Server.h"
#include <iostream>
#include <unistd.h>
#include "Logger.h"

using namespace std;

namespace trickfire {

Server::Server() :
		port(DEFAULT_PORT), connected(false), msgCallback(NULL) {
	pthread_create(&messageThread, NULL, _ServerMessageLoopWrapper,
			(void *) this);
}

Server::Server(int port) :
		port(port), connected(false), msgCallback(NULL) {
	pthread_create(&messageThread, NULL, _ServerMessageLoopWrapper,
			(void *) this);
}

void * Server::ServerMessageLoop() {
	Logger::Log(Logger::LEVEL_INFO,
			"Starting server at port " + to_string(port));
	if (ServerListen() != 0) {
		Logger::Log(Logger::LEVEL_ERROR_CRITICAL,
				"Error listening on port " + to_string(port));
		connected = false;
		pthread_exit(&messageThread);
	}
	Logger::Log(Logger::LEVEL_INFO_FINE,
			"Server listening on port " + to_string(port));
	if (ServerAccept() != 0) {
		Logger::Log(Logger::LEVEL_ERROR_CRITICAL, "Error accepting connection");
		connected = false;
		pthread_exit(&messageThread);
	}

	connected = true;

	while (true) {
		Packet received;

		if (connection.receive(received) != Socket::Done) {
			Logger::Log(Logger::LEVEL_ERROR, "Error receiving packet");
			break;
		}

		Logger::Log(Logger::LEVEL_INFO_VERY_FINE, "Received packet");
		msgCallback(received);
	}

	pthread_exit((void*) messageThread);
	connected = false;
}

int Server::ServerListen() {
	if (listener.listen(port) != Socket::Done) {
		connected = false;
		return 1;
	}
	return 0;
}

int Server::ServerAccept() {
	if (listener.accept(connection) != Socket::Done) {
		connected = false;
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

int Server::Send(Packet& packet) {
	Logger::Log(Logger::LEVEL_INFO_VERY_FINE, "Server sending packet");
	if (connection.send(packet) != Socket::Done) {
		Logger::Log(Logger::LEVEL_ERROR, "Error sending packet");
		connected = false; // TODO: Is this a good idea? Probably not, get a better idea.
		return 1;
	}
	return 0;
}

int Server::operator<<(Packet& packet) {
	return Send(packet);
}

void Server::SetMessageCallback(void (*msgCallback)(Packet& packet)) {
	this->msgCallback = msgCallback;
}

void Server::Disconnect() {
	listener.close();
	connection.disconnect();
	connected = false;
}
}
