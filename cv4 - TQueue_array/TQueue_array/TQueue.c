/** \file TQueue.c
 *  \brief Implementace API pro typ fronta (realizace pomocí kruhového pole)
 *  \author Petyovský
 *  \version 2024
 *  $Id: TQueue.c 2615 2024-02-16 15:36:07Z petyovsky $
 */

#include <assert.h>
#include "TQueue.h"

void queue_init(struct TQueue *aQueue)
	{
	if (aQueue)
		aQueue->iFrontPos = aQueue->iBackPos = 0;

	}

bool queue_is_empty(const struct TQueue *aQueue)
	{
	if (aQueue)
		{
		assert(aQueue->iFrontPos < QUEUE_MAXCOUNT && aQueue->iBackPos < QUEUE_MAXCOUNT);
		if (aQueue->iFrontPos != aQueue->iBackPos)
			return false;
		}
	return true;
	}

bool /* TQueueIterator */ queue_front(const struct TQueue *aQueue, TQueueElement *aValue)
	{
	if (!queue_is_empty(aQueue) && aValue)
		{
		*aValue = aQueue->iValues[aQueue->iFrontPos];
		return true;
		}
	return false;
	}

bool /* TQueueIterator */ queue_back(const struct TQueue *aQueue, TQueueElement *aValue)
	{
	if (!queue_is_empty(aQueue) && aValue)
		{
		size_t last_pos = aQueue->iBackPos == 0 ? QUEUE_MAXCOUNT - 1 : (aQueue->iBackPos) - 1;
		*aValue = aQueue->iValues[last_pos];
		return true;
		}
	return false;
	}

bool queue_push(struct TQueue *aQueue, TQueueElement aValue)
	{
	if (aQueue)
		{
		size_t new_back = ((aQueue->iBackPos)+1) % QUEUE_MAXCOUNT;
		if (new_back == aQueue->iFrontPos)
			return false;
		aQueue->iValues[aQueue->iBackPos] = aValue;
		aQueue->iBackPos = new_back;
		return true;
		}
	return false;
	}

bool queue_pop(struct TQueue *aQueue)
	{
	if (!queue_is_empty(aQueue))
		{
		aQueue->iFrontPos = (++aQueue->iFrontPos) % QUEUE_MAXCOUNT;
		return true;
		}
	return false;
	}

void queue_destroy(struct TQueue *aQueue)
	{
	if (aQueue)
		queue_init(aQueue);
	}

struct TQueueIterator queue_iterator_begin(const struct TQueue *aQueue)
	{
	if (aQueue)
		return (struct TQueueIterator) { .iQueue = aQueue, .iPos = aQueue->iFrontPos };

	return (struct TQueueIterator) { .iQueue = NULL, .iPos = 0 };
	}

bool queue_iterator_is_valid(const struct TQueueIterator *aIter)
	{
	if (aIter && !queue_is_empty(aIter->iQueue))
		{
		if (aIter->iQueue->iFrontPos < aIter->iQueue->iBackPos)	
			return ((aIter->iPos >= aIter->iQueue->iFrontPos) && (aIter->iPos < aIter->iQueue->iBackPos));
		
		else
			return ((aIter->iPos >= aIter->iQueue->iFrontPos) || (aIter->iPos < aIter->iQueue->iBackPos));
		}
	return false;
	}

bool queue_iterator_to_next(struct TQueueIterator *aIter)
	{
	if (queue_iterator_is_valid(aIter))
		{
		aIter->iPos = ++aIter->iPos%QUEUE_MAXCOUNT;
		return queue_iterator_is_valid(aIter);
		}
	queue_iterator_begin(aIter);
	return false;
	}

TQueueElement queue_iterator_value(const struct TQueueIterator *aIter)
	{
	if (queue_iterator_is_valid(aIter))
		return aIter->iQueue->iValues[aIter->iPos];

	return (TQueueElement) { 0 };
	}

bool queue_iterator_set_value(const struct TQueueIterator *aIter, TQueueElement aValue)
	{
	if (queue_iterator_is_valid(aIter))
		((struct TQueue*) aIter->iQueue)->iValues[aIter->iPos] = aValue;
	return false;
	}
