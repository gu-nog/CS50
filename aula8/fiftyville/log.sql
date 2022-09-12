-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM people WHERE phone_number='(676) 555-6554';
SELECT * FROM bakery_security_logs WHERE day=28 AND montSELECT * FROM airports where id IN (SELECT destination_airport_id FROM people, passengers, flights WHERE people.name = 'Taylor' AND passengers.passport_number=people.passport_number AND flights.month=7 AND flights.day=29);
SELECT receiver FROM phone_calls WHERE caller = '(286) 555-6063' AND day=28 AND month=7 AND duration < 60;
SELECT * FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE day=28 AND month=7 AND duration < 60);
SELECT * FROM atm_transactions, bank_accounts, people WHERE bank_accounts.account_number=atm_transactions.account_number AND people.id=bank_accounts.person_id AND atm_transactions.day=28 AND atm_transactions.month=7 AND atm_transactions.transaction_type='withdraw' AND atm_transactions.atm_location='Leggett Street' AND people.name IN (SELECT people.name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE day=28 AND month=7 AND duration < 60));
SELECT * FROM bakery_security_logs WHERE day=28 AND month=7 AND hour=10 AND minute > 30;
SELECT * FROM airports where id IN (SELECT destination_airport_id FROM people, passengers, flights WHERE people.name = 'Taylor' AND passengers.passport_number=people.passport_number AND flights.month=7 AND flights.day=29);
SELECT people.* FROM atm_transactions, bank_accounts, people WHERE bank_accounts.account_number=atm_transactions.account_number AND people.id=bank_accounts.person_id AND atm_transactions.day=28 AND atm_transactions.month=7 AND atm_transactions.transaction_type='withdraw' AND atm_transactions.atm_location='Leggett Street';
