SELECT AVG(rating) AS "Average Movie Rating" FROM ratings
INNER JOIN movies
ON ratings.movie_id = movies.id
WHERE year == "2012";