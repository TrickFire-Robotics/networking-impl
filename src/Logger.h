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

	/**
	 * Log a message to the console with the specified level
	 */
	static void Log(int level, std::string message);

	/**
	 * Set the minimum logging level to actually output at (for example, if I say LEVEL_INFO here, it will log everything from LEVEL_INFO all the way to LEVEL_ERROR_CRITICAL).
	 */
	static inline void SetLoggingLevel(int level) {
		loggingLevel = level;
	}
private:
	/**
	 * The minimum logging level to output at.
	 */
	static int loggingLevel;

	/**
	 * Basically a ToString method for all of the level variables above.
	 */
	static std::string LevelToString(int level);
};
}

#endif /* LOGGER_H_ */
