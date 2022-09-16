import re
from flask import Flask, render_template, request, session # flask run
from flask_session import Session

app = Flask(__name__) # this send the name of the file to transform in our flask application

app.config['SESSION_PERMANENT'] = False
app.config['SESSION_TYPE'] = 'filesystem'
Session(app)

COUNTRIES = ['brazil', 'canada', 'EUA']

@app.route('/') # this tell when to call index function(decorator that modifies other function)
def index():
    # name = request.args.get('name') # get query parameter
    if session.get('name'):
        return render_template('logged.html')
    return render_template('index.html', countries=COUNTRIES) #, name=name)

@app.route('/inputted')
def inputted():
    name = request.args.get('name', 'world') # world is a default value if any parameter is passed
    session['name'] = name
    return render_template('inputted.html', name=name)

@app.route('/signup', methods=['POST'])
def signup():
    email = request.form.get('email')
    password = request.form.get('pass')
    country = request.form.get('country')
    if email == '' or email.count('@') == 0 or email.count('.') == 0 or password == '' or country not in COUNTRIES:
        return render_template('error.html')
    else:
        return render_template('sucess.html')
