/*
 * rational.h
 *
 *  Created on: 05/08/2015
 *      Author: pperezm
 */

#ifndef RATIONAL_H_
#define RATIONAL_H_

#include "exception.h"
#include <string>
#include <sstream>

class Rational {
private:
	int numerator;
	int denominator;

	void normalize();

public:
	Rational();
	Rational(int);
	Rational(int, int);
	Rational(const Rational&);

	int getNumerator() const;
	int getDenominator() const;
	std::string toString() const;

	void operator=   (const Rational&);
	void operator+=  (const Rational&);

	operator double () const;
};

Rational::Rational() {
    numerator = 0;
    denominator = 1;
}

Rational::Rational(int num){
    numerator = num;
    denominator = 1;
}

Rational::Rational(int num, int dem){
    if (dem == 0){
		throw RangeError();
        numerator = 0;
        denominator = 1;
    }else{
        numerator = num;
        denominator = dem;
    }
	normalize();
}


int Rational::getNumerator() const {
	return numerator;
}

int Rational::getDenominator() const {
	return denominator;
}

std::string Rational::toString() const {
	std::stringstream aux;

	aux << numerator << "/" << denominator;
	return aux.str();
}

void Rational::operator= (const Rational &right) {
	numerator = right.getNumerator();
	denominator = right.getDenominator();

	normalize();
}

void Rational::operator+= (const Rational &right) {
	numerator = numerator * right.getDenominator() + denominator * right.getNumerator();
	
	denominator = denominator * right.getDenominator();

	// get the same denominator

	normalize();
}

Rational::operator double () const {
	return (double) numerator / (double) denominator ;
}

int gcd(int a, int b) {
	int aux;

	while (b != 0) {
		aux = b;
		b = a % b;
		a = aux;
	}
	return a;
}

void Rational::normalize() {
	int gcdd = gcd(numerator, denominator);
	numerator = numerator /  gcdd;
	denominator = denominator / gcdd;
	// deal with negative numbers
	// one negative, both negative, etc

	// si los dos son + o - entonces es positivo
	if (denominator < 0) {
		numerator = -1 * numerator;
		denominator = -1 * denominator;
	}

}

Rational operator+ (const Rational &left, const Rational &right) {
	int new_numerator = left.getNumerator() * right.getDenominator() + left.getDenominator() * right.getNumerator();
	int new_denominator = left.getDenominator() * right.getDenominator();

	// get the same denominator
	return Rational(new_numerator, new_denominator);
}

Rational operator- (const Rational &left, const Rational &right) {
	int new_numerator = left.getNumerator() * right.getDenominator() - left.getDenominator() * right.getNumerator();
	int new_denominator = left.getDenominator() * right.getDenominator();

	// get the same denominator
	return Rational(new_numerator, new_denominator);
}

Rational operator- (const Rational &right) {
	
	return Rational(-right.getNumerator(), right.getDenominator());
}

bool operator== (const Rational &left, const Rational &right) {
	
	return left.getNumerator() == right.getNumerator() && left.getDenominator() == right.getDenominator();
}

bool operator<  (const Rational &left, const Rational &right) {
	return (double) left < (double) right;
}

#endif /* RATIONAL_H_ */
