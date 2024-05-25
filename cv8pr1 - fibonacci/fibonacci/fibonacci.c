/** \file fibonacci.c
 *  \brief Definice různých variant implementace výpočtu hodnot Fibonacciho posloupnosti
 *  \author Petyovský
 *  \version 2024
 *  $Id: fibonacci.c 2663 2024-03-25 10:50:21Z petyovsky $
 */

#include "fibonacci.h"

//-----------------------------------------------------------------------
// Implementace stromovou rekurzi
unsigned fibonacci1(unsigned n)
	{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return fibonacci1(n-2) + fibonacci1(n-1);
	}

//-----------------------------------------------------------------------
// Implementace iteraci
unsigned fibonacci2(unsigned n)
	{
	unsigned fib_n_1 = 1;	// fibonacci(n-1)
	unsigned fib_n_2 = 0;	// fibonacci(n-2)
	unsigned fib = 0;

	for (int i = 1; i <= n; i++)
		{
		fib = fib_n_2 + fib_n_1;
		fib_n_2 = fib_n_1;
		fib_n_1 = fib;
		}

	return fib_n_2;
	}

//-----------------------------------------------------------------------
// Implementace stromovou rekurzi s memoizaci
struct TMemoizer mfibonacci3 = { 0, }; // Instance memoizeru

unsigned fibonacci3(unsigned n)
	{

	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return fibonacci3_wrapper(n - 2) + fibonacci3_wrapper(n - 1);
	
	}

unsigned fibonacci3_wrapper(unsigned n)
	{
	return memoizer_eval(&mfibonacci3, n);
	}

//-----------------------------------------------------------------------
// Implementace s koncovou rekurzi
/** \brief Vnitřní a lokální funkce realizující koncovou rekurzi
 */
unsigned fibonacci4_worker(unsigned n, unsigned fib_n_1, unsigned fib_n_2)
	{
	if (n == 0)
		return fib_n_2;

	return fibonacci4_worker(n-1, fib_n_1+fib_n_2, fib_n_1);
	}

unsigned fibonacci4(unsigned n)
	{
	return fibonacci4_worker(n, 1, 0);
	}
