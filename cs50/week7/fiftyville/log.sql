SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28;
SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;
--the information of interview into one sentence.
SELECT * FROM people JOIN phone_calls ON people.phone_number = phone_calls.caller
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
    AND phone_number IN(SELECT phone_number FROM people
        JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
            WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28
            AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute >= 15 AND bakery_security_logs.minute < 25)
    AND people.id IN (SELECT person_id FROM bank_accounts
        JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
            WHERE atm_transactions.year = 2021 AND atm_transactions.month = 7 AND atm_transactions.day = 28
            AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw')
    AND people.passport_number IN (
        SELECT passport_number FROM passengers
        WHERE flight_id IN (
            SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29
            ORDER BY hour, minute ASC LIMIT 1
        )
    );

--the thief is Bruce, and the phone's receiver is (375) 555-8161
--search the receiver
SELECT * FROM people WHERE phone_number = '(375) 555-8161';
--Robin is the receiver
--Bruce's passport_number is 5773159633
--search the flight and the destination

SELECT * FROM airports JOIN flights ON airports.id = flights.destination_airport_id
JOIN passengers ON flight_id = flights.id
    WHERE passengers.passport_number = 5773159633;
--Bruce run away to New York City.