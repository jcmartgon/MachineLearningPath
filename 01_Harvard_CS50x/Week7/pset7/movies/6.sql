-- Write a SQL query to determine the average rating of all movies released in 2012.
SELECT CAST((AVG(ratings.rating) * 100) as int) / 100.0 FROM ratings INNER JOIN movies ON ratings.movie_id = movies.id;
