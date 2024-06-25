/**
*	Author: crylittlebear
*	Data: 2024-6-26
*/

#include "Channel.h"

Channel::Channel(int fd, int events,
				 Callback readCallback,
				 Callback writeCallback)
	: fd_(fd), events_(events),
	readCallback_(readCallback),
	writeCallback_(writeCallback) {}

void Channel::writeEnable(bool flag) {
	if (flag == true) {
		events_ |= WriteEvent;
	} else {
		events_ & ~WriteEvent;
	}
}

bool Channel::isWriteEnable() const {
	return events_ & WriteEvent;
}