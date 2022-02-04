#pragma once
#include <armadillo>
#include <string>

using namespace arma;
using namespace std;

double sigmoid(double value); // scalar sigmoid;
mat sigmoid(mat matrix); // matrix/vector sigmoid;

int countTrainingExamples(string team1, string team2, string file_name); // coount number fo training examples 

mat makeResultMatrix(string team1, string team2, int num_of_exs, string file_name);
mat makeFeatureMatrix(string team1, string team2, int num_of_exs, string file_name);

