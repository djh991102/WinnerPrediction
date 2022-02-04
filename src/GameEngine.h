#include <string>
#include "TrainingModel.h";

using namespace std;

class GameEngine
{
private:
    const string FILE_NAME = "C:\\Users\\djh99\\Downloads\\Big6.csv";

    string team1, team2;
    int num_of_exs;

    mat feature_matrix;
    mat result_matrix;

    mat win_result_matrix;
    mat draw_result_matrix;
    mat lose_result_matrix;

    mat parameters; // initially, it will be filled with zeros

    double learning_rate; // learning rate will determine the rate of convergence

public:
    GameEngine(string team1, string team2); // set teams to train the model

    void setResultMatrix();
    void setFeatureMatrix();

    mat getWinResultMatrix() const;
    mat getDrawResultMatrix() const;
    mat getLoseResultMatrix() const;

    mat getParameters() const;

    double computeCost(mat result_matrix) const;

    void gradientDescent(mat result_matrix);

    void resetParameters();

};