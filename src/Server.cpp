#include "Server.h"
#include <iostream>
#include <unistd.h>
#include "Logger.h"

using namespace std;

namespace trickfire {

Server::Server() :
		messageThread(&Server::ServerMessageLoop, this), port(DEFAULT_PORT), msgCallback(0), connected(false) {
	messageThread.launch();
}

Server::Server(int port) :
		messageThread(&Server::ServerMessageLoop, this), port(port), msgCallback(0), connected(false) {
	messageThread.launch();
}

void Server::ServerMessageLoop() {
	Logger::Log(Logger::LEVEL_INFO,
			"Starting server at port " + to_string(port));
	if (ServerListen() != 0) {
		Logger::Log(Logger::LEVEL_ERROR_CRITICAL,
				"Error listening on port " + to_string(port));
		connected = false;
		return;
	}

	Logger::Log(Logger::LEVEL_INFO_FINE,
			"Server listening on port " + to_string(port));
	if (ServerAccept() != 0) {
		Logger::Log(Logger::LEVEL_ERROR_CRITICAL, "Error accepting connection");
		connected = false;
		return;
	}

	connected = true;

	Logger::Log(Logger::LEVEL_INFO, "Server connected to " + connection.getRemoteAddress().toString());

	while (true) {
		Packet received;

		if (connection.receive(received) != Socket::Done) {
			Logger::Log(Logger::LEVEL_ERROR, "Error receiving packet");
			break;
		}

		Logger::Log(Logger::LEVEL_INFO_VERY_FINE, "Received packet");
		msgCallback(received);
	}

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

void Server::Join() {
	messageThread.wait();
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

void Server::SetMessageCallback(void (*msgCallback)(Packet& packet)) {
	this->msgCallback = msgCallback;
}

void Server::Disconnect() {
	listener.close();
	connection.disconnect();
	connected = false;
	messageThread.terminate();
}
}
