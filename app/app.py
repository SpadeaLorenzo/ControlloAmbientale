# The imports where listed even in requirements.txt
from flask import Flask, render_template, redirect, url_for, request,session
from flask_mysqldb import MySQL
from flask_bcrypt import Bcrypt
from mysql.connector import (connection)
import logging
import json
import mysql.connector
from datetime import date, datetime, timedelta
from graphs import *
import sys

# -----------------------------------------------------------
# This app, is the main file of our project, it contains every
# route to offer each service.
# service.
# It has the connection to the database and functions for graphs.
#
#
# (C)
# -----------------------------------------------------------

# Setting up our Flask Application, with secret key,
# and Bcrypt class.
app = Flask(__name__)
app.secret_key = "lachiavepiusegretadelmondo"
bcrypt = Bcrypt(app)

# Setting up the logging function
logging.basicConfig(datefmt='%Y-%m-%d %H:%M:%S', format='[%(asctime)s][%(levelname)s] %(message)s', level=logging.DEBUG, stream=sys.stdout)

# -----------------------------------------------------------
# The following functions are helper functions we created
# to not write duplicate code.
# -----------------------------------------------------------

# This function returns a connection to the database.
def get_connection():
  try:
    cnx = mysql.connector.connect(user='ControlloAmbient',password='apYv#C-wg*b7gn6f',host='ControlloAmbientale.mysql.pythonanywhere-services.com',database='ControlloAmbient$ca')
    logging.debug('connection established')
    return cnx
  except mysql.connector.Error as err:
    logging.exception('error during db connection' , msg=err)


#Function to check if a username already is in use in out database User table.
def user_exists(username):
    try:
        cnx = get_connection()
        cur = cnx.cursor(dictionary=True)
        cur.execute("SELECT username FROM user")
        for row in cur:
            if(username == row["username"]):
                return True
        cur.close()
        cnx.close()
    except Exception as e:
        logging.exception(e)
    return False

# Functions to check if a fishino name is already in use in out database Fishino table.
def fishino_exists(name):
    try:
        cnx = get_connection()
        cur = cnx.cursor(dictionary=True)
        cur.execute("SELECT name FROM fishino")
        for row in cur:
            if(name == row["name"]):
                return True
        cur.close()
        cnx.close()
    except Exception as e:
        logging.exception(e)
    return False


# Function that given specific parameters, defines the accept range
# for a specific value passed.
#
# @param data_type is the data type to check.
def get_status(data_type):
    cnx = get_connection()
    cursor = cnx.cursor(dictionary=True)
    query = ("SELECT ROUND(AVG({})) as {} FROM data WHERE data > now() - INTERVAL 10 MINUTE").format(data_type, data_type)
    cursor.execute(query)
    value = cursor.fetchone()
    cursor.close()
    cnx.close()
    value = value[data_type]

    if data_type == "humidity":
        if value >= 20 and value <= 60:
            return "status-div-normal"
    elif data_type == "temperature":
        if value >= 15 and value <= 30:
            return "status-div-normal"
    elif data_type == "noise":
        if value <= 80:
            return "status-div-normal"
    elif data_type == "co2":
        if value < 550:
            return "status-div-normal"
    elif data_type == "brightness":
        if value <= 800:
            return "status-div-normal"
    return "status-div-allert"

# This function reurns the data to create the graphs,
#
# @param data_type the type to select, co2, brightness, noise, humidity, temperature
# @param fishino the name of wich fishino we want to query
# @param option
# 1 -> Today
# 2 -> Last Week
# 3 -> Last Month
# 4 -> Last Year
#
# @returns the merge of the labels and data, the lables are Datetime variables,
# to indicate when fisino collected data. And the data of a certain value.

def get_data(data_type,fishino,option):
    cnx = get_connection()
    cursor = cnx.cursor(dictionary=True)
    query = ""
    if option == 1:
        query = ("SELECT data,{} FROM data where DATE(data)=CURDATE() AND fishino_name='{}'").format(data_type,fishino)
    elif option == 2:
        query =  ("SELECT DATE(data) as data, ROUND(AVG({})) as {} FROM data WHERE data > now() - INTERVAL 1 WEEK  AND fishino_name='{}' GROUP BY DATE(data)").format(data_type,data_type,fishino)
    elif option == 3:
        query =  ("SELECT DATE(data) as data, ROUND(AVG({})) as {} FROM data WHERE data > now() - INTERVAL 1 MONTH AND fishino_name='{}' GROUP BY DATE(data)").format(data_type,data_type,fishino)
    elif option == 4:
        query = ("SELECT DATE_FORMAT(`data`, '%Y-%m') as data, ROUND(AVG({})) as {} FROM data WHERE fishino_name='{}' GROUP BY DATE_FORMAT(`data`, '%Y-%m') ORDER BY data DESC LIMIT 12").format(data_type,data_type,fishino)
    elif option == 5:
        query = ("SELECT DATE(data) as data, ROUND(AVG({})) as {} FROM data WHERE data > now() - INTERVAL 10 MINUTE").format(data_type, data_type)


    cursor.execute(query)
    output = cursor.fetchall()

    labels = []
    dati = []

    for row in output:
      labels.append(row['data'])
      dati.append(row[data_type])

    merge = [dati,labels]
    cursor.close()
    cnx.close()
    return merge


#This function returns the position of a fishino.
def get_fishino_position(fishino):
  try:
    cnx = get_connection()
    cursor = cnx.cursor(dictionary=True)
    query = ("SELECT position FROM fishino WHERE name='{}'").format(fishino)
    cursor.execute(query)
    position = cursor.fetchall()
    position = (position[0]['position'])
    return position
  except Exception as e:
    logging.exception(e)


# This function converts the int option number to his string value.
def get_time_string(value):
    if value == 1 :
        return "today"
    elif value == 2:
        return "last week"
    elif value == 3:
        return "last month"
    else:
        return "last year"


#Function to insert the received data from the fishino to our database.
def insert_data(n , h , b , no , c , t):
    try:
      cnx = get_connection()
      cursor = cnx.cursor()
      now = datetime.now()
      statement = """INSERT INTO data(data, fishino_name, humidity, brightness, noise,co2 ,temperature) VALUES (%s,%s,%s,%s,%s,%s,%s)"""
      val = (now, n ,h , b, no, c , t )
      cursor.execute(statement, val)
      cursor.close()
      cnx.commit()
      cnx.close()
    except Exception as e:
      logging.exception(e)


#This function checks if the fishino exists
def is_fishino(fishino_name):
  try:
    exist = False
    cnx = get_connection()
    cursor = cnx.cursor(dictionary=True)
    cursor.execute("SELECT name FROM fishino")
    for row in cursor:
      if(fishino_name == row["name"]):
          exist = True
    cursor.close()
    cnx.close()
  except Exception as e:
    logging.exception(e)
  return exist


# -----------------------------------------------------------
# Those are the routes, we needed to create to offer all services.
# To Login, Logout, Add a new Device, Add a new user,
# delete devices ecc...
# -----------------------------------------------------------

# This is the index route, it shows if the average of each fishino is OK,
# a green box means OK, a red box means ALLERT value.
@app.route("/")
def index():
    return render_template('index.html',co2=get_status("co2"), temp=get_status("temperature"), hum=get_status("humidity"), noise=get_status("noise"),bright=get_status("brightness"))



# Route we need to login.
@app.route("/login", methods=["GET","POST"])
def login():
  if request.method == "POST":
    uname = request.form['username']
    password = request.form['pwd']
    data = None
    try:
        if len(uname.strip()):
            cnx = get_connection()
            cur = cnx.cursor(prepared=True)
            statement = """SELECT * FROM user WHERE username=%s"""
            params = (uname,)
            cur.execute(statement , params)
            data = cur.fetchone()
        else:
            return redirect(url_for('login'))
    except Exception as e:
        logging.exception(f'error logging in with: user: {uname} pass: {password} hash: {hash_password}')

    if data:
        user, pwd = data
        pwd = bytes(pwd).decode("utf-8")
        if bcrypt.check_password_hash(pwd,password):
          session["login"] = True
          session["username"] = uname
          return redirect(url_for('index'))
        else:
            return render_template("login.html",msg="Wrong password")
    else:
        return redirect("login.html",msg="Username does not exists")
  else:
    return render_template("login.html")




# Route to display every fishino we collect data from.
@app.route("/fishino")
def fishino():
    fishinos = []
    try:
      cnx = get_connection()
      cursor = cnx.cursor(dictionary=True)
      cursor.execute("SELECT * FROM fishino")

      for row in cursor:
        print(row)
        fishinos.append(row)
      logging.debug(f'fishino records: {fishinos}')

      cursor.close()
      cnx.close()
    except Exception as e:
      logging.exception(e)

    return render_template('fishino.html', fishino=fishinos)


# From this route we collect the data, sent by the fishino.
@app.route("/fishino/data" , methods=['POST'])
def get_insert_data():
    if request.method == 'POST':
        content_type = request.headers.get('Content-Type')
        if(content_type == 'application/json'):
            json = request.json
            name = json["name"]
            if(is_fishino(name)):
                humidity = json["humidity"]
                brigthness = json["brightness"]
                noise = json["noise"]
                co2 = json["co2"]
                temperature = json["temperature"]
                insert_data(name , humidity , brigthness , noise , co2 , temperature)
            else:
                print(f"fishino name '{name}' does not exist")
        else:
            print('invalid content type')
    else:
        print('Invalid Method request')
    return "200"


# Route to load a page to display single details about the collected data of a fishino.
# /<fishino> is the parameter to define wich fishino we want to query.
@app.route("/fishino/<fishino>", methods=["GET", "POST"])
def get_datas_from_fishino(fishino):
    try:
      option = 1
      if request.method == 'POST':
        if (request.form['time'] == "week"):
          option = 2
        elif (request.form['time'] == "month"):
          option = 3
        elif (request.form['time'] == "year"):
          option = 4
      print(option)
      dataco2 = get_data("co2",fishino,option)
      datahum = get_data("humidity",fishino,option)
      databright = get_data("brightness",fishino,option)
      datanoise = get_data("noise",fishino,option)
      datatemp = get_data("temperature",fishino,option)
      return render_template("graphics.html",
        graph_data_1=create_graph(fishino,get_fishino_position(fishino),"co2",dataco2[0],dataco2[1],get_time_string(option)),
        graph_data_2=create_graph(fishino,get_fishino_position(fishino),"humidity",datahum[0],datahum[1],get_time_string(option)),
        graph_data_3=create_graph(fishino,get_fishino_position(fishino),"brightness",databright[0],databright[1],get_time_string(option)),
        graph_data_4=create_graph(fishino,get_fishino_position(fishino),"noise",datanoise[0],datanoise[1],get_time_string(option)),
        graph_data_5=create_graph(fishino,get_fishino_position(fishino),"temperature",datatemp[0],datatemp[1],get_time_string(option)))
    except Exception as e:
      logging.exception(e)
    return render_template("fishino.html")


# This Route was created to delete a selected fishino.
@app.route("/fishino/delete/<fishino>", methods=["GET", "POST"])
def delete_from_fishino(fishino):
    if session["login"] == True:
        cnx =  get_connection()
        cur =  cnx.cursor()
        delete = (f"DELETE FROM data WHERE fishino_name='{fishino}'")
        delete2 = (f"DELETE FROM fishino WHERE name='{fishino}'")
        if fishino_exists(fishino):
            cur.execute(delete)
            cur.execute(delete2)
            cur.close()
            cnx.commit()
            cnx.close()
            return redirect(url_for('fishino'))
        else:
            return redirect(url_for('fishino'))
    else:
        return redirect(url_for('fishino'))



# Route to add a user to our database.
@app.route('/add_user', methods=['POST', 'GET'])
def add_user():
    if session["login"] == True:
        if request.method == 'POST':
            uname = request.form['username']
            pwd =  request.form['password']
            if user_exists(uname) or len(uname.strip()) == 0:
                return render_template("add_user.html" , msg="User already exists or name is invalid")
            else:
                hash_pwd = bcrypt.generate_password_hash(pwd).decode('utf-8')
                cnx =  get_connection()
                cur =  cnx.cursor()
                statement = """INSERT INTO user(username , pwd) VALUES (%s,%s)"""
                val = (uname , hash_pwd)
                cur.execute(statement, val)
                cur.close()
                cnx.commit()
                cnx.close()
                return render_template("add_user.html" , msg="User added succesfully")
        else:
            return render_template("add_user.html")
    else:
      return render_template("index.html")


#Route to add a new fishino device to our database.
@app.route('/add_fishino', methods=['POST', 'GET'])
def add_fishino():
    if session["login"] == True:
        if request.method == 'POST':
            name = request.form['name']
            position =  request.form['position']
            cnx =  get_connection()
            cur =  cnx.cursor()
            statement = """INSERT INTO fishino(name , position) VALUES (%s,%s)"""
            val = (name , position)
            if fishino_exists(name) or len(name.strip()) == 0:
                return render_template("add_fishino.html" , msg="Fishino already exists or name is invalid")
            else:
                cur.execute(statement, val)
                cur.close()
                cnx.commit()
                cnx.close()
                return render_template("add_fishino.html" , msg="Fishino added succesfully")
        else:
            return render_template("add_fishino.html")
    else:
      return render_template("index.html")

#Finally, our Route to log out from our User.
@app.route('/logout')
def logout():
  session.clear()
  return redirect(url_for('index'))


if __name__ == '__main__':
    app.debug = True