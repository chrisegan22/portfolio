SELECT title, rating FROM movies
INNER JOIN ratings
ON ratings.movie_id = movies.id
WHERE (SELECT rating FROM ratings
WHERE year == "2010")
ORDER BY rating DESC, title ASC;