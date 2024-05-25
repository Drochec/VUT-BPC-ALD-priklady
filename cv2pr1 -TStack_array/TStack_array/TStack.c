/** \file TStack.c
 *  \brief Implementace API pro typ zásobník (realizace pomocí pole)
 *  \author Petyovský
 *  \version 2024
 *  $Id: TStack.c 2592 2024-02-09 17:45:42Z petyovsky $
 */

#include "TStack.h"

void stack_init(struct TStack *aStack)
	{
	if (aStack)
	{
		aStack->iCount = 0;
	}
	}

bool stack_is_empty(const struct TStack *aStack)
	{
	if (aStack)
	{
		return aStack->iCount == 0;
	}

	return true;
	}

bool /* TStackIterator */ stack_top(const struct TStack *aStack, TStackElement *aValue)
	{

	if (stack_is_empty(aStack) || !aValue)
	{
		return false;
	}
	*aValue = aStack->iValues[aStack->iCount - 1];

	return true;
	}

bool stack_push(struct TStack *aStack, TStackElement aValue)
	{
	if (aStack)
	{
		if (aStack->iCount < STACK_MAXCOUNT) 
		{
			aStack->iValues[aStack->iCount++] = aValue;
		}
	}

	return false;
	}

bool stack_pop(struct TStack *aStack)
	{
	if(stack_is_empty(aStack))
		{
		return false;
		}
	--aStack->iCount;
	return false;
	}

void stack_destroy(struct TStack *aStack)
	{
	stack_init(aStack);
	}

struct TStackIterator stack_iterator_begin(const struct TStack *aStack)
	{
	if (!stack_is_empty(aStack))
		{
		return (struct TStackIterator) { .iStack = aStack, .iPos = aStack->iCount - 1 };
		}

	return (struct TStackIterator) { .iStack = NULL, .iPos = 0};
	}



bool stack_iterator_is_valid(const struct TStackIterator *aIter)
	{
	if (aIter && aIter->iStack && aIter->iPos < aIter->iStack->iCount)
		{
		return true;
		}
	return false;
	}

// Pokud je ukazatel aIter platný a iterátor je asociován s platným zásobníkem, pokračuj, jinak vrať false.
// Pokud již další element v zásobníku neexistuje a iterátor ukazuje mimo zásobník,
// funkce vrací false, jinak vrací true.
// Pokud iterátor neukazuje složkou iPos na element umístěný na dně zásobníku a také
// odkazovaná pozice není mimo rozsah daný počtem elementů zásobníku, 
// posuň iterátor na další pozici v zásobníku a vrať true.
// Jinak nastav iterátor jako nevalidní (zrušte propojení iterátoru s asociovaným zásobníkem) a vrať false.
bool stack_iterator_to_next(struct TStackIterator *aIter)
	{
/*
	if (!aIter || !aIter->iStack || aIter->iPos <= 0)
		{
		return false;
		}

	if (aIter->iPos > 0 && aIter->iPos <= STACK_MAXCOUNT)
		{
		aIter->iPos--;
		return true;
		}

	aIter = NULL;
	return false;

*/

	if (aIter && aIter->iStack)
		{
		if (aIter->iPos > 0 && aIter->iPos < aIter->iStack->iCount)
			{
			--aIter->iPos;
			return true;
			}
		*aIter = (struct TStackIterator){ .iStack = NULL, .iPos = 0 };
		}
	return false;
	}

TStackElement stack_iterator_value(const struct TStackIterator *aIter)
	{
	if (stack_iterator_is_valid(aIter))
		{
		return aIter->iStack->iValues[aIter->iPos];
		}
	return (TStackElement) { 0 };
	}
