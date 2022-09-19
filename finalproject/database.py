from shutil import ExecError
import sqlite3
from sre_constants import SUCCESS
import bcrypt

def run_query(query, params=[]):
    """return the result of a query or false in case of an error"""
    db = sqlite3.connect('skilllog.db')
    if len(params) != query.count('?'):
        return False
    else:
        try:
            if params == []:
                result = db.execute(query)
            else:
                result = db.execute(query, params)
            db.commit()
            return result
        except Exception as err:
            print('db error', err)
            return False

def delete_user(id):
    try:
        run_query('DELETE FROM users WHERE id = ?', [id])
        return True
    except:
        return False

def adduser(name, email, password, visibility):
    """return true if sucessfully created the user, otherwise returns false"""
    try:
        hashed = bcrypt.hashpw(password.encode('utf-8'), bcrypt.gensalt(14))
        sucess = run_query('INSERT INTO users (name, email, password, private) VALUES (?, ?, ?, ?)', 
                            [name, email, hashed, visibility == 'private'])
        if sucess == False:
            return False
        return True
    except:
        return False

def verifyuser(email, password):
    try:
        correct_hash = run_query('SELECT password FROM users WHERE email = ?', [email]).fetchall()[0][0]
        if bcrypt.checkpw(password.encode('utf-8'), correct_hash):
            return run_query('SELECT id FROM users WHERE email = ?', [email]).fetchall()[0][0]
        return -1
    except:
        return -1

def nameused(name):
    try:
        search = run_query('SELECT * FROM users WHERE name = ?', [name]).fetchall()
        return len(search) != 0
    except:
        return True

def emailused(email):
    try:
        search = run_query('SELECT * FROM users WHERE email = ?', [email]).fetchall()
        return len(search) != 0
    except:
        return True

def add_activity(title, activity_type, visibility, description, notes, publicnotes, 
                             year, month, day, user_id):
    """True if successfully add or false if occurred an error"""
    try:
        sucess = run_query('INSERT INTO activities (title, type, private, description, notes, private_notes, '+
        'year, month, day, user_id) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)', [title, activity_type, visibility == 'private', 
        description, notes, publicnotes == False, year, month, day, user_id])
        if sucess == False:
            return False
        return True
    except:
        return False
