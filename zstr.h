/*******************************
* FILE: zstr.h                 *
* AUTHOR: Mugdha Sonawane      *
* CLASS: CSC 352, Spring 2022  *
* INSTRUCTOR: Ben Dickken      *
*                              *
* PURPOSE: header file for a   *
* program that does some basic *
* stat operations on strings   * 
* with the help of             *
* pointers                     *
*                              *
*                              *
* PROJECT: Programming         *
* Assignment 6                 *
********************************/

/*
 * typedefs for this program
 */
typedef char* zstr;
typedef int zstr_code;


/*
 * global constants for error codes
 */
#define ZSTR_OK 0
#define ZSTR_ERROR 100
#define ZSTR_GREATER 1
#define ZSTR_LESS -1
#define ZSTR_EQUAL 0

/*
 * global variable for program status
 */
zstr_code zstr_status;

/*
 * print out a zstr, with the size 
 * and allocated space values included.
 */
void zstr_print_detailed(zstr data);

/*
 * allocate enough memory to hold the 
 * char array initial_data using the 
 * malloc function, store the string 
 * length and allocated size, and then 
 * return a zstr.
 */
zstr zstr_create(char* initial_data);

/*
 * calls the free function to free the 
 * mallocated memory
 */
void zstr_destroy (zstr to_destroy);

/*
 * compare and return ZSTR_GREATER if 
 * x > y, ZSTR_EQUAL if x == y, and 
 * ZSTR_LESS if x < y. 
 */
int zstr_compare (zstr x, zstr y);

/*
 * search for the first occurrence of 
 * to_search within base. It should 
 * return the index if found, or -1 
 * if not found
 */
int zstr_index (zstr base, zstr to_search);

/*
 * count how many times to_search appears 
 * within base
 */
int zstr_count (zstr base, zstr to_search);

/*
 * create a new zstr with the contents that 
 * are contained within the substring of base 
 * between begin (inclusive) and end (exclusive).
 */
zstr zstr_substring (zstr base, int begin, int end);

/*
 * take a pointer to a zstr (thus, a char**) which 
 * will act as the base zstr, and a zstr containing 
 * the string content to append to the base zstr.
 */
void zstr_append (zstr * base, zstr to_append);
