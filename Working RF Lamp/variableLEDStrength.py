import RPi.GPIO as GPIO
import os
from flask import Flask, render_template, request
app = Flask(__name__)


@app.route("/")
def main():
	#For each pin, read the pin state and store it in the pins dictionary:
	templateData = {
		'name' : 'greenled',
		'strength' : 0
		}
	# Pass the template data into the tempalte main.html and return it to the user
	return render_template('variableMain.html', **templateData)
	

@app.route('/3/<pwmValue>')
def setLEDStrength(pwmValue):
	# send the pwmValue variable to the C++ code to send to the arduino/s

	os.system("sudo /home/pi/iot_lamp/rf24libs/RF24/scripts/setLEDValue " + pwmValue);
	print pwmValue

	templateData = {
		'name' : 'green led',
		'strength' : pwmValue
		}

	return render_template('variableMain.html', **templateData)


if __name__ == "__main__":
	app.run(host='0.0.0.0', port=333, debug=True)

