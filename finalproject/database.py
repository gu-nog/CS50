import sqlite3


def run_query(query, params=[]):
    """return the result of a query or false in case of an error"""
    db = sqlite3.connect('skilllog.db')
    parameters = [params]
    if len(parameters[0]) != query.count('?'):
        return False
    else:
        try:
            if params == []:
                result = db.execute(query)
            else:
                result = db.execute(query, parameters)
            db.commit()
            return result
        except:
            return False
