import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    # Selecting the following symbol, shares, price and user id from the transactions database table
    transactions_db = db.execute(
        "SELECT symbol, name, price, SUM(shares) as totalShares FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)

    # selecting cash from user from the user table in database.
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    # Adding cash to variable total
    total = cash

    # Calculating total value of shares
    for trans in transactions_db:
        total += trans["price"] * trans["totalShares"]

    # Rendering index template with transactions, cash , usd def , total value
    return render_template("index.html", database=transactions_db, cash=cash, usd=usd, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # Setting method tp post
    if request.method == "POST":

        # requesting symbol and putting it in upper case
        symbol = request.form.get("symbol").upper()

        # Looking up symbol throu lookup function
        item = lookup(symbol)

        # if the symbol is not filled in we return the apology function
        if not symbol:
            return apology("Please enter a symbol!")

        # if the symbol does not excist we return apology function
        elif not item:
            return apology("Invalid symbol!")

        # we try to get back shares amount in integer form
        try:
            shares = int(request.form.get("shares"))

        # if shares is not an integer we return apology function
        except:
            return apology("Shares must be an integer!")

        # if the shares are 0 or lower we return an apology funcation
        if shares <= 0:
            return apology("Shares must be an positive interger!")

        # Requesting user id information from database
        user_id = session["user_id"]

        # requesting the cash from user from the database
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        # requesting the name and price of the shares
        item_name = item["name"]
        item_price = item["price"]

        # Calculating the item price with amount of shares for total
        total_price = item_price * shares

        # Checking if user has enough funds and if not we return an apology function
        if cash < total_price:
            return apology("Not enough cash!")
        else:

            # we calculate the total price of stock and subtracked it from cash
            db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - total_price, user_id)

            # we update the database with the new values
            db.execute("INSERT INTO transactions (user_id, name, shares, price, type, symbol) VALUES (?, ?, ?, ?, ?, ?)",
                       user_id, item_name, shares, item_price, "buy", symbol)

        # Shows message that shares have been bought
        flash("Bought Shares!")

        # After the user will be redirected to the homepage aka portfolio or index
        return redirect("/")

    # else we return the buy html page
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Shows history of transactions"""

    # Requesting user id from database
    user_id = session["user_id"]

    # Requesting the other items in database transactions
    transactions_db = db.execute("SELECT * FROM transactions WHERE user_id = ?", user_id)

    # Returning the information collected back to the html page history
    return render_template("history.html", transactions=transactions_db, usd=usd)


@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    """User can add money"""
    if request.method == "GET":
        return render_template("add.html")

    else:

        # Making new variable to store cash for calculations later
        new_cash = float(request.form.get("new_cash"))

        # Checking if an amount has been filled in other wise we return an apology function
        if not new_cash:
            return apology("Please fill in amount to add")

        # Checking to make sure what is filled in is not an negative number
        if new_cash <= 0:
            return apology("Please add positive amount")
        # retrieving user id from database
        user_id = session["user_id"]
        # Retrieving your wallet amount from database
        user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_db[0]["cash"]

        # Adding new amount of money to your wallet
        update_cash = float(user_cash) + float(new_cash)

        # Updating databasse with new amount added
        db.execute("UPDATE users SET cash = ? WHERE id = ?", update_cash, user_id)

        # shows Message that cash has been added to your account
        flash("Cash added")

        # being redirected back to the index page
        return redirect("/")


@app.route("/withdraw_cash", methods=["GET", "POST"])
@login_required
def withdraw_cash():
    """User can withdraw money"""
    if request.method == "GET":
        return render_template("remove.html")

    else:

        # Making new variable to store cash for calculations later
        new_cash = float(request.form.get("new_cash"))

        # Checking if an amount has been filled in otherwise we return an apology function
        if not new_cash:
            return apology("Please fill in amount to withdraw")

         # Checking to make sure what is filled in is not an negative number
        if new_cash <= 0:
            return apology("Please fill im positive amount")
        # retrieving user id from database
        user_id = session["user_id"]
        # Retrieving your wallet amount from database
        user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_db[0]["cash"]

        # subtracking new amount of money from your wallet
        update_cash = float(user_cash) - float(new_cash)

        # Updating databasse with new amount
        db.execute("UPDATE users SET cash = ? WHERE id = ?", update_cash, user_id)

        # shows message that cash has been withdrawn from users account
        flash("Cash withdrawn")

        # redirecting back to the index page
        return redirect("/")


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

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Shows message that user has been logged out
    flash("You have been logged out")

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")

    else:

        # Asking user to enter an symbol
        symbol = request.form.get("symbol")

        # Checking if there is an symbol has been filled in. and if not return an apology functcion
        if not symbol:
            return apology("Must fill in Symbol")

        # Looking up if stock symbol excists
        stock = lookup(symbol.upper())

        # Checking if symbol excists and if not an apology fuction will be called
        if stock == None:
            return apology("Symbol Does Not Exist")

        # rendering values to quoted html page
        return render_template("quoted.html", name=stock["name"], price=stock["price"], symbol=stock["symbol"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    else:
        # getting username, password and confirmation password
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Checking if the username is filled in other wise return apology
        if not username:
            return apology("Must fill in a Username")

        # Checking if the password is filled in other wise return apology
        if not password:
            return apology("Must fill in a Password")

        # Checking if the confirmation password is filled in other wise return apology
        if not confirmation:
            return apology("Must fill in a Comfirmation Password")

        # Checking if password and confirmation password match. if not send apology
        if password != confirmation:
            return apology("Password does not match")

        # Generating hash for password before storing
        hash = generate_password_hash(password)

        try:
            # Insert  username and hashed password into the database
            new_user = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
        except:
            # Checking if username already excists. if so return apology
            return apology("Username already excists")
        # so it remembers user
        session["user_id"] = new_user

        # shows message that the user has been registraited
        flash("You have successfully registered!")

        # Redirecting to main page
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Setting method
    if request.method == "POST":

        # Requesting user id from database
        user_id = session["user_id"]

        # Requesting symbol from user
        symbol = request.form.get("symbol")

        # Requesting shares from user
        shares = int(request.form.get("shares"))

        # Checking filled in amount is not an negative number and if so returning an apology function
        if shares <= 0:
            return apology("Shares mest be a positive number!")

        # looking up symbol price and name of symbol
        item_price = lookup(symbol)["price"]
        item_name = lookup(symbol)["name"]

        # Calculating price of amount of shares bought
        price = shares * item_price

        # Getting information about shares user owns from database
        shares_owned = db.execute("SELECT SUM(shares) FROM transactions WHERE user_id = ? AND symbol = ?",
                                  user_id, symbol)[0]["SUM(shares)"]

        # Checking that the user has enough shares to sell and if not return an apology fumction
        if shares_owned < shares:
            return apology("You don`t have enough shares")

        # Requesting current cash owned by user
        current_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        # Updating calculated cash to the database users
        db.execute("UPDATE users SET cash = ? WHERE id = ?", current_cash + price, user_id)

        # inserting new values to database transactions
        db.execute("INSERT INTO transactions (user_id, name, shares, price, type, symbol) VALUES (?, ?, ?, ?, ?, ?)",
                   user_id, item_name, -shares, item_price, "sell", symbol)

        # shows message that shares have been sold
        flash("Sold Shares!")

        # redirecting to index page
        return redirect("/")
    else:

        # Requesting user id from database
        user_id = session["user_id"]

        # Requesting symbols for user from databasetransactions
        symbols = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)

        # Returning values to sell page
        return render_template("sell.html", symbols=symbols)