-- Write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.
SELECT p.name FROM people p
INNER JOIN stars s ON p.id = s.person_id
INNER JOIN movies m ON s.movie_id = m.id
WHERE m.id IN (SELECT m.id FROM movies m
                INNER JOIN stars s ON m.id = s.movie_id
                INNER JOIN people p ON s.person_id = p.id
                WHERE p.name = 'Kevin Bacon' AND p.birth = 1958) 
                AND p.id NOT IN (SELECT p.id FROM people p
                WHERE p.name = 'Kevin Bacon' AND p.birth = 1958);