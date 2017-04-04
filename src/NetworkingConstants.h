#ifndef NETWORKINGCONSTANTS_H_
#define NETWORKINGCONSTANTS_H_

#define DRIVE_PACKET 1
#define CAMERA_PACKET 2
#define MINER_MOVE_PACKET 3 // -1 to lower, 1 to raise, 0 to stop
#define MINER_SPIN_PACKET 4 // -1 to empty, 1 to dig, 0 to stop
#define BIN_SLIDE_PACKET 5 // -1 to slide to fill, 1 to slide to dump, 0 to stop
#define CONVEYOR_PACKET 6 // No parameters

#endif
