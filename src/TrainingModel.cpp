#include "TrainingModel.h"
#include "CSVRow.h"

/* sigmoid funciton for a single value */
double sigmoid(double value)
{
    return 1 / (1 + std::exp(-1 * value));
}

/* sigmoid function using vectorization */
mat sigmoid(mat matrix)
{
    return 1 / (1 + exp(-1 * matrix));
}

/*
Make the results matrix for given teams.
Team1 winning the match is equivalent to 3 points, losing the match is equivalent to 0 point.
If there's no winner, i.e. two teams drew the match, it is equivalent to 1 point.

returms the matrix that contains all the results of the training examples
*/
mat makeResultMatrix(string team1, string team2, int num_of_exs, string file_name)
{
    ifstream file(file_name);

    mat result_matrix(num_of_exs, 1);
    int mat_row_index = 0;

    for (CSVIterator loop(file); loop != CSVIterator(); ++loop) {

        // index 0 is Home team and index 1 is Away team
        if ((*loop)[0] == team1 && (*loop)[1] == team2)
        {
            // check the full time result to figure out the winner of the match
            if ((*loop)[4] == "H")
            {
                // set as 3 if team1 won
                result_matrix(mat_row_index, 0) = 3;
                mat_row_index++;
            }
            else if ((*loop)[4] == "A")
            {
                // set as 0  if team 1 lost
                result_matrix(mat_row_index, 0) = 0;
                mat_row_index++;
            }
            else
            {
                // set as 1 if they drew
                result_matrix(mat_row_index, 0) = 1;
                mat_row_index++;
            }
        }

        // index 0 is Home team and index 1 is Away team
        else if ((*loop)[0] == team2 && (*loop)[1] == team1)
        {
            // check the full time result to figure out the winner of the match
            if ((*loop)[4] == "H")
            {
                // set as 0 if team1 lost
                result_matrix(mat_row_index, 0) = 0;
                mat_row_index++;
            }
            else if ((*loop)[4] == "A")
            {
                // set as 3  if team 1 won
                result_matrix(mat_row_index, 0) = 3;
                mat_row_index++;
            }
            else
            {
                // set as 1 if they drew
                result_matrix(mat_row_index, 0) = 1;
                mat_row_index++;
            }
        }
    }

    file.close();

    return result_matrix;
}

mat makeFeatureMatrix(string team1, string team2, int num_of_exs, string file_name)
{
    ifstream file(file_name);

    int num_of_features = 8;
    mat feature_matrix(num_of_exs, num_of_features);
    int mat_row_index = 0;

    for (CSVIterator loop(file); loop != CSVIterator(); ++loop) {
        if ((*loop)[0] == team1 && (*loop)[1] == team2)
        {
            feature_matrix(mat_row_index, 0) = 1; // team1 is home team, hence set as 1
            feature_matrix(mat_row_index, 1) = 0; // team 1 is away team, hence set as 0
            feature_matrix(mat_row_index, 2) = stod((*loop)[5]); // Home team Total Shots
            feature_matrix(mat_row_index, 3) = stod((*loop)[6]); // Away team Total Shots
            feature_matrix(mat_row_index, 4) = stod((*loop)[7]); // Home team Shots on Target
            feature_matrix(mat_row_index, 5) = stod((*loop)[8]); // Away team Shots on Target
            feature_matrix(mat_row_index, 6) = stod((*loop)[11]); // Home team Red Cards
            feature_matrix(mat_row_index, 7) = stod((*loop)[12]); // Away team Red Cards

            mat_row_index++;
        }
        else if ((*loop)[0] == team2 && (*loop)[1] == team1)
        {
            feature_matrix(mat_row_index, 0) = 0; // team1 is away team, hence set as 0
            feature_matrix(mat_row_index, 1) = 1; // team1 is home team, hence set as 1
            feature_matrix(mat_row_index, 2) = stod((*loop)[5]); // Home team Total Shots
            feature_matrix(mat_row_index, 3) = stod((*loop)[6]); // Away team Total Shots
            feature_matrix(mat_row_index, 4) = stod((*loop)[7]); // Home team Shots on Target
            feature_matrix(mat_row_index, 5) = stod((*loop)[8]); // Away team Shots on Target
            feature_matrix(mat_row_index, 6) = stod((*loop)[11]); // Home team Red Cards
            feature_matrix(mat_row_index, 7) = stod((*loop)[12]); // Away team Red Cards
            
            mat_row_index++;
        }
    }

    file.close();

    return feature_matrix;
}
