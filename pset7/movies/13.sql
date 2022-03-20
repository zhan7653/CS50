SELECT DISTINCT people.name FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON movies.id = stars.movie_id
WHERE NOT people.name='Kevin Bacon' AND movies.title IN(
SELECT title FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON people.id = stars.person_id
WHERE people.name='Kevin Bacon' AND people.birth=1958);