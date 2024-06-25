/**
*	Author: crylittlebear
*	Data: 2024-6-26
*/

#pragma once

#include <functional>

enum EventMode {
	TimeOut = 0x01,
	ReadEvent = 0x02,
	WriteEvent = 0x04
};

using Callback = std::function<int(void*)>;

class Channel {
public:
	Channel(int fd, 
			int events,
			Callback readCall, 
			Callback writeCall);
	~Channel() = default;

	void writeEnable(bool flag = true);

	bool isWriteEnable() const;
private:
	int fd_;
	int events_;
	EventMode eventMode_;
	Callback readCallback_;
	Callback writeCallback_;
};

