-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Get information about the crime scene
SELECT * FROM crime_scene_reports
WHERE year=2020 AND month=7 AND day=28 AND street='Chamberlin Street';
-- The theft happened at 10:15am at courthouse. 
-- Interviews were conducted today with three witnesses, each of them mentioned the courthouse.

-- Get information about the interviews
SELECT id, name, transcript FROM interviews
WHERE year=2020 AND month=7 AND day=28;
-- The thief get into a car in the courthouse parking pot lot and drive away at 10:15~10:25am.
-- The thief was withdrawing some money by the ATM on Fifer Street earlier that morning.
-- The thief called someone on that day for less than a minute, said that they were palnning to take the earliest flight out of Fiftyville tomorrow.
-- The thief's accomplice helped them purchase the flight ticket.

-- Check license plate from the courthouse_security_logs
SELECT activity, license_plate FROM courthouse_security_logs
WHERE year=2020 AND month=7 AND day=28 AND hour=10 AND (minute BETWEEN 15 AND 25);

-- Check account_number from the atm_transactions
SELECT account_number FROM atm_transactions
WHERE year=2020 AND month=7 AND day=28 AND atm_location='Fifer Street' AND transaction_type='withdraw';

-- Check phone numbers from the phone_calls
SELECT caller,receiver FROM phone_calls
WHERE year=2020 AND month=7 AND day=28 AND duration <= 60;

-- Get the thief's name by the information we have got.
SELECT name FROM people
WHERE phone_number IN(
SELECT caller FROM phone_calls
WHERE year=2020 AND month=7 AND day=28 AND duration <= 60)
AND id IN(
SELECT person_id FROM bank_accounts
WHERE account_number IN(
SELECT account_number FROM atm_transactions
WHERE year=2020 AND month=7 AND day=28 AND atm_location='Fifer Street' AND transaction_type='withdraw'))
AND license_plate IN(
SELECT license_plate FROM courthouse_security_logs
WHERE year=2020 AND month=7 AND day=28 AND hour=10 AND (minute BETWEEN 15 AND 25));
-- We get two names: Russell and Ernest.

-- Get their passport_number
SELECT passport_number FROM people
WHERE name='Russell' OR name='Ernest';

-- Get all their flight_id
SELECT flight_id FROM passengers
WHERE passport_number IN(
SELECT passport_number FROM people
WHERE name='Russell');
-- Russell's flight_id: 18, 24, 54
SELECT flight_id FROM passengers
WHERE passport_number IN(
SELECT passport_number FROM people
WHERE name='Ernest');
-- Ernest's flight_id: 36


-- Get the id of the airport in Fiftyville.
SELECT id FROM airports
WHERE city='Fiftyville';
-- It's 8.

-- Check all the flights we get.
SELECT * FROM flights
WHERE id IN(
SELECT flight_id FROM passengers
WHERE passport_number IN(
SELECT passport_number FROM people
WHERE name='Russell' OR name='Ernest'));
-- Only flight_id 36 matches, destination_airport_id is 4.
-- The thief is Ernest

-- Get the city the thief escaped to.
SELECT city FROM airports
WHERE id=4;
-- London

-- Get the thief's accomplice.
SELECT name FROM people
WHERE phone_number=(
SELECT receiver FROM phone_calls
WHERE year=2020 AND month=7 AND day=28 AND duration <= 60 AND caller=(
SELECT phone_number FROM people
WHERE name='Ernest'));
-- Berthold



