/* OLED PINS:
D3 -> SDA
D5 -> SCL
*/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "SSD1306.h"


int pin1 = D1;
int pin2 = D2;

int onFlag = 0;

int reading = 0;

const char *ssid     = "www.amalshajan.me";
const char *password = "amalshajan.me";

ESP8266WebServer server(80);

SSD1306  display(0x3c, D3, D5);


void handleRoot() {
	server.send(200, "text/html",
		"<!DOCTYPE html>\n"
		"<html>\n"
		"\t<head>\n"
		"\t\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> \n"
		"\t\t<title>REMS | Real-time-Electricity-Monitoring-System</title>\n"
		"\t\t<style>\n"
		"\t\t\tbody{\n"
		"\t\t\t\tbackground: rgb(39, 55, 70);\n"
		"\t\t\t\tfont-family: helvetica;\n"
		"\t\t\t\tfont-weight: 400;\n"
		"\t\t\t\tfont-size: 15px;\n"
		"\t\t\t\tcolor: #333;\n"
		"\t\t\t\t-webkit-font-smoothing: antialiased;\n"
		"\t\t\t\toverflow-y: scroll;\n"
		"\t\t\t\toverflow-x: hidden;\n"
		"\t\t\t}\n"
		"\t\t\ta{\n"
		"\t\t\t\tcolor: #555;\n"
		"\t\t\t\ttext-decoration: none;\n"
		"\t\t\t}\n"
		"\t\t\t.container{\n"
		"\t\t\t\twidth: 100%;\n"
		"\t\t\t\tposition: relative;\n"
		"\t\t\t}\n"
		"\t\t\t.clr{\n"
		"\t\t\t\tclear: both;\n"
		"\t\t\t\tpadding: 0;\n"
		"\t\t\t\theight: 0;\n"
		"\t\t\t\tmargin: 0;\n"
		"\t\t\t}\n"
		"\t\t\t.main{\n"
		"\t\t\t\twidth: 90%;\n"
		"\t\t\t\tmargin: 0 auto;\n"
		"\t\t\t\tposition: relative;\n"
		"\t\t\t}\n"
		"\t\t\t.container > header{\n"
		"\t\t\t\tmargin: 10px;\n"
		"\t\t\t\tpadding: 20px 10px 10px 10px;\n"
		"\t\t\t\tposition: relative;\n"
		"\t\t\t\tdisplay: block;\n"
		"\t\t\t\ttext-align: center;\n"
		"\t\t\t}\n"
		"\t\t\t.container > header h1{\n"
		"\t\t\t\tfont-size: 36px;\n"
		"\t\t\t\tline-height: 36px;\n"
		"\t\t\t\tmargin: 0;\n"
		"\t\t\t\tposition: relative;\n"
		"\t\t\t\tfont-weight: 300;\n"
		"\t\t\t\tcolor: rgb(255, 255, 255);\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.switch {\n"
		"\t\t\t\tmargin: 50px auto;\n"
		"\t\t\t\tposition: relative;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.switch label {\n"
		"\t\t\t\twidth: 100%;\n"
		"\t\t\t\theight: 100%;\n"
		"\t\t\t\tposition: relative;\n"
		"\t\t\t\tdisplay: block;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.switch input {\n"
		"\t\t\t\ttop: 0; \n"
		"\t\t\t\tright: 0; \n"
		"\t\t\t\tbottom: 0; \n"
		"\t\t\t\tleft: 0;\n"
		"\t\t\t\topacity: 0;\n"
		"\t\t\t\tz-index: 100;\n"
		"\t\t\t\tposition: absolute;\n"
		"\t\t\t\twidth: 100%;\n"
		"\t\t\t\theight: 100%;\n"
		"\t\t\t\tcursor: pointer;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.switch.btn-oval {\n"
		"\t\t\t\twidth: 180px;\n"
		"\t\t\t\theight: 50px;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.switch.btn-oval label {\n"
		"\t\t\t\tdisplay: block;\n"
		"\t\t\t\twidth: 100%;\n"
		"\t\t\t\theight: 100%;\n"
		"\t\t\t\tbackground: #a5a39d;\n"
		"\t\t\t\tborder-radius: 40px;\n"
		"\t\t\t\tbox-shadow:\n"
		"\t\t\t\t\t\tinset 0 3px 8px 1px rgba(0,0,0,0.2),\n"
		"\t\t\t\t\t\t0 1px 0 rgba(255,255,255,0.5);\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.switch.btn-oval label:after {\n"
		"\t\t\t\tcontent: \"\";\n"
		"\t\t\t\tposition: absolute;\n"
		"\t\t\t\tz-index: -1;\n"
		"\t\t\t\ttop: -8px; right: -8px; bottom: -8px; left: -8px;\n"
		"\t\t\t\tborder-radius: inherit;\n"
		"\t\t\t\tbackground: #ababab;\n"
		"\t\t\t\tbackground: -moz-linear-gradient(#f2f2f2, #ababab);\n"
		"\t\t\t\tbackground: -ms-linear-gradient(#f2f2f2, #ababab);\n"
		"\t\t\t\tbackground: -o-linear-gradient(#f2f2f2, #ababab);\n"
		"\t\t\t\tbackground: -webkit-gradient(linear, 0 0, 0 100%, from(#f2f2f2), to(#ababab));\n"
		"\t\t\t\tbackground: -webkit-linear-gradient(#f2f2f2, #ababab);\n"
		"\t\t\t\tbackground: linear-gradient(#f2f2f2, #ababab);\n"
		"\t\t\t\tbox-shadow: 0 0 10px rgba(0,0,0,0.3),\n"
		"\t\t\t\t\t\t\t0 1px 1px rgba(0,0,0,0.25);\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.switch.btn-oval label:before {\n"
		"\t\t\t\tcontent: \"\";\n"
		"\t\t\t\tposition: absolute;\n"
		"\t\t\t\tz-index: -1;\n"
		"\t\t\t\ttop: -18px; right: -18px; bottom: -18px; left: -18px;\n"
		"\t\t\t\tborder-radius: inherit;\n"
		"\t\t\t\tbackground: #eee;\n"
		"\t\t\t\tbackground: -moz-linear-gradient(#e5e7e6, #eee);\n"
		"\t\t\t\tbackground: -ms-linear-gradient(#e5e7e6, #eee);\n"
		"\t\t\t\tbackground: -o-linear-gradient(#e5e7e6, #eee);\n"
		"\t\t\t\tbackground: -webkit-gradient(linear, 0 0, 0 100%, from(#e5e7e6), to(#eee));\n"
		"\t\t\t\tbackground: -webkit-linear-gradient(#e5e7e6, #eee);\n"
		"\t\t\t\tbackground: linear-gradient(#e5e7e6, #eee);\n"
		"\t\t\t\tbox-shadow:\n"
		"\t\t\t\t\t\t0 1px 0 rgba(255,255,255,0.5);\n"
		"\t\t\t\t-webkit-filter: blur(1px);\n"
		"\t\t\t\t-moz-filter: blur(1px);\n"
		"\t\t\t\t-ms-filter: blur(1px);\n"
		"\t\t\t\t-o-filter: blur(1px);\n"
		"\t\t\t\tfilter: blur(1px);\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.switch.btn-oval label i {\n"
		"\t\t\t\tdisplay: block;\n"
		"\t\t\t\theight: 100%;\n"
		"\t\t\t\twidth: 60%;\n"
		"\t\t\t\tborder-radius: inherit;\n"
		"\t\t\t\tbackground: silver;\n"
		"\t\t\t\tposition: absolute;\n"
		"\t\t\t\tz-index: 2;\n"
		"\t\t\t\tright: 40%;\n"
		"\t\t\t\ttop: 0;\n"
		"\t\t\t\tbackground: #b2ac9e;\n"
		"\t\t\t\tbackground: -moz-linear-gradient(#f7f2f6, #b2ac9e);\n"
		"\t\t\t\tbackground: -ms-linear-gradient(#f7f2f6, #b2ac9e);\n"
		"\t\t\t\tbackground: -o-linear-gradient(#f7f2f6, #b2ac9e);\n"
		"\t\t\t\tbackground: -webkit-gradient(linear, 0 0, 0 100%, from(#f7f2f6), to(#b2ac9e));\n"
		"\t\t\t\tbackground: -webkit-linear-gradient(#f7f2f6, #b2ac9e);\n"
		"\t\t\t\tbackground: linear-gradient(#f7f2f6, #b2ac9e);\n"
		"\t\t\t\tbox-shadow:\n"
		"\t\t\t\t\t\tinset 0 1px 0 white,\n"
		"\t\t\t\t\t\t0 0 8px rgba(0,0,0,0.3),\n"
		"\t\t\t\t\t\t0 5px 5px rgba(0,0,0,0.2);\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.switch.btn-oval label i:after {\n"
		"\t\t\t\tcontent: \"\";\n"
		"\t\t\t\tposition: absolute;\n"
		"\t\t\t\tleft: 15%;\n"
		"\t\t\t\ttop: 25%;\n"
		"\t\t\t\twidth: 70%;\n"
		"\t\t\t\theight: 50%;\n"
		"\t\t\t\tbackground: #d2cbc3;\n"
		"\t\t\t\tbackground: -moz-linear-gradient(#cbc7bc, #d2cbc3);\n"
		"\t\t\t\tbackground: -ms-linear-gradient(#cbc7bc, #d2cbc3);\n"
		"\t\t\t\tbackground: -o-linear-gradient(#cbc7bc, #d2cbc3);\n"
		"\t\t\t\tbackground: -webkit-gradient(linear, 0 0, 0 100%, from(#cbc7bc), to(#d2cbc3));\n"
		"\t\t\t\tbackground: -webkit-linear-gradient(#cbc7bc, #d2cbc3);\n"
		"\t\t\t\tbackground: linear-gradient(#cbc7bc, #d2cbc3);\n"
		"\t\t\t\tborder-radius: inherit;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.switch.btn-oval label i:before {\n"
		"\t\t\t\tcontent: \"off\";\n"
		"\t\t\t\ttext-transform: uppercase;\n"
		"\t\t\t\tfont-style: normal;\n"
		"\t\t\t\tfont-weight: bold;\n"
		"\t\t\t\tcolor: rgba(0,0,0,0.4);\n"
		"\t\t\t\ttext-shadow: 0 1px 0 #bcb8ae, 0 -1px 0 #97958e;\n"
		"\t\t\t\tfont-family: Helvetica, Arial, sans-serif;\n"
		"\t\t\t\tfont-size: 24px;\n"
		"\t\t\t\tposition: absolute;\n"
		"\t\t\t\ttop: 50%;\n"
		"\t\t\t\tmargin-top: -12px;\n"
		"\t\t\t\tright: -50%;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.switch.btn-oval input:checked ~ label {\n"
		"\t\t\t\tbackground: #9abb82;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.switch.btn-oval input:checked ~ label i {\n"
		"\t\t\t\tright: -1%;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.switch.btn-oval input:checked ~ label i:before {\n"
		"\t\t\t\tcontent: \"on\";\n"
		"\t\t\t\tright: 115%;\n"
		"\t\t\t\tcolor: #82a06a;\n"
		"\t\t\t\ttext-shadow: \n"
		"\t\t\t\t\t0 1px 0 #afcb9b,\n"
		"\t\t\t\t\t0 -1px 0 #6b8659;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\tiv.table-title {\n"
		"\t\t\t\tdisplay: block;\n"
		"\t\t\t\tmargin: auto;\n"
		"\t\t\t\tmax-width: 600px;\n"
		"\t\t\t\tpadding:5px;\n"
		"\t\t\t\twidth: 100%;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.table-title h3 {\n"
		"\t\t\t\tcolor: #fafafa;\n"
		"\t\t\t\tfont-size: 30px;\n"
		"\t\t\t\tfont-weight: 400;\n"
		"\t\t\t\tfont-style:normal;\n"
		"\t\t\t\tfont-family: \"Roboto\", helvetica, arial, sans-serif;\n"
		"\t\t\t\ttext-shadow: -1px -1px 1px rgba(0, 0, 0, 0.1);\n"
		"\t\t\t\ttext-transform:uppercase;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.table-fill {\n"
		"\t\t\t\tbackground: white;\n"
		"\t\t\t\tborder-radius:3px;\n"
		"\t\t\t\tborder-collapse: collapse;\n"
		"\t\t\t\theight: 320px;\n"
		"\t\t\t\tmargin: auto;\n"
		"\t\t\t\tmax-width: 600px;\n"
		"\t\t\t\tpadding:5px;\n"
		"\t\t\t\twidth: 100%;\n"
		"\t\t\t\tbox-shadow: 0 5px 10px rgba(0, 0, 0, 0.1);\n"
		"\t\t\t\tanimation: float 5s infinite;\n"
		"\t\t\t}\n"
		"\t\t\t\n"
		"\t\t\tth {\n"
		"\t\t\t\tcolor:#D5DDE5;;\n"
		"\t\t\t\tbackground:#1b1e24;\n"
		"\t\t\t\tborder-bottom:4px solid #9ea7af;\n"
		"\t\t\t\tborder-right: 1px solid #343a45;\n"
		"\t\t\t\tfont-size:23px;\n"
		"\t\t\t\tfont-weight: 100;\n"
		"\t\t\t\tpadding:24px;\n"
		"\t\t\t\ttext-align:left;\n"
		"\t\t\t\ttext-shadow: 0 1px 1px rgba(0, 0, 0, 0.1);\n"
		"\t\t\t\tvertical-align:middle;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\tth:first-child {\n"
		"\t\t\t\tborder-top-left-radius:3px;\n"
		"\t\t\t}\n"
		"\t\t\t\n"
		"\t\t\tth:last-child {\n"
		"\t\t\t\tborder-top-right-radius:3px;\n"
		"\t\t\t\tborder-right:none;\n"
		"\t\t\t}\n"
		"\t\t\t\n"
		"\t\t\ttr {\n"
		"\t\t\t\tborder-top: 1px solid #C1C3D1;\n"
		"\t\t\t\tborder-bottom-: 1px solid #C1C3D1;\n"
		"\t\t\t\tcolor:#666B85;\n"
		"\t\t\t\tfont-size:16px;\n"
		"\t\t\t\tfont-weight:normal;\n"
		"\t\t\t\ttext-shadow: 0 1px 1px rgba(256, 256, 256, 0.1);\n"
		"\t\t\t}\n"
		"\t\t\t\n"
		"\t\t\ttr:hover td {\n"
		"\t\t\t\tbackground:#4E5066;\n"
		"\t\t\t\tcolor:#FFFFFF;\n"
		"\t\t\t\tborder-top: 1px solid #22262e;\n"
		"\t\t\t\t}\n"
		"\t\t\t\n"
		"\t\t\ttr:first-child {\n"
		"\t\t\t\tborder-top:none;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\ttr:last-child {\n"
		"\t\t\t\tborder-bottom:none;\n"
		"\t\t\t}\n"
		"\t\t\t\n"
		"\t\t\ttr:nth-child(odd) td {\n"
		"\t\t\t\tbackground:#EBEBEB;\n"
		"\t\t\t}\n"
		"\t\t\t\n"
		"\t\t\ttr:nth-child(odd):hover td {\n"
		"\t\t\t\tbackground:#4E5066;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\ttr:last-child td:first-child {\n"
		"\t\t\t\tborder-bottom-left-radius:3px;\n"
		"\t\t\t}\n"
		"\t\t\t\n"
		"\t\t\ttr:last-child td:last-child {\n"
		"\t\t\t\tborder-bottom-right-radius:3px;\n"
		"\t\t\t}\n"
		"\t\t\t\n"
		"\t\t\ttd {\n"
		"\t\t\t\tbackground:#FFFFFF;\n"
		"\t\t\t\tpadding:20px;\n"
		"\t\t\t\ttext-align:left;\n"
		"\t\t\t\tvertical-align:middle;\n"
		"\t\t\t\tfont-weight:300;\n"
		"\t\t\t\tfont-size:18px;\n"
		"\t\t\t\ttext-shadow: -1px -1px 1px rgba(0, 0, 0, 0.1);\n"
		"\t\t\t\tborder-right: 1px solid #C1C3D1;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\ttd:last-child {\n"
		"\t\t\t\tborder-right: 0px;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\tth.text-left {\n"
		"\t\t\t\ttext-align: left;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\tth.text-center {\n"
		"\t\t\t\ttext-align: center;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\tth.text-right {\n"
		"\t\t\t\ttext-align: right;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\ttd.text-left {\n"
		"\t\t\t\ttext-align: left;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\ttd.text-center {\n"
		"\t\t\t\ttext-align: center;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\ttd.text-right {\n"
		"\t\t\t\ttext-align: right;\n"
		"\t\t\t}\n"
		"\n"
		"\n"
		"\t\t</style>\n"
		"\t</head>\n"
		"\t<body>\n"
		"\t\t<div class=\"container\">\n"
		"\t\t\t<header>\n"
		"\t\t\t\t<h1>REMS-Real-time Electricity Monitoring System</h1> <br/>\n"
		"\t\t\t</header>\n"
		"\t\t\t<section class=\"main\">\n"
		"\t\t\t\t<div class=\"switch btn-oval\">\n"
		"\t\t\t\t\t<input type=\"checkbox\" name=\"pinOne\" onclick=\"handleClick(this)\";>\n"
		"\t\t\t\t\t<label><i></i></label>\n"
		"\t\t\t\t</div>\n"
		"\n"
		"\t\t\t\t<div class=\"table-title\">\n"
		"\t\t\t\t\t<h3>Usage</h3>\n"
		"\t\t\t\t</div>\n"
		"\t\t\t\t<table id=\"data-table\" class=\"table-fill\">\n"
		"\t\t\t\t\t<thead>\n"
		"\t\t\t\t\t\t<tr>\n"
		"\t\t\t\t\t\t\t<th class=\"text-left\">Time</th>\n"
		"\t\t\t\t\t\t\t<th class=\"text-left\">Usage</th>\n"
		"\t\t\t\t\t\t\t<th class=\"text-left\">Rate (Rs.)</th>\n"
		"\t\t\t\t\t\t</tr>\n"
		"\t\t\t\t\t</thead>\n"
		"\t\t\t\t\t<tbody class=\"table-hover\">\n"
		"\t\t\t\t\t\t<tr>\n"
		"\t\t\t\t\t\t\t<td class=\"text-left\"></td>\n"
		"\t\t\t\t\t\t\t<td class=\"text-left\"></td>\n"
		"\t\t\t\t\t\t</tr>\n"
		"\t\t\t\t\t</tbody>\n"
		"\t\t\t\t</table>\n"
		"\t\t\t</section>\n"
		"\t\t</div>\n"
		"\t\t<script>\n"
		"\t\t\t\n"
		"\t\t\tfunction updateVals() {\n"
		"\n"
		"\t\t\t\t\tlet xhttp = new XMLHttpRequest();\n"
		"\t\t\t\t\txhttp.onreadystatechange = function() {\n"
		"\t\t\t\t\t\tif (this.readyState == 4 && this.status == 200) {\n"
		"\t\t\t\t\t\t\tvar reading = parseInt(this.responseText);\n"
		"\n"
		"\t\t\t\t\t\t\tvar table = document.getElementById(\"data-table\");    \n"
		"\t\t\t\t\t\t\tvar row = table.insertRow(1);\n"
		"\t\t\t\t\t\t\tvar timeCell = row.insertCell(0);\n"
		"\t\t\t\t\t\t\tvar usageCell = row.insertCell(1);\n"
		"\t\t\t\t\t\t\tvar rateCell = row.insertCell(2);\n"
		"\n"
		"\t\t\t\t\t\t\ttimeCell.innerHTML = new Date();\n"
		"\t\t\t\t\t\t\trateCell.innerHTML = reading;\n"
		"\t\t\t\t\t\t\tusageCell.innerHTML = reading/17;\n"
		"\t\t\t\t\t\t}\n"
		"\t\t\t\t\t}\n"
		"\t\t\t\t\txhttp.open(\"GET\", \"getReading\", true);\n"
		"\t\t\t\t\txhttp.send();\n"
		"\t\t\t\t}\n"
		"\n"
		"\t\t\t\tfunction handleClick(cb) {\n"
		"\t\t\t\t\tif(cb.checked) {\n"
		"\t\t\t\t\t\tthis.path = cb.name + \"On\";\n"
		"\t\t\t\t\t\tloadInterval = setInterval(updateVals, 3000)\n"
		"\t\t\t\t\t}\n"
		"\t\t\t\t\telse {\n"
		"\t\t\t\t\t\tthis.path = cb.name + \"Off\";\n"
		"\t\t\t\t\t\tclearInterval(loadInterval);\n"
		"\t\t\t\t\t}\n"
		"\t\t\t\t\tlet xhttp = new XMLHttpRequest();\n"
		"\t\t\t\t\txhttp.open(\"GET\", path, true);\n"
		"\t\t\t\t\txhttp.send();\n"
		"\t\t\t\t}\n"
		"\t\t</script>\n"
		"\t</body>\n"
		"</html>"
	);
}

void handelePinOneOn() {
	digitalWrite(pin1, HIGH);
	onFlag = 1;
	server.send(200, "text/html", "Pin one turned on");
}

void handelePinOneOff() {
	digitalWrite(pin1, LOW);
	onFlag = 0;
	server.send(200, "text/html", "Pin one turned off");
}

void handeleGetReading() {
	server.send(200, "text/html", String(reading));
}

void drawValue() {
		display.clear();
		display.setTextAlignment(TEXT_ALIGN_LEFT);
		display.setFont(ArialMT_Plain_16);
		display.drawString(0, 10, "Reading: ");
		display.setFont(ArialMT_Plain_24);
		display.drawString(0, 30, String(reading));
		display.display();
}

void drawString(String str) {
		display.clear();
		display.setTextAlignment(TEXT_ALIGN_LEFT);
		display.setFont(ArialMT_Plain_16);
		display.drawString(0, 10, str);
		display.display();
		delay(5000);
}

void setupWiFi(){
	Serial.print("Connecting to ");
	Serial.println(ssid);
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.println("WiFi connected");
}

int calCurrent() {
	if(!onFlag) {
		return 0;
	}
	return (analogRead(A0) * 220)/60;
}

void setup() {

	pinMode(pin1, OUTPUT);
	pinMode(pin2, OUTPUT);

	Serial.begin(115200);
	display.init();
	display.flipScreenVertically();

	delay(1000);

	//Serial.print("Configuring access point...");
	//drawString("Configuring access point...");
	//WiFi.softAP(ssid);
	//WiFi.softAP(ssid, password);
	setupWiFi();
	IPAddress myIP = WiFi.localIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);
	drawString("IP address: "+String(myIP));

	server.on("/", handleRoot);
	server.on("/pinOneOn", handelePinOneOn);
	server.on("/pinOneOff", handelePinOneOff);
	server.on("/getReading", handeleGetReading);

	server.begin();
	Serial.println("HTTP server started");
	drawString("HTTP server started");

}

void loop() {
	reading += calCurrent();
	drawValue();
	server.handleClient();
}
