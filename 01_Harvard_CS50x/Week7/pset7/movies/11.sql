-- Write a SQL query to list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated
SELECT movies.title FROM people 
INNER JOIN stars ON people.id = stars.person_id 
INNER JOIN movies ON stars.movie_id = movies.id 
INNER JOIN ratings ON movies.id = ratings.movie_id
WHERE people.name == 'Chadwick Boseman'
ORDER BY ratings.rating DESC
LIMIT 5;