#include "Client.h"
#include "Server.h"
#include "Logger.h"
#include <iostream>

namespace trickfire {

Client::Client(std::string address) :
		address(address), port(DEFAULT_PORT), sfmlMessageThread(
				&Client::SfmlMessageListeningLoop, this) {
	Logger::Log(Logger::LEVEL_INFO,
			"Client connecting to server at " + address + ":"
					+ std::to_string(port));

	if (Connect() != 0) {
		Logger::Log(Logger::LEVEL_ERROR_CRITICAL,
				"Couldn't connect to server at " + address + ":"
						+ std::to_string(port));
	} else {
		Logger::Log(Logger::LEVEL_INFO, "Client connected to server");
		sfmlMessageThread.launch();
	}
}

Client::Client(std::string address, int port) :
		address(address), port(port), sfmlMessageThread(
				&Client::SfmlMessageListeningLoop, this) {
	Logger::Log(Logger::LEVEL_INFO,
			"Client connecting to server at " + address + ":"
					+ std::to_string(port));

	if (Connect() != 0) {
		Logger::Log(Logger::LEVEL_ERROR_CRITICAL,
				"Couldn't connect to server at " + address + ":"
						+ std::to_string(port));
	} else {
		Logger::Log(Logger::LEVEL_INFO, "Client connected to server");
		sfmlMessageThread.launch();
	}
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

void Client::SetMessageCallback(void (*msgCallback)(Packet&)) {
	this->msgCallback = msgCallback;
}

void Client::SfmlMessageListeningLoop() {
	Logger::Log(Logger::LEVEL_INFO_FINE,
			"Starting message listening loop thread.");
	_connected = true;

	while (_connected) {
		Packet received;

		if (socket.receive(received) != Socket::Done) {
			Logger::Log(Logger::LEVEL_ERROR, "Error receiving packet");
			_connected = false;
			break;
		}

		Logger::Log(Logger::LEVEL_INFO_VERY_FINE, "Received packet");
		msgCallback(received);
	}
}

void Client::Disconnect() {
	Logger::Log(Logger::LEVEL_INFO, "Client disconnecting");
	socket.disconnect();
	_connected = false;
}

void Client::Join() {
	sfmlMessageThread.wait();
}
}
