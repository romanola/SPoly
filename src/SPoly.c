#include "../headers/SPoly.h"


table *new_table() {
    // creating a new table
    table* t = (table*) malloc(sizeof(table)); // allocate memory
    t -> size = SIZE; // set the starting size SIZE
    t -> p_items = (pair*) malloc((t -> size) * sizeof(pair)); // allocate memory for an array of pairs
    t -> last = 0; // set the index of the last
    return t; // return pointer
}

void increase(table *t) {
    // increases the size of the table (twice)
    // called when the element cannot be added to the table
    if (t -> last == t -> size){ // completeness check
        pair* new = (pair*) malloc((t -> size * 2) * sizeof(pair)); // create a new array of pairs 2 times more
        for (size_t i = 0; i < t -> size; i++){
            new[i] = t -> p_items[i]; // move items from it to old
        }
        free(t -> p_items); // returning the memory of the old array
        t -> p_items = new; // write new in the appropriate field
        t -> size = t -> size * 2; // change current size
    }
}

void setitem(table *t, size_t index, pair p) {
    // sets the index' "index" value p in the table
    t -> p_items[index] = p;
}

pair getitem(table *t, size_t index) {
    // returns value by the index "index"
    return t -> p_items[index];
}

void append(table *t, size_t key, t_coef item) {
    // adds an element to the table
    if (t -> last == t -> size){ // if there is no more space, increase the array
        increase(t);
    }

    pair* p = (pair*) malloc(sizeof(pair)); // dynamically allocate memory for a new pair
    p -> key = key;
    p -> item = item;
    // accordingly fill in the values
    setitem(t, t -> last, *p);
    t -> last++; // change the index of the last item
}

long find_index(table *t, size_t key) {
    long ind = -1;
    for (size_t i = 0; i < t -> last; i++){
        if (t -> p_items[i].key == key){
            ind = i;
            break;
        }

    }
    return ind;
}

bool contains_key(table *t, size_t key) {
    // check
    // key presence in the table
    bool success = false; // checkbox
    for (size_t i = 0; i < t -> last; i++){
        // brute force and comparison
        if (t -> p_items[i].key == key){
            success = true; // exit if successful
            break;
        }
    }
    return success;
}

dict *new_dict() {
    // creates a new dictionary
    table* t = new_table(); // to do this, first create a new table.
    dict* d = (dict*) malloc(sizeof(dict)); // allocate memory for the dictionary
    d -> p_table = t; // fill the field
    return d;
}

void add(dict *d, size_t key, t_coef value) {
    // adds a pair (key: value) if there is no such key in the dictionary
    if (!contains_key(d -> p_table, key)){
        append(d -> p_table, key, value);
    }
}

void update(dict *d, size_t key, t_coef value) {
    // changes the value of an existing key
    long ind = find_index(d -> p_table, key);
    if (ind != -1){
        pair* p = (pair*) malloc(sizeof(pair)); // dynamically allocate memory for a new pair
        p -> key = key;
        p -> item = value;
        // accordingly fill in the values
        setitem(d -> p_table, (size_t) ind, *p);
    }
    else{
        // if there is no such key in the dictionary
        // creates an appropriate pair
        add(d, key, value);
    }

}

t_coef find(dict *d, size_t key) {
    // finds the value of a given key
    // returns 0 if no key
    t_coef val = 0;
    for (size_t i = 0; i < d -> p_table -> last; i++){
        if (key == getitem(d -> p_table, i).key){
            val = getitem(d -> p_table, i).item;
            break;
        }
    }
    return val;
}

size_t *get_keys(dict *d) {
    // returns a pointer to an array of all keys in the dictionary
    // quantity = last field
    size_t* p_keys = (size_t*) malloc(d -> p_table -> last * sizeof(size_t));
    for (size_t i = 0; i < d -> p_table -> last; i++){
        p_keys[i] = getitem(d -> p_table, i).key;
    }

    // sorting
    for (size_t i = 0; i < d -> p_table -> last; i++){
        for (size_t j = i + 1; j < d -> p_table -> last; j++){
            if (p_keys[i] > p_keys[j]){
                size_t tmp = p_keys[i];
                p_keys[i] = p_keys[j];
                p_keys[j] = tmp;
            }
        }
    }
    return p_keys;
}

SPoly *new_poly() {
    // creates a new polynomial and returns a pointer to it.
    SPoly* s = (SPoly*) malloc(sizeof(SPoly));  // allocate memory
    s -> p_poly = new_dict();
    return s;
}

void set_coef(SPoly *p, size_t pow, t_coef coef) {
    // sets the value of the coefficient coef to the degree of pow
    add(p -> p_poly, pow, coef);

}

void update_coef(SPoly *p, size_t pow, t_coef coef) {
    // updates the coefficient of an existing key
    update(p -> p_poly, pow, coef);
}

t_coef get_coef(SPoly *p, size_t pow) {

    // returns the coefficient of a given degree
    return find(p -> p_poly, pow);
}

void print(SPoly *p) {
    // prints polynomial to console
    size_t* p_keys = get_keys(p -> p_poly);
    size_t len = p -> p_poly -> p_table -> last;
    for (size_t i = len - 1; i > 0; i--){
        if (get_coef(p, p_keys[i]) == 0.){continue;}
        printf("%lfx^%zu + ", get_coef(p, p_keys[i]), p_keys[i]);
    }

    if (p_keys[0] == 0){
        printf("%lf\n", get_coef(p, p_keys[0]));
    }
    else{
        printf("%lfx^%zu\n", get_coef(p, p_keys[0]), p_keys[0]);
    }


}

t_coef value(SPoly *s, t_coef x) {
    // returns the value of the polynomial at x
    t_coef val = 0;
    for (size_t i = 0; i < s -> p_poly -> p_table -> last; i++){
        val += find(s -> p_poly, i) * pow(x, i);
    }
    return val;
}

SPoly *input() {
    // standard polynomial introduction

    size_t key;
    t_coef val;



    SPoly* p = new_poly();

    int s;
    while (true){
        printf("Any key to continue / 0 - to stop:\n");
        scanf("%d", &s);
        if (s == 0){
            break;
        }
        printf("Enter degree:\n");
        scanf("%zu" ,&key);

        printf("Enter the coefficient:\n");
        scanf("%lf" ,&val);
        set_coef(p, key, val);
    }
    return p;
}

SPoly *sum(SPoly *p1, SPoly *p2) {
    // returns a pointer to a polynomial
    // which is the sum of the polynomials p1 and p2
    SPoly* res = new_poly();
    size_t *p_keys1 = get_keys(p1 -> p_poly);
    size_t *p_keys2 = get_keys(p2 -> p_poly);

    for (size_t i = 0; i < p1 -> p_poly -> p_table -> last; i++){
        update_coef(res, p_keys1[i], get_coef(res, p_keys1[i]) + get_coef(p1, p_keys1[i]));
    }

    for (size_t i = 0; i < p2 -> p_poly -> p_table -> last; i++){
        update_coef(res, p_keys2[i], get_coef(res, p_keys2[i]) + get_coef(p2, p_keys2[i]));
    }

    return res;
}

SPoly *sub(SPoly *p1, SPoly *p2) {
    // returns a pointer to a polynomial
    // which is the subtraction of the polynomials p1 and p2
    SPoly* res = new_poly();
    size_t *p_keys1 = get_keys(p1 -> p_poly);
    size_t *p_keys2 = get_keys(p2 -> p_poly);

    for (size_t i = 0; i < p1 -> p_poly -> p_table -> last; i++){
        update_coef(res, p_keys1[i], get_coef(res, p_keys1[i]) + get_coef(p1, p_keys1[i]));
    }

    for (size_t i = 0; i < p2 -> p_poly -> p_table -> last; i++){
        update_coef(res, p_keys2[i], get_coef(res, p_keys2[i]) - get_coef(p2, p_keys2[i]));
    }

    return res;
}

SPoly *monom_mul(SPoly *p, SPoly *m) {
    // multiplication of a polynomial by a monomial
    // returns a pointer to the polynom result
    SPoly* res = new_poly();

    size_t* p_keys = get_keys(p -> p_poly);
    size_t m_key = get_keys(m -> p_poly)[0];

    for (size_t i = 0; i < p -> p_poly -> p_table -> last; i++){
        update_coef(res, p_keys[i] + m_key, get_coef(p, p_keys[i]) * get_coef(m, m_key));
    }

    return res;

}

SPoly *mul(SPoly *p1, SPoly *p2) {
    // returns a pointer to a polynomial
    // which is the multiplication of the polynomials p1 and p2
    SPoly* res = new_poly();

    size_t* p1_keys = get_keys(p1 -> p_poly);
    size_t* p2_keys = get_keys(p2 -> p_poly);
    for (size_t i = 0; i < p2 -> p_poly -> p_table -> last; i++){
        SPoly* tmp = new_poly();
        set_coef(tmp, p2_keys[i], get_coef(p2, p2_keys[i]));
        res = sum(res, monom_mul(p1, tmp));
    }
    return res;
}

SPoly *derivative(SPoly *p) {
    // polynomial derivative p
    SPoly* res = new_poly();
    size_t* p_keys = get_keys(p -> p_poly);

    for(size_t i = 0; i < p -> p_poly -> p_table -> last; i++){
        if (p_keys[i] == 0) {continue;}
        update_coef(res, p_keys[i] - 1, get_coef(p, p_keys[i]) * p_keys[i]);

    }

    return res;
}

SPoly *undefinite_integral(SPoly *p) {
    // indefinite integral of the polynomial p
    SPoly* res = new_poly();
    size_t* p_keys = get_keys(p -> p_poly);

    for (size_t i = 0; i < p -> p_poly -> p_table -> last; i++) {

        set_coef(res, p_keys[i] + 1, get_coef(p, p_keys[i]) / (p_keys[i] + 1));
    }
    return res;

}

t_coef definite_integral(SPoly *p, t_coef a, t_coef b) {
    // defined integral of polynomial p from a to b
    // returns value
    return value(undefinite_integral(p), b) - value(undefinite_integral(p), a);
}

SPoly *input_console() {
    // console input
    // one line where the coefficients are separated by a space
    // starting with a free term (degree 0)
    // for example, the string 1 2 0 3 will create the polynomial 3x ^ 3 + 2x + 1
    SPoly* res = new_poly();

    char* str = (char*) malloc(sizeof(char) * 100);

    char sep[10] = " ";

    scanf("%[^\n]s", str);

    char* istr;

    istr = strtok (str,sep);

    // Selection of subsequent parts
    size_t i = 0;

    while (istr != NULL)
    {
        // Conclusion of the next selected part

        set_coef(res, i, (t_coef) atof(istr));
        //        printf ("%d\n", *istr);
        // Selecting the next part of the line
        istr = strtok (NULL, sep);
        i++;
    }
    return res;
}

SPoly *generate(size_t n, size_t m) {
    // returns a pointer to a polynomial
    // with random coefficients
    // dimension n of m members

    srand(time(NULL));

    SPoly* res = new_poly();

    set_coef(res, n, rand() % 400 - 200);

    for (size_t i = 0; i < m - 1; i++){

        size_t pow = 0 + rand() % n;

        while (contains_key(res -> p_poly -> p_table, pow)){
            size_t pow = 0 + rand() % n;
        }

        set_coef(res, pow, rand() % 400 - 200);

    }

    return res;

}

t_coef *find_root(SPoly *p, t_coef a, t_coef b) {
    // Secant method is a root-finding algorithm on the segment [a, b]
    // returns a pointer to an array of 2 elements
    // 0 - polynom value
    // 1 - point at which the polynomial has a root


    const double EPS = 1E-15;
    t_coef x0 = a, x1 = b, tmp_y = value(p, a);
    long i = 0;
    while (fabs(tmp_y) > EPS){
        t_coef func_x1 = value(p, x1);
        t_coef tmp_x = x1;
        x1 = x1 - func_x1 * (x1 - x0) / (func_x1 - value(p, x0));
        x0 = tmp_x;
        tmp_y = value(p ,tmp_x);
        i++;
        if (i > 10000){
            return NULL;  // additional condition in the absence of zero
        }
    }

    t_coef* res = (t_coef*) malloc(sizeof(t_coef) * 2);
    res[0] = tmp_y;
    res[1] = x1;

    return res;

}

void output_to_bin(SPoly *p) {
    // output to binary file
    // specify the absolute path of the file in the PATH
    FILE* f;
    f = fopen(PATH, "wb+");
    size_t* p_keys = get_keys(p -> p_poly);
    size_t len = p -> p_poly -> p_table -> last;
    for (size_t i = len - 1; i > 0; i--){
        if (get_coef(p, p_keys[i]) == 0.) {continue;}
        fprintf(f, "%lfx^%zu + ", get_coef(p, p_keys[i]), p_keys[i]);
    }
    if (p_keys[0] == 0){
        fprintf(f, "%lf\n", get_coef(p, p_keys[0]));
    }
    else{
        fprintf(f, "%lfx^%zu\n", get_coef(p, p_keys[0]), p_keys[0]);
    }
    fclose(f);
}

void output_to_file(SPoly *p) {
    // output to file
    // specify the absolute path of the file in the PATH
    FILE* f;
    f = fopen(PATH, "wt");

    size_t* p_keys = get_keys(p -> p_poly);
    size_t len = p -> p_poly -> p_table -> last;

    for (size_t i = len - 1; i > 0; i--){
        if (get_coef(p, p_keys[i]) == 0.) {continue;}
        fprintf(f, "%lfx^%zu + ", get_coef(p, p_keys[i]), p_keys[i]);
    }

    if (p_keys[0] == 0){
        fprintf(f, "%lf\n", get_coef(p, p_keys[0]));
    }

    else{
        fprintf(f, "%lfx^%zu\n", get_coef(p, p_keys[0]), p_keys[0]);
    }


    fclose(f);

}
