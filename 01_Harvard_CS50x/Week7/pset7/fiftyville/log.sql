-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Initial overview of the crime scene reports during the day of the crime
SELECT description FROM crime_scene_reports WHERE year = 2020 AND month = 7 AND day = 28 AND street = 'Chamberlin Street';
-- Three witnesses mention the courthouse
-- Theft took place at 10:15

-- Check interview from the corresponding date
SELECT transcript FROM interviews WHERE year = 2020 AND month = 7 AND day = 28;
-- Thief was parked at the courthouse's parking lot, and left between 10:15 and 10:25
-- The thief withdrew money from the ATM on Fifer Street earlier the day of the crime
-- Right after the theft, the thief called someone for less than a minute, their accomplice was instructed to buy a plane ticket right away

-- Check courthouse security logs for the date and time interval provided during the interviews
SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = 'exit';
-- Possible licence plates:
--      5P2BI95
--      94KL13X
--      6P58WS2
--      4328GD8
--      G412CB7
--      L93JTIZ
--      322W7JE
--      0NTHK55

-- Check atm_transactions for withdrawals of money on the day of the crime, at Fifer Street
SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = 'Fifer Street' AND transaction_type = 'withdraw';
-- Possible bank accounts:
--      28500762
--      28296815
--      76054385
--      49610011
--      16153065
--      25506511
--      81061156
--      26013199

-- Check phone_calls for calls which took place on the day of the crime and lasted less than 1 minute
SELECT caller, receiver FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60;
-- Possible phone numbers of the thief and their accomplice:
--      Thief           | Accomplice
--      (130) 555-0289  | (996) 555-8899
--      (499) 555-9472  | (892) 555-8872
--      (367) 555-5533  | (375) 555-8161
--      (609) 555-5876  | (389) 555-5198
--      (499) 555-9472  | (717) 555-1342
--      (286) 555-6063  | (676) 555-6554
--      (770) 555-1861  | (725) 555-3243
--      (031) 555-6622  | (910) 555-3251
--      (826) 555-1652  | (066) 555-9701
--      (338) 555-6650  | (704) 555-2131

-- Check for people who exited the couthouse and made a short phone call at the time and date of the theft
SELECT name, passport_number 
FROM people
WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60) 
AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 and MINUTE <= 25 AND activity = 'exit');
-- Possible thief names and passport_numbers:
--      Name    | Passport number
--      Roger   | 1695452385
--      Russell | 3592750733
--      Evelyn  | 8294398571
--      Ernest  | 5773159633

-- Check passengers for the flights and seats the suspects have been involved in
SELECT flight_id, seat 
FROM passengers 
WHERE passport_number IN (SELECT passport_number 
FROM people
WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60) 
AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 and MINUTE <= 25 AND activity = 'exit'));
-- Possible flights and seats taken by the thief and their accomplice:
--      Flight Id   | Seat
--      18          | 4C
--      24          | 2C
--      36          | 3B
--      36          | 4A
--      36          | 6C
--      54          | 6C

-- Check flights for destinations associated to the possible flights (no valid flight took place the day of the theft)
SELECT destination_airport_id
FROM flights 
WHERE origin_airport_id = 8
AND year = 2020 
AND month = 7 
AND day = 29
AND id IN (SELECT flight_id 
FROM passengers 
WHERE passport_number IN (SELECT passport_number 
FROM people
WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60) 
AND license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 and MINUTE <= 25 AND activity = 'exit')));
-- Possible destination ids:
--      6
--      4

