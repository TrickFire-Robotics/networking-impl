#include "Client.h"
#include "Server.h"
#include "Logger.h"
#include <iostream>

namespace trickfire {

Client::Client(std::string address) :
		address(address), port(DEFAULT_PORT) {
	Logger::Log(Logger::LEVEL_INFO,
			"Client connecting to server at " + address + ":"
					+ std::to_string(port));

	if (Connect() != 0) {
		Logger::Log(Logger::LEVEL_ERROR_CRITICAL,
				"Couldn't connect to server at " + address + ":"
						+ std::to_string(port));
	} else {
		Logger::Log(Logger::LEVEL_INFO, "Client connected to server");
	}
}

Client::Client(std::string address, int port) :
		address(address), port(port) {
	Connect();
}

int Client::Connect() {
	if (socket.connect(address, port) != Socket::Done) {
		return 1;
	}
	return 0;
}

int Client::Send(Packet& packet) {
	Logger::Log(Logger::LEVEL_INFO_VERY_FINE, "Client sending packet");
	if (socket.send(packet) != Socket::Done) {
		Logger::Log(Logger::LEVEL_ERROR, "Error sending packet");
		return 1;
	}
	return 0;
}

int Client::operator<<(Packet& packet) {
	return Send(packet);
}

void Client::Disconnect() {
	Logger::Log(Logger::LEVEL_INFO, "Client disconnecting");
	socket.disconnect();
}
}
