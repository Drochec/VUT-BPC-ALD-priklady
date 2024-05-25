/** \file basic_sorts.c
 *  \brief Implementace API přímých metod třídění
 *  \author Petyovský
 *  \version 2024
 *  $Id: basic_sorts.c 2631 2024-03-08 16:40:08Z petyovsky $
 */

#include "basic_sorts.h"

void print_element(const struct TVectorIterator *aIter)
	{
	vector_element_store_file(vector_iterator_value(aIter), stdout);
	}

void insert_sort(struct TVector *aVector)
	{

	for (size_t nsort = 1; nsort < aVector->iSize; nsort++)
		{
		TVectorElement tmp = vector_value(aVector,nsort);

		size_t idx;
		for (idx = nsort; idx > 0; idx--)
			{
			if (vector_compare_position_value(aVector, idx-1, tmp) == 1)
				{
				vector_move_positions(aVector, idx, aVector, idx-1);
				}
			else
				{
				break;
				}
			}
		vector_set_value(aVector, idx, tmp);

		}
	vector_for_each(vector_iterator_begin(aVector), print_element);
	putchar('\n');
	}

void select_sort(struct TVector *aVector)
	{
	for (size_t nsort = 0; nsort < aVector->iSize-1; nsort++)
		{
		size_t idx_min = nsort;

		for (size_t idx_act = nsort + 1; idx_act < aVector->iSize; idx_act++)
			{
			if (vector_compare_positions(aVector, idx_act, aVector, idx_min) < 0)
				{
				idx_min = idx_act;
				}
			}
		vector_swap_positions(aVector, idx_min, aVector, nsort);
		
		}
	vector_for_each(vector_iterator_begin(aVector), print_element);
	putchar('\n');
	}

void bubble_sort(struct TVector *aVector)
	{
	for (size_t sort = 0; sort < aVector->iSize - 1; sort++)
		{
		for (size_t idx = 0; idx < aVector->iSize - 1 - sort; idx++)
			{
			if (vector_compare_positions(aVector,idx,aVector,idx+1) == 1)
				vector_swap_positions(aVector, idx, aVector, idx + 1);
			}
		}

	vector_for_each(vector_iterator_begin(aVector), print_element);
	putchar('\n');
	}

void bubble_sort_optimized(struct TVector *aVector)
	{

	for (size_t sort = 0; sort < aVector->iSize - 1; sort++)
		{
		bool swapped = false;
		for (size_t idx = 0; idx < aVector->iSize - 1 - sort; idx++)
			{
			if (vector_compare_positions(aVector, idx, aVector, idx + 1) == 1)
				{
				vector_swap_positions(aVector, idx, aVector, idx + 1);
				swapped = true;
				}
			}
		if (!swapped)
			break;
		}

	vector_for_each(vector_iterator_begin(aVector), print_element);
	putchar('\n');
	}

void bubble_sort_optimized2(struct TVector *aVector)
	{
	size_t sort_idx = aVector->iSize-1;
	while (sort_idx > 0)
		{
		size_t change_idx = 0;
		for (size_t idx = 0; idx < sort_idx; idx++)
			{
			if (vector_compare_positions(aVector, idx, aVector, idx + 1) == 1)
				{
				vector_swap_positions(aVector, idx, aVector, idx + 1);
				change_idx = idx;
				}
			}
		sort_idx = change_idx;
		}

	vector_for_each(vector_iterator_begin(aVector), print_element);
	putchar('\n');

	}

void shaker_sort(struct TVector *aVector)
	{
	size_t max_pos = aVector->iSize - 1;
	size_t min_pos = 0;
	while (min_pos < max_pos)
		{
		size_t change_idx = 0;
		for (size_t idx = min_pos; idx < max_pos; idx++)
			{
			if (vector_compare_positions(aVector, idx, aVector, idx + 1) == 1)
				{
				vector_swap_positions(aVector, idx, aVector, idx + 1);
				change_idx = idx;
				}
			}
		max_pos = change_idx;
		
		for (size_t idx = max_pos; idx > min_pos; idx--)
			{
			if (vector_compare_positions(aVector, idx - 1, aVector, idx) == 1)
				{
				vector_swap_positions(aVector, idx - 1, aVector, idx);
				change_idx = idx;
				}
			}
		
		min_pos=change_idx;
		
		}

	vector_for_each(vector_iterator_begin(aVector), print_element);
	putchar('\n');
	}
