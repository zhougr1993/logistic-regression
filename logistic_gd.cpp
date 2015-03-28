#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//row for Matrix
//u can get it from http://eigen.tuxfamily.org/dox/group__TutorialMatrixArithmetic.html
#include <eigen3/Eigen/Dense>

#include "util.hpp"
#include "data_loader.hpp"

using namespace Eigen;
using namespace std;

bool debug = true;
VectorXd sigmoid_V(VectorXd in_v){
    double e = 2.718281828;
    VectorXd out_v(in_v.rows());
    for(int i = 0;i<in_v.rows();i++){
        out_v(i) = 1.0/(1.0 + pow(e,-in_v(i)));
    }
    return out_v;
}
//
double sigmoid(double x) {
    double e = 2.718281828;

    return 1.0 / (1.0 + pow(e, -x));
}

//gd to optimization
    // the convergence rate epsilon
    // the learning rate gamma
    // the max training times max_iters
VectorXd lr_gd(MatrixXd& x,
        VectorXd& y,double epsilon,double gamma,int max_iters
        ) {

    int iter = 0;
    // init
    VectorXd weight_old(x.cols());
    for (size_t i=0; i<weight_old.rows(); ++i) {
        weight_old(i) = 0; 
    } 

    cout << "old weight: " << weight_old << endl;

    VectorXd weight_new(x.cols());
    for (size_t i=0; i<weight_new.rows(); ++i) {
        weight_new(i) = 0; 
    } 
    cout << "new weight: " << weight_new << endl;
    
    while (true) {
        // update each weight
        VectorXd errors(x.rows());
        errors = sigmoid_V(x*weight_old)-y;
        MatrixXd X_T = x;
        X_T.transposeInPlace();
        weight_new = weight_old - X_T*errors*gamma;
        double dist = norm(weight_new, weight_old);
        if (dist < epsilon) {
            cout << "the best weight: " << weight_new << endl;
            break;
        }
        else {
            weight_old=weight_new;
           // weight_old = weight_new;
        }

        iter += 1;
        if (iter >= max_iters) {
            cout << "Reach max_iters=" << max_iters << endl;
            break;
        }
    /* for debug 
        cout << "================================================" << endl;
        cout << "The " << iter << " th iteration, weight:" << endl;
        cout << weight_new << endl << endl;
        cout << "the diff between the old weight and the new weight: " << dist << endl << endl;
    */
    }

    cout << "The best weight:" << endl;
    cout << weight_new << endl;
    return weight_new;
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cout << "Usage: " << argv[0] << "data_file" << "epsilon"<<" gama"<<"Max iters"<<endl;
        return -1;
    }

    const int record_num = 100;//nums of training data
    const int dim_num = 4 + 1;//nums of dim for feature
    double epsilon = 0;
    epsilon = atof(argv[2]);
    double gama = 0;
    gama = atof(argv[3]);
    int Max_iters = 0;
    Max_iters = atoi(argv[4]);
    VectorXd y(record_num);
    MatrixXd x(record_num, dim_num);
    SimpleDataLoader loader(record_num, dim_num);
    loader.load_file(argv[1], y, x);
    VectorXd weight(dim_num);
    // lr_gd_method
    weight = lr_gd(x, y,epsilon,gama,Max_iters);
    //for test your classifier u may need it
    /*
    for(int i=0;i<record_num;i++){
        //cout<<x.row(i)<<endl;
        cout<<sigmoid(x.row(i)*weight)<<" y value:"<<y(i)<<endl;
    }*/
    
    return 0;
}
