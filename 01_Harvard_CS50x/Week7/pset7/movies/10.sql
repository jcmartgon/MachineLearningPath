-- Write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0.
SELECT people.name FROM people 
INNER JOIN directors ON people.id = directors.person_id 
INNER JOIN movies ON directors.movie_id = movies.id 
INNER JOIN ratings ON movies.id = ratings.movie_id
WHERE ratings.rating >= 9.0;