-- Keep a log of any SQL queries you execute as you solve the mystery.

-- .schema and tables to check the tables
.tables
airports              crime_scene_reports   people
atm_transactions      flights               phone_calls
bakery_security_logs  interviews
bank_accounts         passengers
.schema
--CREATE TABLE interviews (
  --  id INTEGER,
   -- name TEXT,
   -- year INTEGER,
   -- month INTEGER,
   -- day INTEGER,
   -- transcript TEXT,
   -- PRIMARY KEY(id)
--);
--enz.

-- to start off with to get description about crimes that day and place
-- took place on July 28, 2021 and that it took place on Humphrey Street.
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28 AND year = 2021
AND street = "Humphrey Street";
--Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
--Interviews were conducted today with three witnesses who were present at the time
--each of their interview transcripts mentions the bakery.
--Littering took place at 16:36. No known witnesses.


--to check what the witnesses had seen
SELECT transcript, name
FROM interviews
WHERE month = 7 AND day = 28 AND year = 2021 AND transcript LIKE "%bakery%";

--Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
--If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
--Ruth
-- Checking Ruth´s statement and getting first suspects.
SELECT name FROM people
INNER JOIN bakery_security_logs
ON bakery_security_logs.license_plate = people.license_plate
WHERE month = 7 AND day = 28 AND year = 2021 AND hour = 10 AND minute >= 15 AND minute <= 25
AND activity = "exit";
-- Suspects : Vanessa Bruce Barry Luca Sofia Iman Diana Kelsey


--I don't know the thief's name, but it was someone I recognized.
--Earlier this morning, before I arrived at Emma's bakery,
--I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
--Eugene
-- Checking Eugene´s statement and getting second set of suspects.
SELECT name FROM people
INNER JOIN bank_accounts
ON bank_accounts.person_id = people.id
INNER JOIN atm_transactions
ON atm_transactions.account_number = bank_accounts.account_number
WHERE month = 7 AND day = 28 AND year = 2021 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";
-- Second suspects: Bruce Diana Brooke Kenny Iman Luca Taylor Benista
-- First suspects : Vanessa Bruce Barry Luca Sofia Iman Diana Kelsey

-- compare suspects list one with list two
-- Matching suspects: Bruce Luca Iman Diana

--As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
--In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
--The thief then asked the person on the other end of the phone to purchase the flight ticket.
--Raymond

--Flight information:
SELECT name FROM people
INNER JOIN passengers
ON passengers.passport_number = people.passport_number
WHERE passengers.flight_id = (SELECT id
FROM flights
WHERE month = 7 AND day = 29 AND year = 2021 AND origin_airport_id =(SELECT id
FROM airports
WHERE city = "Fiftyville")
ORDER BY hour, minute
LIMIT 1);
--New suspects: Doris Sofia Bruce Edward Kelsey Taylor Kenny Luca
-- compare new list with matching suspects
-- Matching suspects: Bruce Luca Iman Diana
--New matching suspects: Luca Bruce

--Caller Phone Numbers check
SELECT name FROM people
INNER JOIN phone_calls
ON phone_calls.caller = people.phone_number
WHERE month = 7 AND day = 28 AND year = 2021 AND duration < 60;
-- New suspects: Sofia Kelsey Bruce Kelsey Taylor Diana Carina Kenny Benista
--Matching suspects: Luca Bruce
--Thief is : Bruce

-- where did they escape to ?
SELECT city
FROM airports
WHERE id = (SELECT destination_airport_id
FROM flights
WHERE month = 7 AND day = 29 AND year = 2021 AND origin_airport_id =(SELECT id
FROM airports
WHERE city = "Fiftyville")
ORDER BY hour, minute
LIMIT 1);
-- Escaped to : New York City

--Finding who Bruce called
--Finding Bruce´s number first
SELECT phone_number FROM people
WHERE name = "Bruce";
--phone_number: (367) 555-5533
--Finding Caller
SELECT name FROM people
WHERE phone_number =(SELECT receiver
FROM phone_calls
WHERE month = 7 AND day = 28 AND year = 2021 AND duration < 60 AND caller = "(367) 555-5533");
--Accomplice is: Robin.