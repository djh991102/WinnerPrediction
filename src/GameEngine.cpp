#include "GameEngine.h"
#include "CSVRow.h"
#include <fstream>
#include <iostream>

GameEngine::GameEngine(string team1, string team2):
    team1(team1), team2(team2)
{
    ifstream file(FILE_NAME); // open the file

    int num_of_exs = 0;

    // count the number of training examples
    for (CSVIterator loop(file); loop != CSVIterator(); ++loop) {
        if ((*loop)[0] == team1 && (*loop)[1] == team2)
        {
            num_of_exs++;
        }
        else if ((*loop)[0] == team2 && (*loop)[1] == team1)
        {
            num_of_exs++;
        }
    }

    this->num_of_exs = num_of_exs; // save the number of examples 

    file.close();

    // After counting number of examples, set the size of each matrix
    win_result_matrix.set_size(num_of_exs, 1);
    draw_result_matrix.set_size(num_of_exs, 1);
    lose_result_matrix.set_size(num_of_exs, 1);

    // initialize the parameters to 0
    parameters.set_size(9, 1); // number of features + additional column vector = 8 + 1 = 9
    parameters.zeros();
}

/*
Set a new result matrix with given home_team and away_team
*/
void GameEngine::setResultMatrix()
{
    // call TrainingModel's function to creat a new result matrix;
    result_matrix = makeResultMatrix(team1, team2, num_of_exs, FILE_NAME);

    result_matrix.print("Records:");

    // set matrix for "one vs rest" algorithm
    for (int i = 0; i < num_of_exs; i++) {
        
        // set win_result_matrix element as 1 if team1 won
        if (result_matrix(i) == 3.0)
        {
            win_result_matrix(i) = 1;
            draw_result_matrix(i) = 0;
            lose_result_matrix(i) = 0;
        }
        // set draw_result_matrix element as 1 if there's no winner
        else if (result_matrix(i) == 1.0)
        {
            win_result_matrix(i) = 0;
            draw_result_matrix(i) = 1;
            lose_result_matrix(i) = 0;
        }
        // set lost_result_matrix element as 1 if team1 lost
        else
        {
            win_result_matrix(i) = 0;
            draw_result_matrix(i) = 0;
            lose_result_matrix(i) = 1;
        }
    }
}

/*
Set a new feature matrix with given home_team and away_team
*/
void GameEngine::setFeatureMatrix()
{
    // call TrainingModel's function to create a new feature matrix;
    feature_matrix = makeFeatureMatrix(team1, team2, num_of_exs, FILE_NAME);
    
    // add the vector filled with one in the first column
    feature_matrix = join_horiz(ones(num_of_exs, 1), feature_matrix);
}

mat GameEngine::getWinResultMatrix() const
{
    return win_result_matrix;
}

mat GameEngine::getDrawResultMatrix() const
{
    return draw_result_matrix;
}

mat GameEngine::getLoseResultMatrix() const
{
    return lose_result_matrix;
}

mat GameEngine::getParameters() const
{
    return parameters;
}

/*
Compute the squared Error of our hypothesis with given parameters
*/
double GameEngine::computeCost(mat result_matrix) const
{
    // compute each hypotehsis with given features and parameters
    mat hypothesis = sigmoid(feature_matrix * parameters);

    // compute the errors
    mat errors = (-1 * result_matrix).t() * 
        log10(hypothesis) - (1 - result_matrix).t() * log10(1 - hypothesis);

    // compute the cost
    double cost = errors(0, 0) / 16;

    return cost;
}

void GameEngine::gradientDescent(mat result_matrix)
{
    double learning_rate = 0.02; 
    mat gradient(9, 1);

    for (int i = 0; i < 2000; i++) {
        gradient = (feature_matrix.t() * (sigmoid( feature_matrix* parameters) - result_matrix)) / 16;

        parameters = parameters - learning_rate * gradient;
    }

    parameters.print("Parameters After Gradient descent:");
}

void GameEngine::resetParameters()
{
    // reset parameters to zeros
    parameters.zeros();
}