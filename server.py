import string
from mysql.connector import connect
import flask

app = flask.Flask(__name__)

def run_query(query: string):
    connection = connect(host='localhost', username="root", password="root", database="iot_db")
    cursor = connection.cursor()
    cursor.execute(query)
    result = cursor.fetchall()
    connection.commit()
    cursor.close()
    connection.close()
    return result


@app.route('/', methods=['GET'])
def index():
    return "Hello flask"


@app.route("/temperature", methods=["GET"])
def get_temperature():
    query = "select id, value, created_at from temp_values;"
    result = run_query(query)
    return flask.jsonify(result)

@app.route('/temperature', methods=['POST'])
def add_temperature():
    temperature = flask.request.form.get('temperature')
    query = f'insert into temp_values(value) values ({temperature})'
    result = run_query(query)
    return 'value added'



app.run(port=4000, host='0.0.0.0', debug=True)