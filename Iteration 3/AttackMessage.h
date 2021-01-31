//
// Created by Ethan on 11/30/2019.
//

#ifndef HW6_ATTACKMESSAGE_H
#define HW6_ATTACKMESSAGE_H
struct Message {
    int from; // Who sent this Message: 0 = Castle, 1 = First Knight, etc.
    int type; // 0 = taunt, 1 = cow, 2 = rabbit, 3 = knight
    int damage;
};
#endif //HW6_ATTACKMESSAGE_H
