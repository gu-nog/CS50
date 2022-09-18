# SQLite - inside your application
# pip install db-sqlite3
import sqlite3
db = sqlite3.connect('mydb.db')
cursor = db.cursor() # the cursor that we use to run queries
# cursor.execute('CREATE TABLE people (name TEXT, age INTEGER)')
# cursor.execute('INSERT INTO people (name, age) VALUES ("david", 31)')
untrusted_parameters = ('david') # this way to pass parameters is to avoid SQLinjection
print('List of tuple: ', cursor.execute("SELECT * FROM people WHERE name = ?", [untrusted_parameters]).fetchall())
db.commit() # execute this queries
