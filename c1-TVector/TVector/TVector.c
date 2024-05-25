/** \file TVector.c
 *  \brief Implementace Basic Vector API
 *  \author Petyovský
 *  \version 2024
 *  $Id: TVector.c 2584 2024-02-05 14:33:25Z petyovsky $
 */

#include <stdlib.h>
#include <assert.h>
#include "TVector.h"
#include "check.h"

bool vector_init(struct TVector *aVector, size_t aSize)
	{
	if (!aVector || aSize == 0) {
		return false;
		}
	TVectorElement* new_values = calloc(aSize, sizeof(TVectorElement));
	if (!new_values) {
		return false;
		}

	*aVector = (struct TVector){ .iSize = aSize, .iValues = new_values };

	return true;
	}

bool vector_init_random(struct TVector *aVector, size_t aSize)
	{
	if (!aVector || aSize == 0) {
		return false;
	}
	TVectorElement* new_values = malloc(aSize * sizeof(TVectorElement));
	if (!new_values) {
		return false;
	}

	for (int i = 0; i < aSize; i++) {
		new_values[i] = vector_element_random_value();
	}

	*aVector = (struct TVector){ .iSize = aSize, .iValues = new_values };
	return true;
	}

bool vector_init_file(struct TVector *aVector, FILE *aInputFile)
	{
	if (!aVector || !aInputFile) {
		return false;
		}
	size_t new_size = 0;
	if (fscanf(aInputFile, "%zu", &new_size) != 1) {
		return false;
		}
	
	TVectorElement* new_values = calloc(new_size, sizeof(TVectorElement));
	if (!new_values) {
		return false;
		}
	for (size_t i = 0; i < new_size; i++) {
		if (!vector_element_load_file(&new_values[i], aInputFile)) {
			free(new_values);
			return false;
			}
		}
	*aVector = (struct TVector){ .iSize = new_size, .iValues = new_values };

	return true;
	}

bool vector_clone(const struct TVector *aVector, struct TVector *aVectorClone)
	{
	return false;
	}

bool vector_store_file(const struct TVector *aVector, FILE *aOutputFile)
	{
	return false;
	}

TVectorElement vector_value(const struct TVector *aVector, size_t aPos)
	{
	assert(aVector);
	assert(aVector->iValues);
	assert(aPos < aVector->iSize);

	return (TVectorElement) { aVector->iValues[aPos] };
	}

void vector_set_value(struct TVector *aVector, size_t aPos, TVectorElement aValue)
	{
	}

size_t vector_size(const struct TVector *aVector)
	{

	if (!aVector || !aVector->iValues) {
		return 0;
	}

	return aVector->iSize;
	}

bool vector_resize(struct TVector *aVector, size_t aNewSize)
	{
	return false;
	}

void vector_destroy(struct TVector *aVector)
	{
	if (!aVector) {
		return;
		}
	free(aVector->iValues);
	*aVector = (struct TVector) {.iValues = NULL, .iSize = 0};
	}

struct TVectorIterator vector_iterator_begin(const struct TVector *aVector)
	{
	if (aVector)
		{ 
		return (struct TVectorIterator) { .iVector = aVector, .iPos = 0 };
		}
	return (struct TVectorIterator) { .iVector = NULL, .iPos = 0 };
	}

struct TVectorIterator vector_iterator_pos(const struct TVector *aVector, size_t aPos)
	{
	if (aVector && aVector->iSize > aPos) {
		return (struct TVectorIterator) { .iVector = aVector, .iPos = aPos };
	}
	return (struct TVectorIterator) { .iVector = NULL, .iPos = 0 };
	}

struct TVectorIterator vector_iterator_last(const struct TVector *aVector)
	{
	if (aVector)
		{
		return (struct TVectorIterator) { .iVector = aVector, .iPos = aVector->iSize-1 };
		}
	return (struct TVectorIterator) { .iVector = NULL, .iPos = 0 };
	}

bool vector_iterator_is_valid(const struct TVectorIterator *aIter)
	{
	if (aIter)
		{ 
		if (aIter->iPos < aIter->iVector->iSize)
			return true;
		}
	return false;
	}

bool vector_iterator_to_next(struct TVectorIterator *aIter)
	{
	if(vector_iterator_is_valid(aIter))
		{
		aIter->iPos++;
		return true;
		}
	return false;
	}

bool vector_iterator_to_prev(struct TVectorIterator *aIter)
	{
	if (vector_iterator_is_valid(aIter))
	{
		aIter->iPos--;
		return true;
	}
	return false;
	}

TVectorElement vector_iterator_value(const struct TVectorIterator *aIter)
	{
	if (vector_iterator_is_valid(aIter))
		return aIter->iVector->iValues[aIter->iPos];
	return (TVectorElement) { 0 };
	}

bool vector_iterator_set_value(const struct TVectorIterator *aIter, TVectorElement aValue)
	{
	if (vector_iterator_is_valid(aIter))
		{
		aIter->iVector->iValues[aIter->iPos] = aValue;
		return true;
		}
	return false;
	}
