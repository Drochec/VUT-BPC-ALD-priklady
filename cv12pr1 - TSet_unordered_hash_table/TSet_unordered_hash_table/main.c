/** \file main.c
 *  \brief Hlavní program pro testování ADT TSet - (realizace unordered množiny pomocí hašovací tabulky)
 *  \author Petyovský
 *  \version 2024
 *  $Id: main.c 2731 2024-04-20 15:14:55Z petyovsky $
 */

#include <stdio.h>
#include "testbench.h"
#include "TSet.h"

/** \defgroup MainProgram 5. Hlavní program
 *  \brief Definice funkcí hlavního programu
 *  \{
 */

const struct TTestPlan testplan[] =
	{
	#include "testplan_set1.h"
	//#include "testplan_set2.h"
	//#include "testplan_set3.h"
	};

void testset_hardcoded(void)
	{
	struct TSet set = { 0 };
	set_init(&set);
	gSetElementComparisons = 0;

	printf("set is empty: %s\n", set_is_empty(&set) ? "true" : "false");
	set_insert(&set, 222);
	printf("set is empty: %s\n", set_is_empty(&set) ? "true" : "false");

	for(struct TSetIterator it = set_iterator_begin(&set); set_iterator_is_valid(&it); set_iterator_to_next(&it))
		printf("%d ", set_iterator_value(&it));
	putchar('\n');

	set_insert(&set, 42);
	set_insert(&set, 43);
	set_insert(&set, 40);
	set_insert(&set, 41);
	set_insert(&set, 44);
	set_insert(&set, 45);

	//for(int i = 200;i > 100; --i)
	for(int i = 200;i > 197; --i)
		set_insert(&set, i);

	set_for_each(set_iterator_begin(&set), print_value_by_iterator);
	putchar('\n');

	set_erase(&set, 44);
	//for(int i = 200;i > 100; --i)
	for(int i = 200; i > 197; --i)
		set_erase(&set, i);

	set_erase(&set, 222);
	set_erase(&set, 40);
	set_erase(&set, 41);

	set_for_each(set_iterator_begin(&set), print_value_by_iterator);
	putchar('\n');

	bool erased = set_erase(&set, 42+256);
	printf("set erase(42+256): %s\n", (erased) ? "true" : "false");

	set_for_each(set_iterator_begin(&set), print_value_by_iterator);
	putchar('\n');

	bool is_element_of = set_is_element_of(&set, 42);
	printf("set find(42): %s\n", (is_element_of) ? "true" : "false");

	bool inserted = set_insert(&set, 45);
	printf("set insert(45): %s\n", (inserted) ? "true" : "false");

	set_for_each(set_iterator_begin(&set), print_value_by_iterator);
	putchar('\n');

	erased = set_erase(&set, 64);
	printf("set erase(64): %s\n", (erased) ? "true" : "false");

	set_for_each(set_iterator_begin(&set), print_value_by_iterator);
	putchar('\n');

	set_destroy(&set);

	printf("\nTSetElement comparisons: %zu\n", gSetElementComparisons);
	}

int main(int argc, char *argv[])
	{
	struct TSet set = { 0 };
	set_init(&set);

	if(!testbench_run(&set, ITEMS_OF(testplan), testplan))
		{
		puts("testplan failed!!!");
		set_destroy(&set);
		return 1;
		}
	set_destroy(&set);

	testset_hardcoded();
	return 0;
	}

/** \example cv12_reports_testplan_set1_linear_probing.lst
 * Příklad výstupu programu pro soubor `testplan_set1.h` při `HASH_TABLE_SEARCH_VARIANT == LINEAR_PROBING`.
 */
/** \example cv12_reports_testplan_set1_quadratic_probing.lst
 * Příklad výstupu programu pro soubor `testplan_set1.h` při `HASH_TABLE_SEARCH_VARIANT == QUADRATIC_PROBING`.
 */

/** \example cv12_reports_testplan_set2_linear_probing.lst
 * Příklad výstupu programu pro soubor `testplan_set2.h` při `HASH_TABLE_SEARCH_VARIANT == LINEAR_PROBING`.
 */
/** \example cv12_reports_testplan_set2_quadratic_probing.lst
 * Příklad výstupu programu pro soubor `testplan_set2.h` při `HASH_TABLE_SEARCH_VARIANT == QUADRATIC_PROBING`.
 */

/** \example cv12_reports_testplan_set3_linear_probing.lst
 * Příklad výstupu programu pro soubor `testplan_set3.h` při `HASH_TABLE_SEARCH_VARIANT == LINEAR_PROBING`.
 */
/** \example cv12_reports_testplan_set3_quadratic_probing.lst
 * Příklad výstupu programu pro soubor `testplan_set3.h` při `HASH_TABLE_SEARCH_VARIANT == QUADRATIC_PROBING`.
 */

/** \} MainProgram */
