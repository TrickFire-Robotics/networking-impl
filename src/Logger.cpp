#include "Logger.h"

namespace trickfire {

int Logger::loggingLevel = Logger::LEVEL_INFO_VERY_FINE;

void Logger::Log(int level, std::string message) {
	if (level <= loggingLevel) {
		std::cout << "[TrickFire Logger - " << LevelToString(level) << "] "
				<< message << std::endl;
	}
}

std::string Logger::LevelToString(int level) {
	switch (level) {
	case LEVEL_NONE:
		return "None";
	case LEVEL_ERROR_CRITICAL:
		return "CRITICAL ERROR";
	case LEVEL_ERROR_IMPORTANT:
		return "Important Error";
	case LEVEL_ERROR:
		return "Error";
	case LEVEL_WARNING:
		return "Warning";
	case LEVEL_INFO_CRITICAL:
		return "CRITICAL INFO";
	case LEVEL_INFO_IMPORTANT:
		return "Important Info";
	case LEVEL_INFO:
		return "Info";
	case LEVEL_INFO_FINE:
		return "Info (fine)";
	case LEVEL_INFO_VERY_FINE:
		return "Info (very fine)";
	}
	return "[undefined logger level]";
}
}

