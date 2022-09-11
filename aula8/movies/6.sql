SELECT AVG(ratings.rating) FROM movies, ratings WHERE movies.id = ratings.movie_id and movies.year == 2012;
