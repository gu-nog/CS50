from cs50 import SQL
db = SQL("sqlite:///testes.db")
min_age = input('Min age: ')
rows = db.execute("SELECT * FROM tests WHERE age > ?;", min_age) # list
for row in rows: # dicts
    print(row)
