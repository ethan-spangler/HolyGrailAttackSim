//
// Created by Ethan on 10/17/2019.
//

#ifndef LOGGING_ATTMESS_H
#define LOGGING_ATTMESS_H
struct Message {
    int from; // Who sent this Message: 0 = Castle, 1 = First Knight, etc.
    int type; // 0 = taunt, 1 = cow, 2 = rabbit, 3 = knight
    int damage;
};
#endif //LOGGING_ATTMESS_H
