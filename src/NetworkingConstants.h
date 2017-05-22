#ifndef NETWORKINGCONSTANTS_H_
#define NETWORKINGCONSTANTS_H_

#define DRIVE_PACKET 1
#define CAMERA_PACKET 2
#define MINER_MOVE_S1_PACKET 3 // -1 to lower, 1 to raise, 0 to stop, L and then R doubles for speed
#define MINER_MOVE_S2_PACKET 4 // -1 to lower, 1 to raise, 0 to stop
#define MINER_SPIN_PACKET 5 // -1 to empty, 1 to dig, 0 to stop
#define BIN_SLIDE_PACKET 6 // -1 to slide to fill, 1 to slide to dump, 0 to stop, 2/-2 makes it extended
#define CONVEYOR_PACKET 7 // 1 to fill, 0 to stop

#endif
