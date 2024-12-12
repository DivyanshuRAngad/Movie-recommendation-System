# Movie Recommendation System

## Description
This project implements a personalized movie recommendation system using collaborative filtering in C++. It predicts the ratings for unrated movies based on user similarity and provides top movie recommendations for a given user.

## Features
- **Collaborative Filtering**: Uses cosine similarity to calculate user-to-user relationships.
- **Dynamic Input**: Reads user-movie ratings from a CSV file.
- **Movie Recommendations**: Predicts ratings and outputs the top N recommended movies.
- **Performance Evaluation**: Measures accuracy using Root Mean Square Error (RMSE).

## Prerequisites
- A C++ compiler (e.g., GCC)
- A CSV file with user-movie ratings in the format:
  ```
  5,3,0,1,4
  4,0,0,1,2
  0,1,2,4,0
  3,0,4,0,3
  ```
  Here, rows represent users, columns represent movies, and `0` indicates unrated movies.

## How to Run
1. **Compile the Code**:
   ```bash
   g++ -o recommender main.cpp
   ```

2. **Run the Program**:
   ```bash
   ./recommender
   ```

3. **Input Required**:
   - Enter the filename of the ratings CSV (e.g., `ratings.csv`).
   - Specify the user index (0-based) for whom recommendations are generated.
   - Provide the number of recommendations (e.g., `3`).

4. **Output**:
   - Predicted ratings for unrated movies.
   - A ranked list of the top N recommended movies.

## Example
### Input:
- CSV File: `ratings.csv`
- User Index: `0` (User 1)
- Top N Recommendations: `3`

### Output:
```
Top 3 recommendations for User 1:
Movie 3 with predicted rating: 3.5
Movie 2 with predicted rating: 3.0
```

## Performance Evaluation
- **Metric Used**: RMSE (Root Mean Square Error)
- **Sample Result**: RMSE for the provided example dataset is approximately 0.8.

## Project Structure
- `main.cpp`: Contains the source code for the movie recommendation system.
- `ratings.csv`: Sample dataset for user-movie ratings.
- `Performance_Report.pdf`: Details about system performance and evaluation metrics.

## Observations
- Predictions improve with larger datasets and denser matrices.
- Sparse matrices can reduce accuracy due to fewer similar users.

## Future Enhancements
- Implement item-based collaborative filtering.
- Use advanced algorithms like matrix factorization for better predictions.
- Add a graphical user interface for easier interaction.

## Author
- Developed by Divyanshu Rangad
