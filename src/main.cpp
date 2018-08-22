/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: dube_
 *
 * Created on 22 August 2018, 10:28 PM
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <Eigen/Eigenvalues> 
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;
using Eigen::MatrixXd;
using Eigen::Matrix2f;

struct {

    void operator()(float a) {
	cout << a << ", ";
    }
} print;

pair<vector<float>, vector<float>> get_data(string file_name) {
    ifstream input_file(file_name);
    pair<vector<float>, vector<float>> data;
    float temp_x, temp_y;
    while (input_file >> temp_x >> temp_y) {
	data.first.push_back(temp_x);
	data.second.push_back(temp_y);
    }
    return data;
}

float mean(vector<float> data) {
    float sum = 0, counter = 0;
    for (float a : data) {
	sum += a;
	++counter;
    }
    return sum / counter;
}

vector<float> subtract_mean(vector<float> data) {
    float data_mean = mean(data);
    vector<float> adjusted_data;
    for (float a : data) {
	adjusted_data.push_back(a - data_mean);
    }
    return adjusted_data;
}

Matrix2f cov(vector<float> x, vector<float> y) {
    Matrix2f result;
    /* the expection is a matrix as below:
     *	cov(x x), cov(x y)
     *	cov(y, x), cov(y, y)
     */
    float x_min = mean(x);
    float y_min = mean(y);
    float varx;
    float vary;
    float varxy;
    for (int i = 0; i < x.size(); ++i) {
	varx += (x[i] - x_min)*(x[i] - x_min);
	vary += (y[i] - y_min)*(y[i] - y_min);
	varxy += (x[i] - x_min)*(y[i] - y_min);
    }

    varx /= x.size() - 1;
    vary /= y.size() - 1;
    varxy /= x.size() - 1;
    result(0, 0) = varx;
    result(1, 0) = result(0, 1) = varxy;
    result(1, 1) = vary;

    return result;
}

void calculate_eigenvectors(Matrix2f cov_matrice) {
    EigenSolver<Matrix2f> ces(cov_matrice, false);
    cout << "The first eigenvector of the 3x3 matrix of ones is:"
	    << endl << ces.eigenvalues() << endl;
}

/*
 * 
 */
int main(int argc, char** argv) {
    pair<vector<float>, vector<float>> d = get_data("resources/testing.dat");
    vector<float > x = d.first;
    vector<float> y = d.second;
    x = subtract_mean(x);
    y = subtract_mean(y);
    x[3] = 0.09;
    std::for_each(x.begin(), x.end(), print);
    cout << endl;
    std::for_each(y.begin(), y.end(), print);
    cout << endl;
    Matrix2f m = cov(x, y);
    calculate_eigenvectors(m);
    cout << m;
    return 0;
}

