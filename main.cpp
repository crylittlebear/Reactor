#include <iostream>

#include "Buffer.h"
#include "TimeStamp.h"
#include "Logger.h"

int main(int argc, char* argv[]) {	
	Buffer buf1, buf2;
	std::string str = "I am a string";
	buf1.append("hello world");
	buf1.printReadable();
	buf1.append("nihaoshijie", 6);
	buf1.printReadable();
	buf1.append(str);
	buf1.printReadable();
	buf2.append("i am buf2");
	buf2.printReadable();
	buf1.append(buf2);
	buf1.printReadable();
	return 0;
}