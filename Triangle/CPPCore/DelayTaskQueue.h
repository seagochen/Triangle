#pragma once
#ifndef _TRI_DELAY_TASK_QUEUE_H_
#define _TRI_DELAY_TASK_QUEUE_H_

#include "../Core/TypeDef.h"
#include "../Core/SysInterfaces.h"
#include "ListContainer.hpp"
#include "Timeval.h"
#include <vector>

// callback
typedef void TaskFunc(void* data);

// DelayQueueEntry, is for task scheduling, user should manually call 
// the triggerCallback function when a entry is finished its lifecycle.
// This set of components can be extended and applied to a variety
// of programs that require resource scheduling.
class DelayQueueEntry {
private:
	TaskFunc* function;
	void* data;
	size_n datasize;
	size_n id = 0; // default event id

public:
	Timeval timeRemaining;

public:
	DLL_EXPO DelayQueueEntry();

	DLL_EXPO DelayQueueEntry(Timeval& delayTime,
		TaskFunc* proc = nullptr, void* data = nullptr, size_n size = 0);

	DLL_EXPO void triggerCallback();

	DLL_EXPO void setId(size_n id);

	DLL_EXPO size_n getId();

	DLL_EXPO void setDelayTime(Timeval const& delayTime);

	DLL_EXPO Timeval const& getDelayTime();

	DLL_EXPO void setCallback(TaskFunc* proc, void* data, size_n size);

	DLL_EXPO TaskFunc* getCallback();

	DLL_EXPO void const* getData();

	DLL_EXPO size_n getDataSize();

    DLL_EXPO static DelayQueueEntry& createEntry(Timeval& delayTime,
        TaskFunc* proc = nullptr, void* data = nullptr, size_n size = 0);

    DLL_EXPO static DelayQueueEntry& createEntry(double delayTime,
        TaskFunc* proc = nullptr, void* data = nullptr, size_n size = 0);
};

class DelayQueue {

	/**
	* delay timetable: | 0.1| 0.3| 0.5| 0.9| 0.91| ...
	* task token id  : | 0x3| 0x6| 0x9| 0xA| 0x51| ...
	*
	* trying to insert a new task (0.7, 0xC), the new entry will be inserted before 0x9
	* 0.7 = 0.1 + 0.3 + (0.3), however, the 0.3 is less than 0.5
	* delay timetable: | 0.1| 0.3| 0.3| 0.5| 0.9| 0.91| ...
	* task token id  : | 0x3| 0x6| 0xC| 0x9| 0xA| 0x51| ...
	*
	* a period for example is 0.9s, after called synchronize, the queue should be:
	* 0.9 = 0.1 + 0.3 + 0.3 + (0.5-0.2)
	* delay timetable: | 0.0| 0.0| 0.0| 0.3| 0.9| 0.91| ...
	* task token id  : | 0x3| 0x6| 0xC| 0x9| 0xA| 0x51| ...
	*
	* after handleAlarm, remove the first item if its delay time is already zero:
	* delay timetable: | 0.0| 0.0| 0.3| 0.9| 0.91| ...
	* task token id  : | 0x6| 0xC| 0x9| 0xA| 0x51| ...
	*/

private:
	void synchronize();

	size_n ids = 0;

public:
	// default constructor
	DLL_EXPO DelayQueue();

	// deconstructor
	DLL_EXPO ~DelayQueue();

	// add entry to queue
	DLL_EXPO void add(DelayQueueEntry& entry);

	DLL_EXPO void update(DelayQueueEntry& entry, Timeval& newDelay);

	DLL_EXPO void update(size_n idToFind, Timeval& newDelay);

	DLL_EXPO DelayQueueEntry* remove(DelayQueueEntry& entry);

	DLL_EXPO DelayQueueEntry* remove(size_n idToFind);

	DLL_EXPO Timeval const* timeToNextAlarm();

	DLL_EXPO void handleAlarm();

	DLL_EXPO void print();

	DLL_EXPO size_n length();

private://// variables

	// container
	ListContainer<DelayQueueEntry> container;

	// last sync time to handle alarm event
	Timeval lastSyncTime;
};

#endif