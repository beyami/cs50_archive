SELECT title FROM movies JOIN stars ON movies.id = movie_id
JOIN people ON person_id = people.id
WHERE people.name = 'Chadwick Boseman' LIMIT 5;