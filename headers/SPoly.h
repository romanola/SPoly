#ifndef test_h
#define test_h

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


#define SIZE 100 // starting table size (array)
#define PATH "output.txt" //output file path

typedef double t_coef;  //type for polynomial coefficients


// structure "pair" = (key, value)
// node to add to the table and dictionary
typedef struct pair{
    size_t key; // key
    t_coef item; // value
} pair;


// ========= table ==========

// structure table (dynamic array whose elements are objects of the structure of steam)
typedef struct table{

    size_t size; // current array size
    pair* p_items; //pointer to array
    size_t last; // the index of the last added element + 1

} table;



//creating a new table
table *new_table(void);

//doubles the size of the table
void increase(table* t);

// sets the index' "index" value p in the table
void setitem(table* t, size_t index, pair p);

// returns value by index
pair getitem(table* t, size_t index);

// adds an element to the table
void append(table* t, size_t key, t_coef item);

// check
// key presence in the table
bool contains_key(table* t ,size_t key);

// returns the index of the element by key, -1 in other way
long find_index(table* t, size_t key);



// ========= table ==========





// ========= dict ==========



// structure dictionary
typedef struct dict{

    table* p_table; // pointer to the table

} dict;


// create a new dictionary
dict* new_dict(void);

// adds a pair key:value if there is no such key in the dictionary
void add(dict* d, size_t key, t_coef value);

// changes the value of an existing key
void update(dict* d, size_t key, t_coef value);

// finds the value of a given key
// returns 0 if no key
t_coef find(dict* d, size_t key);

// returns a pointer to an array of all keys in the dictionary
// quantity = field last
size_t* get_keys(dict* d);


// ========= dict ==========



// ========= poly ==========


// structure polynomial
typedef struct SPoly{
    dict* p_poly; // dictionary: key - degree, coefficient value

} SPoly;


// creates e new polynomial and returns a pointer to it
SPoly* new_poly(void);


// sets the value of the coefficient "coef" to the degree of pow
void set_coef(SPoly* p, size_t pow, t_coef coef);

// updates coefficient of an existing key
void update_coef(SPoly* p, size_t pow, t_coef coef);

// returns coefficient of a given degree
t_coef get_coef(SPoly* p, size_t pow);

// prints polynomial to console
void print(SPoly* p);

//returns the value of the polynomial at x
t_coef value(SPoly* s, t_coef x);


// standard polynomial introduction
SPoly* input(void);

// returns a pointer to a polynomial
// which is the sum of the polynomials p1 and p2
SPoly* sum(SPoly* p1, SPoly* p2);

// returns a pointer to a polynomial
// which is the subtraction of the polynomials p1 and p2
SPoly* sub(SPoly* p1, SPoly* p2);


// multiplication of a polynomial by a monomial
// returns a pointer to the result of the polynomial
SPoly* monom_mul(SPoly* p, SPoly* m);


// return a pointer to the polynomial
// which is the multiplication of the polynomials p1 and p2
SPoly* mul(SPoly* p1, SPoly* p2);

// polynomial derivative p
SPoly* derivative(SPoly* p);

// indefinite integral of the polynomial p
SPoly* undefinite_integral(SPoly* p);

// defined integral of polynomial p from a to b
// returns value
t_coef definite_integral(SPoly* p, t_coef a, t_coef b);


// console input
// one line where the coefficients are separated by a space
// starts with a free member (grade 0)
// for example, the string 1 2 0 3 will create the polynomial 3x^3 + 2x + 1
SPoly* input_console(void);

// returns a pointer to a polynomial
// with random coefficients
// dimension n of m members
SPoly* generate(size_t n, size_t m);

// Secant method is a root-finding algorithm on the segment [a, b]
// returns a pointer to an array of 2 elements
// 0 - polynom value
// 1 - point at which the polynomial has a root
t_coef* find_root(SPoly* p, t_coef a, t_coef b);

// output to binary file
// specify the absolute path of the file in the PATH
void output_to_bin(SPoly *p);

// output to file
// specify the absolute path of the file in the PATH
void output_to_file(SPoly *p);

#endif /* test_h */
