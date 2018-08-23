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
#include "../includes/Eigen/Eigenvalues"
#include "../includes/Eigen/Dense"

#define DEFAULT_FILE "resources/testing.dat"
#define RESULT  "result/results.dat"

using namespace std;
using namespace Eigen;

ofstream file(RESULT);
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
    float x_min = mean(x), y_min = mean(y);
    float varx, vary, varxy;
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
    EigenSolver<Matrix2f> es;
    es.compute(cov_matrice, false);
    file << "\n\nThe eigenvalue for principle component 1 and 2 are:\n" << es.eigenvalues() << endl;
    EigenSolver<Matrix2f> ces(cov_matrice);
    file << "\n\nThe eigenvector corresponding to the first principal component is:\n" << ces.eigenvectors().col(0) << endl;
    file << "\n\nThe eigenvector corresponding to the second principal component is:\n" << ces.eigenvectors().col(1) << endl;

}

void perform_algorithm(string input_filename) {
    pair<vector<float>, vector<float>> d = get_data(input_filename);
    vector<float > x = subtract_mean(d.first);
    vector<float> y = subtract_mean(d.second);
    Matrix2f m = cov(x, y);
    file << "The covariance matrix is:\n" << m << endl;
    calculate_eigenvectors(m);
}

/*
 * 
 */
int main(int argc, char** argv) {
    file << "*****************************Results*****************************\n" << endl;
    perform_algorithm(argc > 1 ? argv[1] : DEFAULT_FILE);
    file.close();
}

