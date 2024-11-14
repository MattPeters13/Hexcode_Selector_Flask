from flask import Flask, render_template, request, jsonify
# import requests

app = Flask(__name__)

# Endpoint of the C++ web server (Chagnge IP to ip the device gets from DHCP if taking the arduino it to a new network)
# cpp_server_url = "http://192.168.1.10:5000/color" 

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/send_color', methods=['POST'])
def send_color():
    color_hex = request.form.get('color_hex')
    print(color_hex)
    return render_template('index.html')
    # if color_hex:
    #     try:
    #         # Send the color hex code to the C++ server
    #         response = requests.post(cpp_server_url, json={"color_hex": color_hex})
    #         return jsonify({"status": response.status_code, "message": response.text})
    #     except Exception as e:
    #         return jsonify({"status": "error", "message": str(e)})
    # else:
    #     return jsonify({"status": "error", "message": "No color selected"})

if __name__ == '__main__':
    app.run(debug=True)
