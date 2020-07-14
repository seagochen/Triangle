#include "DelayTaskQueue.h"
#include <memory.h>
#include <iostream>

DelayQueueEntry::DelayQueueEntry() : 
	function(nullptr), data(nullptr), timeRemaining(0), datasize(0)
{ /* nothing need to do */ }

DelayQueueEntry::DelayQueueEntry(Timeval& delayTime, TaskFunc* proc, void* d, size_n s) :
	timeRemaining(delayTime), function(proc), data(nullptr), datasize(0)
{
	if (d != nullptr && s > 0) {
		data = malloc(s);

		if (data == nullptr) {
			std::cerr << "malloc space for delay queue entry failed" << std::endl;
			return;
		}

		memcpy(data, d, s);
		datasize = s;
	}
}

void DelayQueueEntry::triggerCallback()
{
	if (function != nullptr) (*function)(data);
	if (data != nullptr) { SAFE_FREE(data); }
}

void DelayQueueEntry::setId(size_n id)
{
	this->id = id;
}

size_n DelayQueueEntry::getId()
{
	return id;
}

void DelayQueueEntry::setDelayTime(Timeval const& delayTime)
{
	timeRemaining = delayTime;
}

Timeval const& DelayQueueEntry::getDelayTime()
{
	return timeRemaining;
}

void DelayQueueEntry::setCallback(TaskFunc* proc, void* ptr, size_n size)
{
	function = proc;

	if (function != nullptr) {
		// free data first
		SAFE_FREE(data);

		if (ptr != nullptr and size > 0) {
			data = malloc(size);

			if (data == nullptr) {
				std::cerr << "malloc space for delay queue entry failed" << std::endl;
				return;
			}

			memcpy(data, ptr, size);
			datasize = size;
		}
	}
}

TaskFunc* DelayQueueEntry::getCallback()
{
	return function;
}

void const* DelayQueueEntry::getData()
{
	return data;
}

size_n DelayQueueEntry::getDataSize()
{
	return datasize;
}

/// this entry is used for rapidly creating an entry to delay queue
DelayQueueEntry tempEntry;

DelayQueueEntry& DelayQueueEntry::createEntry(Timeval& delayTime, TaskFunc* proc, void* data, size_n size)
{
    tempEntry.setDelayTime(delayTime);
    tempEntry.setCallback(proc, data, size);
    tempEntry.setId(0);

    // return the temporary entry to caller
    return tempEntry;
}


DelayQueueEntry& DelayQueueEntry::createEntry(double delayTime, TaskFunc* proc, void* data, size_n size)
{
    tempEntry.setDelayTime(delayTime);
    tempEntry.setCallback(proc, data, size);
    tempEntry.setId(0);

    // return the temporary entry to caller
    return tempEntry;
}