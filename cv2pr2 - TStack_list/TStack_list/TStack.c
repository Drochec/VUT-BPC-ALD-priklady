/** \file TStack.c
 *  \brief Implementace API pro typ zásobník (realizace pomocí lineárního jednosměrně vázaného seznamu)
 *  \author Petyovský
 *  \version 2024
 *  $Id: TStack.c 2592 2024-02-09 17:45:42Z petyovsky $
 */

#include "TStack.h"

/** \brief Úplná definice privátního typu StackNode
 *  \details Privátní typ StackNode (nedostupný mimo funkce ze souboru TStack.c) reprezentuje typ pro jednotlivé uzly lineárního jednosměrně vázaného seznamu.
 */
struct TStackNode
	{
	struct TStackNode *iNext;				///< Ukazatel na následující uzel lineárního jednosměrně vázaného seznamu
	TStackElement iValue;					///< Element zásobníku uložený v uzlu lineárního jednosměrně vázaného seznamu
	};

void stack_init(struct TStack *aStack)
	{
	if (aStack)
		{
		aStack->iTop = NULL;
		}
	}

bool stack_is_empty(const struct TStack *aStack)
	{
	if (aStack && aStack->iTop)
		return false;
	return true;
	}

bool /* TStackIterator */ stack_top(const struct TStack *aStack, TStackElement *aValue)
	{
	if (aStack && aStack->iTop && aValue) {
		*aValue = aStack->iTop->iValue;
		return true;
	}
	return false;
	}

bool stack_push(struct TStack *aStack, TStackElement aValue)
	{
	if (aStack)
		{
		struct TStackNode *new_node = malloc(sizeof(struct TStackNode));
		if (!new_node)
			return false;

		*new_node = (struct TStackNode){.iNext = aStack->iTop, .iValue = aValue};

		aStack->iTop = new_node;
		return true;
		}
	return false;
	}

bool stack_pop(struct TStack *aStack)
	{

	if (!aStack || !aStack->iTop)
		{
		return false;
		}

	struct TStackNode* pop_element = aStack->iTop;
	
	aStack->iTop = aStack->iTop->iNext;

	free(pop_element);

	return true;
	}

void stack_destroy(struct TStack* aStack)
	{
	if (!aStack)
		return;
	struct TStackNode* act_node = aStack->iTop;
	aStack->iTop = NULL;

	while (act_node != NULL)
		{
		struct TStackNode* old_node = act_node;
		act_node = act_node->iNext;
		free(old_node);
		}

	}

struct TStackIterator stack_iterator_begin(const struct TStack *aStack)
	{
	if (aStack && aStack->iTop)
		return (struct TStackIterator) { .iStack = aStack, .iActual = aStack->iTop };

	return (struct TStackIterator) { .iStack = NULL, .iActual = NULL };
	}

bool stack_iterator_is_valid(const struct TStackIterator *aIter)
	{
	if (aIter && aIter->iStack)
		if (aIter->iStack->iTop && aIter->iActual)
			return true;

	return false;
	}

bool stack_iterator_to_next(struct TStackIterator *aIter)
	{
	if (!aIter || !aIter->iStack)
		return false;
	
	if (stack_iterator_is_valid(aIter))
		aIter->iActual = aIter->iActual->iNext;

	
	return stack_iterator_is_valid(aIter);
	}

TStackElement stack_iterator_value(const struct TStackIterator *aIter)
	{
	if (stack_iterator_is_valid)
		return aIter->iActual->iValue;

	return (TStackElement) { 0 };
	}
