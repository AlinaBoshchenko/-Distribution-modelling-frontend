//
// Created by lesslyrics on 23.02.2020.
//

#include <iostream>
#include <iomanip>
#include "InverseFunctionMethodModel.h"
#include "HyperGeomTheoretical.h"
#include "Model.h"

const int a_alt = 5;
const int b_alt = 5;
const int k_alt = 4;

/** This function finds factorial of large numbers **/
long long int InverseFunctionMethodModel::findFactorial(int num) {
    int fact = 1, i;
    for (i = 1; i <= num; i++)
        fact = fact * i;
    return fact;
}

/**
 * method to activateModel random values using inverse function method
 * @param a
 * @param b
 * @param k
 * @return
 */
int InverseFunctionMethodModel::generateRandomValue(int a, int b, int k) {
    int i = 0;
    int n = a + b;

//    std::cout <<"fac1 " << (long double)(findFactorial(b) * findFactorial(n-k)) <<  std::endl ;
//    std::cout <<"fac2 " << (long double)(findFactorial(n - a - k)) << std::endl;
//    std::cout <<"fac3 " << (long double)(findFactorial(n)) <<  std::endl ;

    long double p =
            (long double) (findFactorial(b) * findFactorial(n - k)) / findFactorial(n - a - k) / findFactorial(n);
    long double l = p;
    long double alpha = randomRange(0, 1);


    while (alpha >= l) {
        p = p * (a - i) * (k - i) / ((i + 1) * (n - a - k + i + 1));
        l += p;
        i++;
    }
    return i;
}

/**
 * Generate distribution
 * @param trials
 * @param a
 * @param b
 * @param k
 * @param nt
 * @param p_fin
 * @param exp_freq
 * @param act_freq
 * @param p_dist
 * @param p_dist_alt
 * @return
 */
void InverseFunctionMethodModel::createDist(int trials, int a, int b, int k, int nt) {

    int q1, q2;

    std::vector<double> h1(a + 1, 0); // histograms
    std::vector<double> h2(a + 1, 0); // histograms


    for (int j = 0; j != nt; ++j) {
        q1 = generateRandomValue(a, b, k);
        q2 = generateRandomValue(a_alt, b_alt, k_alt);
        h1[q1]++;
        h2[q2]++;
    }

    actual_freq.clear();
    actual_alt_freq.clear();

    for (int i = 0; i != a + 1; i++)
        actual_freq.push_back(h1[i]);


    for (int i = 0; i != a + 1; i++)
        actual_alt_freq.push_back(h2[i]);

}