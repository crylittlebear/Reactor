/**
*	Author: crylittlebear
*	Data: 2024-6-25
*/

#include "Buffer.h"

Buffer::Buffer(std::size_t initSize) 
	: data_(new char[initSize]), 
	readPos_(0),
	writePos_(0),
	capacity_(initSize) {}

Buffer::~Buffer() { delete [] data_; }

void Buffer::setReadPos(std::size_t pos) { readPos_ = pos; }

void Buffer::setWritePos(std::size_t pos) { writePos_ = pos; }

std::size_t Buffer::readPos() const { return readPos_; }

std::size_t Buffer::writePos() const { return writePos_; }

std::size_t Buffer::readableSize() const { 
	assert(writePos_ >= readPos_);
	return writePos_ - readPos_;
}

std::size_t Buffer::writableSize() const {
	assert(capacity_ >= writePos_);
	return capacity_ - writePos_;
}

void Buffer::append(const std::string& str) {
	append(str.c_str());
}

void Buffer::append(const char* str) {
	append(str, strlen(str));
}
void Buffer::append(const char* str, std::size_t len) {
	// 首先保证有足够的可写空间
	makeRoom(len);
	memcpy(data_ + writePos_, str, len);
}

void Buffer::append(const Buffer& buf) {
	append(buf.data_ + buf.readPos_,  buf.readableSize());
}

ssize_t Buffer::readFromFd(int fd) {
	char buf[65536];
	struct iovec iov[2];
	std::size_t writable = writableSize();
	iov[0].iov_base = data_ + writePos_;
	iov[0].iov_len = writable;
	iov[1].iov_base = buf;
	iov[1].iov_len = sizeof buf;
	ssize_t len = readv(fd, iov, 2);
	if (len < 0) {
		// TO DO(添加打印信息)
	} else if (len <= writable) {
		writePos_ += len;
	} else {
		writePos_ += capacity_;
		append(buf, len - writable);
	}
	return len;
}

ssize_t Buffer::writeToFd(int fd) {
	int readable = readableSize();
	ssize_t len = write(fd, data_ + readPos_, readable);
	if (len < 0) {
		// TO DO (添加打印信息)
	} else {
		readPos_ += readable;
	}
	return len;
}

void Buffer::makeRoom(std::size_t reqSize) {
	// 如果可写的空间大于需要写的空间大小
	if (writableSize() >= reqSize) { return; }
	// 如果合并后的可写空间大小大于等于需要写的空间大小
	if (readPos_ + writableSize() >= reqSize) {
		// 移动数据
		memcpy(data_, data_ + readPos_, readableSize());
		// 更新读写位置
		writePos_ = readableSize();
		readPos_ = 0;
		return;
	}
	// 如果合并后的数据依然不够需要空间的大小，重新分配内存
	std::size_t newSize = capacity_ + reqSize;
	char* temp = new char[newSize];
	// 将原内存上的数据移动到新分配的空间中
	memcpy(temp, data_, writePos_);
	// 释放原有的空间
	delete[] data_;
	// 更新数组容量大小
	capacity_ = newSize;
}