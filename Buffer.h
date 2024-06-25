/**
*	Author: crylittlebear
*	Data: 2024-6-25
*/

#pragma once

#include <cctype>
#include <cstring>
#include <cassert>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/uio.h>

const int initBufferSize = 10240;

class Buffer {
public:
	Buffer(std::size_t initSize = initBufferSize);
	~Buffer();
	
	// 获取和设置成员
	void setReadPos(std::size_t pos);
	void setWritePos(std::size_t pos);
	std::size_t readPos() const;
	std::size_t writePos() const;

	// 可读取的字节数
	std::size_t readableSize() const;
	// 可写的字节数
	std::size_t writableSize() const;

	// 往buffer中追加数据
	void append(const std::string& str);
	void append(const char* str);
	void append(const char* str, std::size_t len);
	void append(const Buffer& buf);

	// 从文件描述符中读写数据
	ssize_t readFromFd(int fd);
	ssize_t writeToFd(int fd);
	
	// 打印输出可读数据
	void printReadable();

private:
	// 检查可写容量是否够写，如果不够重新分配内存
	void makeRoom(std::size_t reqSize);

private:
	char* data_;
	// buffer中读取的起始位置
	std::size_t readPos_;
	// buffer中写入的起始位置
	std::size_t writePos_;
	// 申请的数组总容量
	std::size_t capacity_;
}; // class Buffer


