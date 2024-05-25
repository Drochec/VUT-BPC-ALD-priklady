/** \file advanced_sorts.c
 *  \brief Implementace API účinnějších metod třídění
 *  \author Petyovský
 *  \version 2024
 *  $Id: advanced_sorts.c 2680 2024-04-02 10:28:36Z petyovsky $
 */

#include "advanced_sorts.h"
/** \brief Formátovaný tisk hodnoty elementu za předpokladu platné hodnoty
 *  \details Vytiskne formátovaně hodnotu elementu pokud je parametr \p aCondition platný, jinak se vytisknou zástupné znaky.
 *  \param[in] aCondition pokud je \c true bude hodnota vytisknuta, jinak se tisknou zástupné znaky
 *  \param[in] aValue Hodnota elementu k vytisknutí
 */
//[[maybe_unused]]  // Since C23
static inline void print_element_if(bool aCondition, TVectorElement aValue)
	{
	if(aCondition)
		vector_element_store_file(aValue, stdout);
	else
		fprintf(stdout, ". ");
	}

void shell_sort(struct TVector *aVector)
	{
	size_t h = 1;

	//printf("h: %zu\n", h);

	//for(size_t x = 0; x < aVector->iSize; ++x)
	//	vector_element_store_file(aVector->iValues[x], stdout);
	//putchar('\n');

	//for(size_t x = 0; x < aVector->iSize; ++x)
	//	print_element_if( (x % h == k) && (x <= i), aVector->iValues[x]);
	//putchar('\n');

	//putchar('\n');
	}

/** \brief Vnitřní a lokální funkce realizující rekurzivní funkci pro metodu (Quick Sort)
 *  \details Realizuje rekurzivní funkci pro třídicí metodu (Quick Sort) pro elementy vektoru v rozsahu pozic `<k,l>`.
 *  \param[in,out] aVector Ukazatel na tříděný vektor hodnot
 *  \param[in] k Index levého elementu z rozsahu `<k,l>`
 *  \param[in] l Index pravého elementu z rozsahu `<k,l>`
 */
static void quick_sort_worker(struct TVector* /*restrict*/ aVector, size_t k, size_t l)
	{

	if (k > l)
		return;

	size_t s = k + (l - k) / 2;
	TVectorElement tmp = vector_value(aVector, s);
	size_t i = k;
	size_t j = l;

	while (i <= j)
		{
		while (vector_compare_position_value(aVector, i, tmp) < 0)
			{
			i++;
			}
		while (vector_compare_position_value(aVector, j, tmp) > 0)
			{
			if (j > k)
				j--;
			}

		if (i > j)
			break;

		vector_swap_positions(aVector, i, aVector, j);
		i++;
		if (j > k)
			j--;
		}

	if (k < j)
		quick_sort_worker(aVector, k, j);

	if (l > i)
		quick_sort_worker(aVector, i, l);

	//for(size_t x = 0; x < aVector->iSize; ++x)
	//	print_element_if( (x >= k) && (x <= l), aVector->iValues[x]);
	//putchar('\n');
	}

void quick_sort(struct TVector *aVector)
	{
	if(vector_size(aVector) < 2) // Výraz v podmínce vhodně upravte :-)
		return;

	quick_sort_worker(aVector, 0, aVector->iSize - 1);
	}
