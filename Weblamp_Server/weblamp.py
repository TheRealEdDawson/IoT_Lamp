import RPi.GPIO as GPIO
from flask import Flask, render_template, request
app = Flask(__name__)
 
GPIO.setmode(GPIO.BCM)
#GPIO.setmode(GPIO.BOARD)
 
 
# Create a dictionary called pin to store the pin number, name and pin state:
# 24 : {'name' : 'coffee maker', 'state' : GPIO.LOW},
 
pins = {
        23 : {'name' : 'lamp', 'state' : GPIO.LOW}
        }
 
#Set each pin as an outpuit and make it low:
for pin in pins:
        GPIO.setup(pin, GPIO.OUT)
        GPIO.output(pin, GPIO.LOW)
 
@app.route("/")
def main():
        #For each pin, read the pin state and store it in the pins dictionary:
        for pin in pins:
        #       pins[pin]['state'] = GPIO.input(pin)
                print pin
        # Put the pin dictionary into the template data dictionary:
        templateData = {
                'pins' : pins
                }
        # Pass the template data into the tempalte main.html and return it to the user
        return render_template('main.html', **templateData)
       
 
# The function belopw is executed when someone requests a URL with the pin number and action in it:
@app.route("/<changePin>/<action>")
def action(changePin, action):
        # Convert the pin from the URL into an integer:
        changePin = int(changePin)
        GPIO.setup(changePin, GPIO.OUT)
        # Get the device nasme for the pin being changed:
        deviceName = pins[changePin]['name']
        # If the action part of the URL is "on", execute the code indented below:
        if action == "on":
                # Set the pin high:
                GPIO.output(changePin, GPIO.HIGH)
                # Save the status message to be passed into the template:
                message = "Turned " + deviceName + " on."
        if action == "off":
                GPIO.output(changePin, GPIO.LOW)
                message = "Turned " + deviceName + " off."
        if action == "toggle":
                # Read the pin and set it to whatever it isn't, i.e. toggle it
                print "Priting Changepin"
                #print GPIO.gpio_function(changePin)
                #GPIO.output(changePin, not GPIO.input(changePin))
                GPIO.setup(changePin, GPIO.IN)
                tempValue =  GPIO.input(changePin)
                GPIO.setup(changePin, GPIO.OUT)
                GPIO.output(changePin, not tempValue)
                message = "Toggled " + deviceName + "."
 
        # For each pin, read the pin state and store it in the pins dictionary:
        #for pin in pins:
        #       pins[pin]['state'] = GPIO.input(pin)
               
        # Along with the pin dictionary, put the message into the template data dictionary:
        templateData = {
                'message' : message,
                'pins' : pins
                }
 
        return render_template('main.html', **templateData)
 
if __name__ == "__main__":
        app.run(host='0.0.0.0', port=80, debug=True)