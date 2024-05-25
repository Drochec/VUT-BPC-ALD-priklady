/** \file TQueue.c
 *  \brief Implementace API pro typ fronta (realizace pomocí lineárního jednosměrně vázaného seznamu)
 *  \author Petyovský
 *  \version 2024
 *  $Id: TQueue.c 2616 2024-02-16 15:36:28Z petyovsky $
 */

#include <assert.h>
#include "TQueue.h"

/** \brief Úplná definice privátního typu QueueNode
 *  \details Privátní typ QueueNode (nedostupný mimo funkce ze souboru TQueue.c) reprezentuje typ pro jednotlivé uzly lineárního jednosměrně vázaného seznamu.
 */
struct TQueueNode
	{
	struct TQueueNode *iNext;				///< Ukazatel na následující uzel lineárního jednosměrně vázaného seznamu
	TQueueElement iValue;					///< Element fronty uložený v uzlu lineárního jednosměrně vázaného seznamu
	};

void queue_init(struct TQueue *aQueue)
	{
	if (aQueue)
		*aQueue = (struct TQueue){ .iFront = NULL, .iBack = NULL };
	}

bool queue_is_empty(const struct TQueue *aQueue)
	{
	if (aQueue)
		{
		assert((aQueue->iBack && aQueue->iFront) || (!aQueue->iBack && !aQueue->iFront));
		if (aQueue->iFront)
			return false;
		}
	return true;
	}

bool /* TQueueIterator */ queue_front(const struct TQueue *aQueue, TQueueElement *aValue)
	{
	if (!queue_is_empty(aQueue) && aValue)
		{
		*aValue = aQueue->iFront->iValue;
		return true;
		}
	
	return false;
	}

bool /* TQueueIterator */ queue_back(const struct TQueue *aQueue, TQueueElement *aValue)
	{
	if (aQueue && !queue_is_empty(aQueue) && aValue)
		{
		aQueue->iBack->iValue = *aValue;
		return true;
		}

	return false;
	}

bool queue_push(struct TQueue *aQueue, TQueueElement aValue)
	{
	if (!aQueue)
		return false;

	struct TQueueNode* new_node = malloc(sizeof(struct TQueueNode));
	if (!new_node)
		return false;

	*new_node = (struct TQueueNode){ .iNext = NULL, .iValue = aValue };

	if (queue_is_empty(aQueue))
		{
		*aQueue = (struct TQueue){ .iFront = new_node, .iBack = new_node };
		return true;
		}

	aQueue->iBack->iNext = new_node;
	aQueue->iBack = new_node;

	return true;
	}

bool queue_pop(struct TQueue *aQueue)
	{
	if (!aQueue || queue_is_empty(aQueue))
		return false;

	struct TQueueNode* pop_node = aQueue->iFront;

	aQueue->iFront = aQueue->iFront->iNext;

	if (aQueue->iFront == NULL)
		aQueue->iBack = NULL;

	free(pop_node);

	return true;
	}

void queue_destroy(struct TQueue *aQueue)
	{
	if (aQueue)
		{
		struct TQueueNode* actual_node = aQueue->iFront;
		*aQueue = (struct TQueue){ .iFront = NULL, .iBack = NULL };

		while (actual_node) 
			{
			struct TQueueNode* remove_node = actual_node;
			actual_node = actual_node->iNext;
			free(remove_node);
			}
		}
	}

struct TQueueIterator queue_iterator_begin(const struct TQueue *aQueue)
	{
	if (aQueue && !queue_is_empty(aQueue))
		return (struct TQueueIterator) { .iQueue = aQueue, .iActual = aQueue->iFront };

	return (struct TQueueIterator) { .iQueue = NULL, .iActual = NULL };
	}

bool queue_iterator_is_valid(const struct TQueueIterator *aIter)
	{
	if (aIter && !queue_is_empty(aIter->iQueue))
		return aIter->iActual != NULL;

	return false;
	}

bool queue_iterator_to_next(struct TQueueIterator *aIter)
	{
	if (queue_iterator_is_valid(aIter))
		{
		aIter->iActual = aIter->iActual->iNext;
		return aIter->iActual == NULL;
		}

	*aIter = (struct TQueueIterator){ .iQueue = NULL, .iActual = NULL };
	return false;
	}

TQueueElement queue_iterator_value(const struct TQueueIterator *aIter)
	{
	if (queue_iterator_is_valid(aIter))
		return aIter->iActual->iValue;

	return (TQueueElement) { 0 };
	}

bool queue_iterator_set_value(const struct TQueueIterator *aIter, TQueueElement aValue)
	{
	if (queue_iterator_is_valid(aIter))
		{
		aIter->iActual->iValue = aValue;
		return true;
		}
	return false;
	}
