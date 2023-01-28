SELECT distinct(name) FROM people JOIN stars ON people.id = person_id
JOIN movies ON movie_id = movies.id
WHERE movies.title IN
(SELECT distinct(title) FROM movies JOIN stars ON movies.id = movie_id
JOIN people ON person_id = people.id
WHERE people.name = 'Kevin Bacon' AND people.birth = 1958)
AND people.name != 'Kevin Bacon';