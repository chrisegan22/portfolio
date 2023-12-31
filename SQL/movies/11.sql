SELECT title FROM movies
INNER JOIN stars
ON movies.id = stars.movie_id
INNER JOIN people
ON stars.person_id = people.id
INNER JOIN ratings
ON ratings.movie_id = movies.id
WHERE name == "Chadwick Boseman"
ORDER BY rating DESC LIMIT "5";