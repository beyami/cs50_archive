SELECT title FROM movies JOIN stars ON movies.id = movie_id
JOIN people ON person_id = people.id
WHERE people.name = 'Johnny Depp' AND movies.title IN
(SELECT movies.title FROM movies JOIN stars ON movies.id = movie_id
JOIN people ON person_id = people.id
WHERE people.name = 'Helena Bonham Carter');