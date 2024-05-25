/** \file TSetHashTableOpenAddr.c
 *  \brief Implementace API pro typ SetHashTable - (hašovací tabulka využívající otevřené adresování)
 *  \author Petyovský
 *  \version 2024
 *  $Id: TSetHashTableOpenAddr.c 2731 2024-04-20 15:14:55Z petyovsky $
 */

#define LINEAR_PROBING		1	///< Volba pro lineární zkoumání následující pozice ve funkci: `set_hash_table_search()`
#define QUADRATIC_PROBING	2	///< Volba pro kvadratické zkoumání následující pozice ve funkci: `set_hash_table_search()`

//#define HASH_TABLE_SEARCH_VARIANT	LINEAR_PROBING		///< Varianta využívající lineární zkoumání následující pozice ve funkci: `set_hash_table_search()`
#define HASH_TABLE_SEARCH_VARIANT	QUADRATIC_PROBING	///< Varianta využívající kvadratické zkoumání následující pozice ve funkci: `set_hash_table_search()`

#include <stdlib.h>
#include <assert.h>
#include "TSetHashTableOpenAddr.h"
#include "check.h"

/** \brief Úplná definice typu SetHashTable
 *  \details Typ SetHashTable realizuje hash tabulku s elementy typu ukazatel na SetElementHashable a umožňuje s nimi pracovat pomocí definovaného API.
 */
struct TSetHashTable
	{
	size_t iCapacity;			///< Naalokovaná kapacita vnitřního pole přihrádek
	TSetElement *iBucket[];		///< Pole přihrádek realizující hašovací tabulku (každá přihrádka je ukazatel na typ SetElement Hashable)
	};

/** \brief Funkce vracející hodnotu reprezentující smazanou přihrádku
 *  \details Servisní funkce pro výpočet hodnoty reprezentující značku pro dříve obsazenou, ale nyní již smazanou přihrádku.
 *  \param[in] aTable Ukazatel na existující hašovací tabulku
 *  \return Vrací hodnotu reprezentující značku pro smazanou přihrádku
 *  \attention Funkce ověřuje platnost ukazatele \b pouze při překladu v režimu `Debug`, kdy pomocí `assert` hlásí běhovou chybu!
 */
static inline TSetElement* calc_erased_bucket_marker(const struct TSetHashTable *aTable)
	{
	assert(aTable);
	assert(aTable->iBucket);
	return (TSetElement *) &aTable->iBucket[0];
	}

bool set_hash_table_init(struct TSetHashTable **aTablePtr, size_t aCapacity)
	{
	if(!aTablePtr || !aCapacity)
		return false;

	struct TSetHashTable *new_table =
		calloc(1, offsetof(struct TSetHashTable, iBucket) + aCapacity * sizeof(TSetElement *));

	if(!new_table)
		return false;

	new_table->iCapacity = aCapacity;
	*aTablePtr = new_table;
	return true;
	}

int set_hash_table_search(const struct TSetHashTable *aTable, TSetElement aValue, size_t *aPosPtr)
	{
	if(!aTable)
		return -2;

	if(!aPosPtr)
		return -1;

	assert(aTable->iCapacity);

	/* Zde implementujte algoritmus pro vyhledávání elementu v hašovací tabulce */

#if HASH_TABLE_SEARCH_VARIANT == LINEAR_PROBING

		/* Zde implementujte lineární zkoumání následující pozice */

	size_t hash1 = set_element_hash_value(&aValue);
	size_t hash2 = hash1 % aTable->iCapacity;

	size_t pos = hash2;
	size_t stop = hash2;

	TSetElement* erased_marker = calc_erased_bucket_marker(aTable);

	size_t u_pos = pos;
	bool u_found = false;

	do {
		if (aTable->iBucket[pos] == NULL)
			{
			*aPosPtr = u_found ? u_pos : pos;
			return 1;
			}
		else if (aTable->iBucket[pos] == erased_marker)
			{
			if (!u_found)
				{
				u_pos = pos;
				u_found = true;
				}
			}
		else
			{
			if (set_element_comparator(&aTable->iBucket[pos],&aValue) == 0)
				{
				*aPosPtr = pos;
				return 0;
				}
			}
		
		pos = (pos + 1) % aTable->iCapacity;
		
		}

	while (pos != stop);
			{
			return 1;
			}

#elif HASH_TABLE_SEARCH_VARIANT == QUADRATIC_PROBING

		/* Zde implementujte kvadratické zkoumání následující pozice */
	size_t hash1 = set_element_hash_value(&aValue);
	size_t hash2 = hash1 % aTable->iCapacity;

	size_t pos = hash2;
	size_t stop = hash2;

	TSetElement* erased_marker = calc_erased_bucket_marker(aTable);

	size_t u_pos = pos;
	bool u_found = false;

	int i = 0;

	do {
		if (aTable->iBucket[pos] == NULL)
			{
			*aPosPtr = u_found ? u_pos : pos;
			return 1;
			}
		else if (aTable->iBucket[pos] == erased_marker)
			{
			if (!u_found)
				{
				u_pos = pos;
				u_found = true;
				}
			}
		else
			{
			if (set_element_comparator(&aTable->iBucket[pos], &aValue) == 0)
				{
				*aPosPtr = pos;
				return 0;
				}
			}

		i++;
		pos = (hash2 + i * i) % aTable->iCapacity;

		}

	while (pos != stop);

	if (u_found)
		return 1;
#else
	#error Missing correct HASH_TABLE_SEARCH_VARIANT symbol definition
#endif

	return 2;		// Element was not found and hash table is completely full
	}

bool set_hash_table_insert(struct TSetHashTable *aTable, TSetElement aValue)
	{

	/* Zde implementujte vložení kopie elementu do hašovací tabulky na správnou pozici. */
	/* Využijte servisní funkci: set_hash_table_search */

	size_t pos = 0;
	int cmp = set_hash_table_search(aTable, aValue, &pos);
	if (cmp == 0 || cmp == 2)
		return false;

	TSetElement* tmp = malloc(sizeof(TSetElement));
	
	if (!tmp)
		return false;
	*tmp = aValue;
	aTable->iBucket[pos] = tmp;

	return true;
	}

bool set_hash_table_erase(struct TSetHashTable *aTable, TSetElement aValue)
	{

	/* Zde implementujte odebrání elementu ze správné pozice v hašovací tabulce. */
	/* Využijte servisní funkci: set_hash_table_search */

	size_t pos = 0;

	if (set_hash_table_search(aTable, aValue, &pos) != 0)
		return false;

	free(aTable->iBucket[pos]);
	aTable->iBucket[pos] = calc_erased_bucket_marker(aTable);


	return true;	// Hash table is full and element was not found, or just element was not found
	}

void set_hash_table_destroy(struct TSetHashTable *aTable)
	{
	if(!aTable)
		return;

	assert(aTable->iCapacity);
	TSetElement *const Marked_as_erased = calc_erased_bucket_marker(aTable);
	for(size_t i = 0; i < aTable->iCapacity; ++i)
		{
		if(aTable->iBucket[i] != Marked_as_erased)
			free(aTable->iBucket[i]);

		aTable->iBucket[i] = NULL;
		}

	free(aTable);
	}

size_t set_hash_table_begin_pos(const struct TSetHashTable *aTable)
	{
	assert(aTable);
	assert(aTable->iCapacity);

	TSetElement *const Marked_as_erased = calc_erased_bucket_marker(aTable);
	size_t pos = 0;
	for(; pos < aTable->iCapacity; ++pos)
		if( (aTable->iBucket[pos]) && (aTable->iBucket[pos] != Marked_as_erased) )
			break;

	return pos;
	}

bool set_hash_table_is_valid_pos(const struct TSetHashTable *aTable, size_t aPos)
	{
	if(aTable)
		{
		assert(aTable->iCapacity);
		TSetElement *const Marked_as_erased = calc_erased_bucket_marker(aTable);
		return (aPos < aTable->iCapacity) && (aTable->iBucket[aPos]) && (aTable->iBucket[aPos] != Marked_as_erased);
		}

	return false;
	}

size_t set_hash_table_next_pos(const struct TSetHashTable *aTable, size_t aPos)
	{
	assert(aTable);
	assert(aTable->iCapacity);

	TSetElement *const Marked_as_erased = calc_erased_bucket_marker(aTable);
	for(++aPos; aPos < aTable->iCapacity; ++aPos)
		if( (aTable->iBucket[aPos]) && (aTable->iBucket[aPos] != Marked_as_erased) )
			break;

	return aPos;
	}

TSetElement set_hash_table_value_at_pos(const struct TSetHashTable *aTable, size_t aPos)
	{
	assert(aTable);
	assert(aTable->iCapacity);
	assert(aPos < aTable->iCapacity);

	TSetElement *const Marked_as_erased = calc_erased_bucket_marker(aTable);
	assert( (aTable->iBucket[aPos]) && (aTable->iBucket[aPos] != Marked_as_erased) );

	return *aTable->iBucket[aPos];
	}
