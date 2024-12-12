#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

// Function to load the user-movie ratings matrix from a CSV file
vector<vector<double>> loadRatingsMatrix(const string& filename) {
    vector<vector<double>> matrix;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        vector<double> row;
        string value;

        while (getline(ss, value, ',')) {
            row.push_back(stod(value)); // Convert string to double
        }
        matrix.push_back(row);
    }

    return matrix;
}

// Function to calculate cosine similarity between two users
double calculateSimilarity(const vector<double>& user1, const vector<double>& user2) {
    double dotProduct = 0, norm1 = 0, norm2 = 0;
    for (size_t i = 0; i < user1.size(); ++i) {
        dotProduct += user1[i] * user2[i];
        norm1 += user1[i] * user1[i];
        norm2 += user2[i] * user2[i];
    }
    return (norm1 == 0 || norm2 == 0) ? 0 : dotProduct / (sqrt(norm1) * sqrt(norm2));
}

// Predict ratings for a specific user
vector<double> predictRatings(const vector<vector<double>>& matrix, int userIndex) {
    vector<double> predictions(matrix[userIndex].size(), 0);

    for (size_t movie = 0; movie < matrix[userIndex].size(); ++movie) {
        if (matrix[userIndex][movie] == 0) { // Predict only for unrated movies
            double weightedSum = 0, similaritySum = 0;

            for (size_t otherUser = 0; otherUser < matrix.size(); ++otherUser) {
                if (userIndex != otherUser && matrix[otherUser][movie] != 0) {
                    double similarity = calculateSimilarity(matrix[userIndex], matrix[otherUser]);
                    weightedSum += similarity * matrix[otherUser][movie];
                    similaritySum += abs(similarity);
                }
            }

            predictions[movie] = (similaritySum != 0) ? weightedSum / similaritySum : 0;
        }
    }

    return predictions;
}

// Recommend top N movies for a specific user
void recommendMovies(const vector<vector<double>>& matrix, int userIndex, int topN) {
    vector<double> predictedRatings = predictRatings(matrix, userIndex);
    vector<pair<double, int>> movieRatings;

    for (size_t i = 0; i < predictedRatings.size(); ++i) {
        if (matrix[userIndex][i] == 0) { // Only consider unrated movies
            movieRatings.push_back({predictedRatings[i], i});
        }
    }

    // Sort movies by predicted ratings in descending order
    sort(movieRatings.rbegin(), movieRatings.rend());

    cout << "Top " << topN << " recommendations for User " << userIndex + 1 << ":\n";
    for (int i = 0; i < topN && i < movieRatings.size(); ++i) {
        cout << "Movie " << movieRatings[i].second + 1
             << " with predicted rating: " << movieRatings[i].first << endl;
    }
}

int main() {
    string filename;
    cout << "Enter the filename of the ratings CSV: ";
    cin >> filename;

    vector<vector<double>> matrix = loadRatingsMatrix(filename);

    int userIndex;
    cout << "Enter the user index (0-based): ";
    cin >> userIndex;

    int topN;
    cout << "Enter the number of recommendations to generate: ";
    cin >> topN;

    recommendMovies(matrix, userIndex, topN);

    return 0;
}
