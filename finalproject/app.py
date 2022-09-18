from flask import Flask, render_template
from database import run_query

app = Flask(__name__)

@app.route('/')
def index():
    result = run_query('.schema')
    return render_template('index.html', content=result)
