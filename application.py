from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

#import datetime
from datetime import datetime

# Configure application
app = Flask(__name__)

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    currentUser = db.execute("select * from users where id = :usersId", usersId=session["user_id"])
    if len(currentUser) != 1:
        return apology("db error", 400)
    currentCash = currentUser[0]["cash"]
    mainArray = []
    totalActive = currentCash
    currentID = session["user_id"]
    allSymbols = db.execute(
        "select stock_symbol, sum(quantity) as q from history where user_id = :currentID group by stock_symbol", currentID=currentID)
    for i in allSymbols:
        if int(i['q']) != 0:
            eachSymbolData = lookup(i["stock_symbol"])
            if eachSymbolData != None:
                newArray = []
                newArray.append(eachSymbolData['symbol'])
                newArray.append(eachSymbolData['name'])
                newArray.append(i['q'])
                newArray.append(usd(eachSymbolData['price']))
                newArray.append(usd(i['q'] * eachSymbolData['price']))
                totalActive = totalActive + i['q'] * eachSymbolData['price']
                mainArray.append(newArray)
    return render_template("index.html", symb=mainArray, cash=usd(currentCash), total=usd(totalActive))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")
    else:
        getSymbol = request.form.get("symbol")
        if not getSymbol:
            return apology("missing symbol", 400)
        getShares = request.form.get("shares")
        if not getShares:
            return apology("missing shares", 400)
        if getShares.isalpha():
            return apology("invalid shares. You must enter the integer", 400)
        if "," in getShares:
            return apology("invalid shares. You must enter the whole integer", 400)
        if "." in getShares:
            return apology("invalid shares. You must enter the whole integer", 400)
        if int(getShares) <= 0:
            return apology("you must enter value more than zero", 400)
        getSymbol = getSymbol.upper()
        aboutSymbol = {}
        aboutSymbol = lookup(getSymbol)
        if aboutSymbol == None:
            return apology("invalid symbol", 400)
        # Query database for cash
        currentUser = session["user_id"]
        userBD = db.execute("SELECT * FROM users WHERE id = :idNow", idNow=currentUser)
        if len(userBD) != 1:
            return apology("DB error", 403)
        userCash = userBD[0]['cash']
        priceSymbol = aboutSymbol['price']
        if userCash >= int(getShares) * priceSymbol:
            userCash = userCash - int(getShares) * priceSymbol
            db.execute("insert into history(user_id, stock_symbol, price_symbol, quantity) values (:user_id, :stock_symbol, :price_symbol, :quantity)",
                       user_id=currentUser, stock_symbol=getSymbol, price_symbol=priceSymbol, quantity=getShares)
            db.execute("update users set cash = :userCash where id = :currentUser",
                       userCash=userCash, currentUser=currentUser)
            return redirect("/")
        return apology("can`t afford", 400)


@app.route("/history")
@login_required
def history():
    currentID = session["user_id"]
    currentUser = db.execute("select * from users where id = :usersId", usersId=currentID)
    if len(currentUser) != 1:
        return apology("db error", 400)
    currentCash = currentUser[0]["cash"]
    mainArray = []
    totalActive = currentCash
    allSymbols = db.execute("select * from history where user_id = :currentID", currentID=currentID)
    for i in allSymbols:
        newArray = []
        newArray.append(i['stock_symbol'])
        newArray.append(i['quantity'])
        newArray.append(i['price_symbol'])
        newArray.append(i['date_operation'])
        mainArray.append(newArray)
    return render_template("history.html", row=mainArray)


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

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


@app.route("/changePassword", methods=["GET", "POST"])
@login_required
def changePassword():
    """Allow to user ability change the password"""
    currentuserID = session["user_id"]
    if request.method == "GET":
        return render_template("changePassword.html")
    else:
        getOldPass = request.form.get("oldpassword")
        getNewPass = request.form.get("newpassword")
        getconfirmNewPass = request.form.get("confirmnewPass")
        hash = generate_password_hash(getOldPass)
        hashPassword = db.execute(
            "select hash from users where id =:currentuserID", currentuserID=currentuserID)
        if not check_password_hash(hashPassword[0]["hash"], getOldPass):
            return apology("old password don`t match", 400)
        if getNewPass != getconfirmNewPass:
            return apology("new password don`t match", 400)
        if not getNewPass:
            return apology("must provide new password", 400)
        hash = generate_password_hash(getNewPass)
        db.execute("update users set hash =:hash where id =:currentuserID",
                   currentuserID=currentuserID, hash=hash)

    # Redirect user to home page
    return redirect("/")


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
    if request.method == "GET":
        return render_template("quote.html")
    else:
        getName = request.form.get("symbol")
        if not getName:
            return apology("missing symbol", 400)
        getName = getName.upper()
        quoteFromFu = {}
        quoteFromFu = lookup(getName)
        if quoteFromFu == None:
            return apology("invalid symbol", 400)
        else:
            symbol = quoteFromFu['symbol']
            name = quoteFromFu['name']
            price = quoteFromFu['price']
            return render_template("quoted.html", symbolIn=symbol, nameIn=name, priceIn=usd(price))


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")
    else:
        getName = request.form.get("username")
        getPassword = request.form.get("password")
        getConfirm = request.form.get("confirmation")
        if not getName:
            return apology("must provide username", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=getName)

        # Ensure username exists and password is correct
        if len(rows) >= 1:
            return apology("invalid username. The name already exists", 400)

        if not getPassword:
            return apology("must provide password", 400)

        if not getPassword == getConfirm:
            return apology("passwords don`t match", 400)

        # Insert the name and pass in db
        hash = generate_password_hash(getPassword)

        db.execute("insert into users(username, hash) values (:getNamein, :getPasswordin)",
                   getNamein=getName, getPasswordin=hash)

        # Redirect user to home page
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    currentID = session["user_id"]
    if request.method == "GET":

        # get all avialable symbols stock
        allSymbols = db.execute(
            "SELECT stock_symbol FROM history WHERE user_id = :currentID group by stock_symbol", currentID=currentID)
        symbolArray = []
        for i in allSymbols:
            symbolArray.append(i["stock_symbol"])
        return render_template("sell.html", symb=symbolArray)
    else:
        getSymbol = request.form.get("symbol")
        getQuantity = request.form.get("shares")
        if getSymbol == "Symbol":
            return apology("you must select share to sell", 400)
        if int(getQuantity) <= 0:
            return apology("you must enter value more than zero", 400)

        # get available quantity of shares what the user needs
        availabelSymbol = db.execute(
            "select sum(quantity) FROM history WHERE stock_symbol = :symbol and user_id =:currentID", symbol=getSymbol, currentID=currentID)
        if availabelSymbol == None:
            return apology("you don`t have such symbol stock", 400)
        else:
            if availabelSymbol[0]['sum(quantity)'] < int(getQuantity):
                return apology("you don`t have enough shares", 400)
            else:

                # get all data about Symbol. Need to know current price of symbol shares.
                rowSymbol = lookup(getSymbol)
                priceSymbol = rowSymbol['price']

                # get all data about current user from db. Need to know current cash.
                rowUser = db.execute(
                    "select * from users where id = :currentID", currentID=currentID)

                # look at cash info. In stock now.
                baseCash = rowUser[0]['cash']

                # calculate earnin cash. In stock + quantity * current price of shares
                userCash = baseCash + int(getQuantity) * int(priceSymbol)

                # insert in table history all new info
                db.execute("insert into history(user_id, stock_symbol, price_symbol, quantity) values (:user_id, :stock_symbol, :price_symbol, :quantity)",
                           user_id=currentID, stock_symbol=getSymbol, price_symbol=priceSymbol, quantity=-(int(getQuantity)))
                db.execute("update users set cash = :userCash where id = :currentUser",
                           userCash=userCash, currentUser=currentID)
                return redirect("/")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
