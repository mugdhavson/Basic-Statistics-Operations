/*******************************
* FILE: zstr.c                 *
* AUTHOR: Mugdha Sonawane      *
* CLASS: CSC 352, Spring 2022  *
* INSTRUCTOR: Ben Dickken      *
*                              *
* PURPOSE: c file for a        *
* program that does some basic *
* stat operations on strings   * 
* with the help of             *
* pointers                     *
*                              *
*                              *
* PROJECT: Programming         *
* Assignment 6                 *
********************************/

#include <stdio.h>
#include <stdlib.h>
#include "zstr.h"

/*
 * function that calculates the amount of memory 
 * that will be needed by the malloc function
 * to store string of size string_size
 *
 * return: the amount of malloc mem needed
 */
int malloc_size(int string_size) {

	int before_size = string_size + sizeof(int) + sizeof(int) + 1;
	int mallocated_space = 0;
	if (before_size <= 16) {
		mallocated_space = 16;
	} else if (before_size <= 32) {
		mallocated_space = 32;
	} else if (before_size <= 256) {
		mallocated_space = 256;
	} else if (before_size <= 1024) {
		mallocated_space = 1024;
	} else if (before_size <= 2048) {
		mallocated_space = 2048;
	} else {
		zstr_status = ZSTR_ERROR;
	}

	return mallocated_space;
}

/*
 * a helper function to calculate the string size
 * from a char*
 *
 * return: size of string in int
 */
int string_size(char* string) {
	int size = 0;
	char* temp = string;
	while (*temp != '\0') {
		size++;
		temp++;
	}

	return size;
}

/*
 * frees the memory taken up by to_destroy 
 * string
 */
void zstr_destroy(zstr to_destroy) {	
	zstr temp = to_destroy;
	temp -= 8;
	free(temp);
}

/*
 * prints the information about data:
 * the string length, the datasize and 
 * the string itself
 */
void zstr_print_detailed(zstr data) {	
	zstr temp = data;
	temp-=8;
	printf("STRLENGTH: %d\n", *temp);
        temp+=4;
	printf(" DATASIZE: %d\n", *temp);
	temp+=4;
	printf("   STRING: >");
	while (*temp != '\0') {
		printf("%c", *temp);
		temp++;
	}	
	printf("<\n");


}

/*
 * gets the substring that starts at index 
 * begin in base and ends at index (end -1)
 */
zstr zstr_substring (zstr base, int begin, int end) {
	int new_string_size = end - begin;
	int mallocated_space = malloc_size(new_string_size);
	if (zstr_status != ZSTR_ERROR) {
		zstr storage = (char*) malloc(mallocated_space);
		zstr temp = base;
       

       		if (storage != NULL) {
			*storage = new_string_size;
               		storage += 4;
                	*storage = mallocated_space;
               		storage += 4;
			int beginning = begin;
			temp+= begin;
			while (beginning != end) {
				*storage = *temp;
				storage++;
				temp++;
				beginning++;
			}
			*storage = '\0';
			return (storage - new_string_size);
		} else {
			zstr_status = ZSTR_ERROR;
		}	

	}

	// maybe this should be storage - size
	return base;	
}


/*
 * returns the starting index of to_search's first 
 * occurrence in base
 */
int zstr_index (zstr base, zstr to_search) {
	zstr base_temp = base;
	zstr to_search_temp = to_search;
	int index = 0;
	while (*base_temp != '\0') {

		int gap = 0;
		while (*base_temp == *to_search_temp && *to_search_temp != '\0') {
			to_search_temp++;
			base_temp++;
			gap++;
			if (*to_search_temp == '\0') {
				return index;
			}
		}
		if (gap > 0) {
			index+= gap - 1; // -1 cause the index is incrementing at the end
			base_temp--;
			to_search_temp = to_search;
		}
		base_temp++;
		index++;
	}
	return -1;
}

/*
 * counts how many times to_search shows up in base
 */
int zstr_count (zstr base, zstr to_search) {
	int counter = 0;
	
	int to_search_size = string_size(to_search);
	int base_size = string_size(base);
	int max_to_search = base_size/to_search_size; // max number of to_search that can fit into base

	int next_index;

	zstr base_temp = base;
	zstr to_search_temp = to_search;
	for (int x = 0; x <= max_to_search; x++) {
		if (zstr_index(base_temp, to_search_temp) != -1) {
			next_index = zstr_index(base_temp, to_search_temp) + to_search_size;
			base_temp = zstr_substring (base_temp, next_index, base_size);
			counter++;
		}	
	}
	
	return counter;
}

/*
 * compares x with y
 * if x > y, then returns +1
 * if x < y, then returns -1
 * if x == y, then returns 0
 */
int zstr_compare (zstr x, zstr y) {
	int x_size = string_size(x);
	int y_size = string_size(y);
	zstr x_ptr = x;
	zstr y_ptr = y;
	zstr control = x;
	int greatest = 1;
	// 0 = both are equal
	// 1 = x is smallest
	// 2 = x is greatest
	if (x_size > y_size) {
		control = y;
	}
	int end_num = 0;
	while (*control != '\0') {
		if (*x_ptr <= *y_ptr) {
			y_ptr++;
			x_ptr++;
			control++;
			end_num++;
		} else {
			greatest = 2;
			break;
		}

	}	
	if (end_num == x_size && end_num == y_size) {
		greatest = 0;
	}
	if (greatest == 1) {
		return ZSTR_LESS;
	} else if (greatest == 2) {
		return ZSTR_GREATER;
	// end number being the size of either means that the while loop didn't exit
	} else if (greatest == 0)  {
		return ZSTR_EQUAL;
	}
	return 0;
}




/*
 * creates a zstr with string length and mallocated 
 * space and the string itself included 
 */
zstr zstr_create(char* initial_data) {
	int size = string_size(initial_data);

	int mallocated_space = malloc_size(size);

	if (zstr_status != ZSTR_ERROR) {

		zstr storage = (char*) malloc(mallocated_space);

		if (storage != NULL) { 
		
			*storage = size;

			storage += 4;
	
			*storage = mallocated_space;	

			storage += 4;
	
			zstr temp = initial_data;
			while (*temp != '\0') {
				*storage = *temp;

				temp++;
				storage++;
			}
			*storage = '\0';
			return ((zstr)(storage - size));
		} else {
			zstr_status = ZSTR_ERROR;
		}
	}
	return initial_data;
}

/*
 * appends to_append to the end of base. resizes base 
 * if necessary
 */
void zstr_append (zstr * base, zstr to_append) {
	int size_base = string_size(*base);
	int size_to_append = string_size(to_append);
	// get the mallocated size of base
	zstr temp_base = *base;
	zstr temp_to_append = to_append;
	temp_base-=4;
	int mallocated_space = *temp_base;
	temp_base+=4;
	// check if adding the to_append will require more memory
	if (mallocated_space >= (size_base + size_to_append + sizeof(int) + sizeof(int) + 1)) {


		temp_base+=(size_base - 1);
		while (*temp_to_append != '\0') {
			*temp_base = *temp_to_append;
			temp_base++;
			temp_to_append++;	
		}
		*temp_base = '\0';
		base = &temp_base;

 
	} else {
		mallocated_space = malloc_size(size_base + size_to_append);
		if (zstr_status != ZSTR_ERROR) {
			zstr storage = (char*) malloc(mallocated_space);
                	if (storage != NULL) {
				*storage = (size_base + size_to_append);	
                       		storage += 4;
                        	*storage = mallocated_space;
    				storage += 4;
				while (*temp_base != '\0') {
					*storage = *temp_base;
	
					temp_base++;
					storage++;
				}
				while (*temp_to_append != '\0') {
					*storage = *temp_to_append;
			
					temp_to_append++;
					storage++;
				}	
				*storage = '\0';
				storage -= (size_base+size_to_append);
	
				*base = storage;


							
			}
		}

	}


}














