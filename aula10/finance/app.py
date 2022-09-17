import os
import re

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db") 
# users with id, username, hash e cash

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required # if no user_id redirect to /login
def index():
    """Show portfolio of stocks"""
    try:
        cash = float(db.execute('SELECT * FROM users WHERE id = ?', session['user_id'])[0]['cash'])
        stocks_money = 0
        stocks = db.execute('SELECT * FROM portifolio WHERE user_id = ?', session['user_id'])
        complete_stocks = []
        for stock in stocks:
            symbol = stock['stock']
            qty = stock['qty']
            more_info = lookup(symbol)
            name = more_info['name']
            price = more_info['price']
            total = price * qty
            stocks_money += total
            if qty > 0:
                complete_stocks.append({"name": name, "symbol": symbol, "shares": qty, "price": usd(price), 'total': usd(total)})
    except:
        return apology('We are having problems on our servers, please comeback later :)', '500')
    return render_template("index.html", cash=usd(cash), total=usd(cash + stocks_money), stocks=complete_stocks)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == 'GET': # form of stock symbol and quantity
        return render_template('buy.html')
    else: # Buy it
        # Verify - enough cash, positive quantity, valid stock
        stock = request.form.get('symbol')
        try:
            qty = int(request.form.get('qty'))
        except:
            return apology('must provide valid quantity')
        if qty <= 0:
            return apology('must buy 1+ stocks')
        stock_info = lookup(stock)
        cash = float(db.execute('SELECT * FROM users WHERE id = ?', session['user_id'])[0]['cash'])
        if stock_info == None:
            return apology('must provide valid symbol')
        if cash < qty * stock_info['price']:
            return apology('must have cash enough')

        # Add in history and portifolio; update cash
        db.execute('UPDATE users SET cash = ? WHERE id = ?', cash - qty * stock_info['price'], session['user_id'])
        today = datetime.date.today()
        month = int(str(today)[5:7])
        day = int(str(today)[-2:])
        db.execute('INSERT INTO history (day, month, stock, qty, total_price, user_id) VALUES (?, ?, ?, ?, ?, ?)', 
                day, month, stock, qty, qty * stock_info['price'], session['user_id'])
        before = db.execute('SELECT * FROM portifolio WHERE stock = ? AND user_id = ?', stock, session['user_id'])
        if len(before) > 0:
            before_qty = before[0]['qty']
            db.execute('UPDATE portifolio SET qty = ? WHERE user_id = ? AND stock = ?', before_qty + qty, session['user_id'], stock)
        else:
            db.execute('INSERT INTO portifolio (stock, qty, user_id) VALUES (?, ?, ?)', stock, qty, session['user_id'])
        return redirect('/buy')


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    try:
        transactions = db.execute('SELECT * FROM history WHERE user_id = ?', session['user_id'])
        all_transactions = []
        for transaction in transactions:
            symbol = transaction['stock']
            qty = int(transaction['qty'])
            total_price = float(transaction['total_price'])
            unit_price = abs(total_price) / abs(qty)
            if qty < 0:
                type = 'sell'
            else:
                type = 'buy'
            all_transactions.append(
                {"type": type, "date": f"{transaction['month']}/{transaction['day']}", "symbol": symbol, "shares": abs(qty), "price": usd(unit_price), 'total': usd(abs(total_price))}
            )
    except:
        return apology('We are having problems on our servers, please comeback later :)', '500')
    return render_template("history.html", transactions=all_transactions)

@app.route('/delete')
@login_required
def delete():
    """Delete user account"""
    user = session['user_id']
    db.execute("DELETE FROM history WHERE user_id = ?", user)
    db.execute("DELETE FROM portifolio WHERE user_id = ?", user)
    db.execute("DELETE FROM users WHERE id = ?", user)
    session.clear()
    return redirect('/')

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect) > interface with form
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # GET - form with stock
    if request.method == 'GET':
        return render_template('quote.html')
    # POST - display stock data
    else:
        stock = request.form.get('symbol')
        if stock == '':
            return apology('must provide stock')
        else:
            stock_info = lookup(stock)
            if stock_info == None:
                return apology('invalid stock symbol or internal server error')
            else:
                stock_info['price'] = usd(stock_info['price'])
                return render_template('quoted.html', stockinfo=stock_info)

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # GET > form to signup
    if request.method == 'GET':
        return render_template('signup.html')

    # POST
    else:
    #   verify if ok(name used, pass don't match, no empth input field) > if not return apology
        name = request.form.get('username')
        password = request.form.get('password')
        verifypassword = request.form.get('verifypassword')
        if password == '':
            return apology('must provide password')
        elif verifypassword == '':
            return apology('you must provide an verify password, so we will can verify if you typed it correctly')
        elif not password == verifypassword:
            return apology('password and verify password must match')
        elif name == '':
            return apology('must provide username')
        elif len(list(db.execute('SELECT * FROM users WHERE username = ?', name))) != 0:
            return apology('username already been used')
        else:
        #   insert user and login
            db.execute('INSERT INTO users (username, hash) VALUES (?, ?)', name, generate_password_hash(password))
            rows = db.execute('SELECT * from users WHERE username = ?', name)
            session["user_id"] = rows[0]["id"]
            return redirect('/')


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == 'GET': # form of stock symbol and quantity
        return render_template('sell.html')
    else: # Buy it
        # Verify - enough stocks, positive quantity, valid stock
        stock = request.form.get('symbol')
        try:
            qty = int(request.form.get('qty'))
        except:
            return apology('must provide valid quantity')
        if qty <= 0:
            return apology('must sell 1+ stocks')
        stock_info = lookup(stock)
        before_shares = int(db.execute('SELECT * FROM portifolio WHERE user_id = ? AND stock = ?', session['user_id'], stock)[0]['qty'])
        if stock_info == None:
            return apology('must provide valid symbol')
        if before_shares < qty:
            return apology('must have shares enough')

        # Add in history and portifolio; update qty
        sold_value = qty * stock_info['price']
        cash = float(db.execute('SELECT * FROM users WHERE id = ?', session['user_id'])[0]['cash'])
        db.execute('UPDATE users SET cash = ? WHERE id = ?', cash + sold_value, session['user_id'])
        db.execute('UPDATE portifolio SET qty = ? WHERE user_id = ? AND stock = ?', before_shares - qty, session['user_id'], stock)
        today = datetime.date.today()
        month = int(str(today)[5:7])
        day = int(str(today)[-2:])
        db.execute('INSERT INTO history (day, month, stock, qty, total_price, user_id) VALUES (?, ?, ?, ?, ?, ?)', 
                day, month, stock, qty * -1, sold_value * -1, session['user_id'])
        return redirect('/sell')
