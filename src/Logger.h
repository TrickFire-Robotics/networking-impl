#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>

namespace trickfire {

class Logger {
public:
	static const int LEVEL_NONE = 0; // (used in setting level to just say to not log anything)
	static const int LEVEL_ERROR_CRITICAL = 1; // An error that is absurd and absolutely breaks stuff
	static const int LEVEL_ERROR_IMPORTANT = 2; // An error that has a major impact on the program run
	static const int LEVEL_ERROR = 3; // A general error, survivable but definitely notable
	static const int LEVEL_WARNING = 4; // A mild error that is survivable but possibly worth noting
	static const int LEVEL_INFO_CRITICAL = 5; // Information that the user HAS to know
	static const int LEVEL_INFO_IMPORTANT = 6; // Information that is important (large program changes, milestones, etc.)
	static const int LEVEL_INFO = 7; // Generic status update
	static const int LEVEL_INFO_FINE = 8; // Fine logging, not quite method for method but still very verbose
	static const int LEVEL_INFO_VERY_FINE = 9; // Absurd console-spam level of logging

	static inline void Log(int level, std::string message) {
		if (level <= loggingLevel) {
			std::cout << "[TrickFire Logger - " << LevelToString(level) << "] " << message << std::endl;
		}
	}
	static inline void SetLoggingLevel(int level) {
		loggingLevel = level;
	}
private:
	static int loggingLevel;

	static inline std::string LevelToString(int level) {
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
};

int Logger::loggingLevel = Logger::LEVEL_INFO;
}

#endif /* LOGGER_H_ */
