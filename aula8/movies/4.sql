SELECT COUNT(movies.title) FROM movies, ratings WHERE movies.id = ratings.movie_id and ratings.rating = 10.0;
