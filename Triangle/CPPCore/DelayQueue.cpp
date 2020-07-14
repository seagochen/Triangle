#include "DelayTaskQueue.h"
#include <iostream>
#include <memory.h>
#include <string.h>

#ifndef INT_MAX
#define INT_MAX	0x7FFFFFFF
#endif

#ifndef MILLION
#define MILLION 1000000
#endif

#define ZERO    0
#define SECOND  1
#define MINUTE  60
#define HOUR    MINUTE*60
#define DAY     HOUR*24

const Timeval DELAY_ZERO(ZERO);
const Timeval DELAY_SECOND(SECOND);
const Timeval DELAY_MINUTE(MINUTE);
const Timeval DELAY_HOUR(HOUR);
const Timeval DELAY_DAY(DAY);
const Timeval ETERNITY(INT_MAX, MILLION - 1);

#define TIME_NOW time_since1970();

Timeval tempval;
Timeval& operator-(Timeval const& arg1, Timeval const& arg2) {
	double darg1 = arg1.toVal();
	double darg2 = arg2.toVal();
	
	tempval.fromVal(darg1 - darg2);
	return tempval;
}

void DelayQueue::synchronize()
{
	// first, figure out how much time has elapsed since last synchronized
	Timeval timeNow = TIME_NOW;

	// the system clock has apparently gone back in time; reset  
	if (timeNow < lastSyncTime) {
		lastSyncTime = TIME_NOW;
		return;
	}

	// the period between last synchronizing time
	Timeval lastSyncPeriod(timeNow.toVal() - lastSyncTime.toVal());
	lastSyncTime = timeNow;

	// then adjust the delay queue for any entries whose time is up
	for (Iterator<DelayQueueEntry>* itr = container.iterator(); itr->has_next(); itr->next()) {
		DelayQueueEntry* entry = itr->ptr();

		// errors handling
		if (entry == nullptr) {
			std::cerr << "iterate delay queue failed" << std::endl;
			return;
		}

		// period since last synchronized will to be zero, and break the cycle
		if (entry->timeRemaining > lastSyncPeriod) {
			entry->timeRemaining -= lastSyncPeriod;
			break;
		}

		// set the entry's delta time remaining to zero
		lastSyncPeriod -= entry->timeRemaining;
		entry->timeRemaining = DELAY_ZERO;
	}
}

DelayQueue::DelayQueue()
{
	// time now
	lastSyncTime = TIME_NOW;

	// add the first delay to queue
	DelayQueueEntry entry;
	entry.timeRemaining = ETERNITY;
	add(entry);
}

DelayQueue::~DelayQueue() {  /* nothing need to do */ }

void DelayQueue::add(DelayQueueEntry& newEntry)
{
	synchronize();

	int anchor = 0;
	for (Iterator<DelayQueueEntry>* itr = container.iterator(); itr->has_next(); itr->next()) {
		DelayQueueEntry* entry = itr->ptr();

		// some unknown errors occurs
		if (entry == nullptr) {
			std::cerr << "iterate delay queue failed" << std::endl;
			return;
		}

		if (newEntry.timeRemaining < entry->timeRemaining) {
			break; // this means the entry should be insert to front of the task
		}

		newEntry.timeRemaining -= entry->timeRemaining;
		anchor += 1;
	}

	// insert the entry to the correct position
	newEntry.setId(ids++);
	container.insert(newEntry, anchor);
}

void DelayQueue::update(DelayQueueEntry& entry, Timeval& newDelay)
{
	// remove entry from queue
	DelayQueueEntry* ptr = remove(entry);

	// nothing found
	if (ptr == nullptr) { return; }

	// update delay
	ptr->timeRemaining = newDelay;

	// insert entry to queue again
	add(*ptr);
}

void DelayQueue::update(size_n tokenToFind, Timeval& newDelay)
{
	// remove entry from queue
	DelayQueueEntry* ptr = remove(tokenToFind);

	// nothing found
	if (ptr == nullptr) { return; }

	// update delay
	ptr->timeRemaining = newDelay;

	// insert entry to queue again
	add(*ptr);
}

DelayQueueEntry* DelayQueue::remove(DelayQueueEntry& entry)
{
	return remove(entry.getId());
}


DelayQueueEntry* DelayQueue::remove(size_n tokenToFind)
{
	// no elements inside
	if (container.length() <= 0) return nullptr;

	// memset
	DelayQueueEntry* entry = (DelayQueueEntry*)malloc(sizeof(DelayQueueEntry));
	memset(entry, 0, sizeof(DelayQueueEntry));

	// trying to delete a node by given id
	int anchor = 0;
	for (Iterator<DelayQueueEntry>* itr = container.iterator(); itr->has_next(); itr->next())
	{
		if (itr->ptr() != nullptr and itr->ptr()->getId() == tokenToFind) { // find the target
			container.pick(anchor, *entry);
		}

		anchor += 1;
	}

	// return to caller
	return entry;
}

Timeval const* DelayQueue::timeToNextAlarm()
{
	// if queue is empty
	if (container.length() <= 0) return nullptr;

	if (container.access(0)->timeRemaining == DELAY_ZERO)
		return &DELAY_ZERO;

	synchronize();

	return &container.access(0)->timeRemaining;
}

void DelayQueue::handleAlarm()
{
	// if queue is empty
	if (container.length() <= 0) return;

	// update the scheduler timetable
	if (container.access(0)->timeRemaining != DELAY_ZERO) synchronize();

	// if the header task is timeout!
	if (container.access(0)->timeRemaining == DELAY_ZERO) {

		// the entry to hold
		DelayQueueEntry entry;

		// popup
		container.popup(entry);

		// trigger the callback
		entry.triggerCallback();
	}
}

#include <iostream>

void DelayQueue::print()
{
	if (container.length() <= 0) {
		std::cout << "queue is empty" << std::endl;
		return;
	}

	std::cout << "tokenID/delaytime(s)..." << std::endl;

	for (Iterator<DelayQueueEntry>* itr = container.iterator(); itr->has_next(); itr->next()) {
		DelayQueueEntry* entry = itr->ptr();

		if (entry == nullptr) {
			std::cerr << "uncertain error occurs" << std::endl;
			return;
		}

		std::cout << entry->getId()
			<< "/" << entry->timeRemaining.toVal() << " | ";
	}

	std::cout << std::endl;
}

inline size_n DelayQueue::length()
{
	return container.length();
}
