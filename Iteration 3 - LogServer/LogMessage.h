//
// Created by Ethan on 12/5/2019.
//

#ifndef LOGSERVER_LOGMESSAGE_H
#define LOGSERVER_LOGMESSAGE_H

struct LogMessage {
    int command;
    char data[1024];
};

#endif //LOGSERVER_LOGMESSAGE_H
