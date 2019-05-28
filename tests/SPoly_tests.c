#include "../headers/SPoly.h"




int main(int argc, const char * argv[]) {

    // tests

//
//    SPoly - structure sparse polynomial
//    given by the dictionary (degree: coefficient)

    // SPoly* generate(size_t n, size_t m) - returns a pointer to a random polynomial of dimension n from m terms

    SPoly *generated1 = generate(15, 4);

    //    method print(SPoly* p) - prints the polynomial p to the console

    printf("random polynomial:  ");

    print(generated1);

    // SPoly* derivative(SPoly* p) - returns a pointer to a polynomial - a derivative of the polynomial p

    SPoly* der1 = derivative(generated1);

    printf("its derivative: ");

    print(der1);

    // SPoly* undefinite_integral(SPoly* p) - returns a pointer to a polynomial - the indefinite integral of the polynomial p

    SPoly* undef_integ1 = undefinite_integral(generated1);

    printf("its indefinite integral: ");

    print(undef_integ1);


    // t_coef value(SPoly* p, t_coef x) - returns the value of the polynomial p at the point x

    t_coef x = 0.75;

    t_coef val1 = value(generated1, x);

    printf("value of polynomial at point x = 0.75 : %lf:\n", val1);

    // t_coef definite_integral(SPoly* p, t_coef a, t_coef b) - returns the value of the defined integral p from a to b

    t_coef a = -10, b = 25;

    t_coef def_integ1 = definite_integral(generated1, a, b);

    printf("definite integral from a = -10 to b = 25: %lf\n", def_integ1);



    // create a second random polynomial


    SPoly* generated2 = generate(10, 6);

    printf("second random polynomial: ");

    print(generated2);

    // check arithmetic operations:


    // SPoly* sum(SPoly* p1, SPoly* p2) - returns a pointer to a polynomial - the sum of the polynomials p1 and p2

    printf("the sum: ");

    print(sum(generated1, generated2));


    // SPoly* sub(SPoly* p1, SPoly* p2) - returns a pointer to a polynomial - subtracting the polynomials p1 and p2

    printf("subtracting: ");

    print(sub(generated1, generated2));


    // SPoly* mul(SPoly* p1, SPoly* p2) - returns a pointer to a polynomial - multiplication of the polynomials p1 and p2

    printf("multiplication: ");

    print(mul(generated1, generated2));

    return 0;

}
