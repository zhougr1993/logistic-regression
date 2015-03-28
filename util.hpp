#ifndef _CPP_UTIL_
#define _CPP_UTIL_

#include<iostream>
#include<string>
#include<sstream>
#include<eigen3/Eigen/Dense>

using namespace std;
using namespace Eigen;

//////////////////// utils/////////////////////////////////
template < class T> 
void convert_from_string(T& value, const string& s)
{
    stringstream ss(s);
    ss >> value;
}

double norm(VectorXd v1, VectorXd v2) {
    assert (v1.rows() == v2.rows());
    double sum = 0;
    for (size_t i=0; i<v1.rows(); ++i)
    {
        double minus = v1(i) - v2(i);
        double r = minus * minus;
        sum += r;
    }

    return sqrt(sum);
}


double norm_1(VectorXd& v1, VectorXd& v2) {
    assert (v1.rows() == v2.rows());
    double sum = 0;
    for (size_t i=0; i<v1.size(); ++i)
    {
        double minus = abs(v1(i) - v2(i));
        sum += minus;
    }

    return sum;
}

#endif
