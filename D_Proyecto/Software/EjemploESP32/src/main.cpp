#include <WiFi.h>
#include <WebServer.h>

// Nombre de la red Wi-Fi y contraseña
const char* ssid = "lacasona";
const char* password = "cordoba2023";

// Crear una instancia de WebServer
WebServer server(80);

// Pines de entrada analógica
int inputPin1 = 34;
int inputPin2 = 35;
int inputPin3 = 36;
int inputPin4 = 39;

// Pines de entrada digital
int inputPin5 = 23;
int inputPin6 = 22;
int inputPin7 = 21;
int inputPin8 = 19;

// Pines de salida digital
int outputPin1 = 18;
int outputPin2 = 5;
int outputPin3 = 17;
int outputPin4 = 16;

void setup() {
  // Inicializar pines de entrada y salida
  pinMode(inputPin1, INPUT);
  pinMode(inputPin2, INPUT);
  pinMode(inputPin3, INPUT);
  pinMode(inputPin4, INPUT);
  pinMode(inputPin5, INPUT);
  pinMode(inputPin6, INPUT);
  pinMode(inputPin7, INPUT);
  pinMode(inputPin8, INPUT);
  pinMode(outputPin1, OUTPUT);
  pinMode(outputPin2, OUTPUT);
  pinMode(outputPin3, OUTPUT);
  pinMode(outputPin4, OUTPUT);

  // Inicializar conexión Wi-Fi
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Configurar rutas del servidor web
  server.on("/", handleRoot);
  server.on("/analog_inputs", handleAnalogInputs);
  server.on("/digital_inputs", handleDigitalInputs);
  server.on("/digital_outputs", handleDigitalOutputs);

  // Iniciar servidor web
  server.begin();
  Serial.println("Server started");
}

void loop() {
  // Manejar solicitudes del servidor web
  server.handleClient();
}

void handleRoot() {
  // Mostrar página principal
  String html = "<html><head><title>ESP32 Web Server</title></head><body>";
  html += "<h1>ESP32 Web Server</h1>";
  html += "<ul>";
  html += "<li><a href=\"/analog_inputs\">Analog Inputs</a></li>";
  html += "<li><a href=\"/digital_inputs\">Digital Inputs</a></li>";
  html += "<li><a href=\"/digital_outputs\">Digital Outputs</a></li>";
  html += "</ul>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleAnalogInputs() {
  // Aquí mostramos valores de entrada analógica
  String html = "<html><head><title>Analog Inputs</title></head><body>";
  html += "<h1>Analog Inputs</h1>";
  html += "<ul>";
  // pegar aqui el codigo de los pines analogicos  Jose
  html += "<li>Input 2: " + String(analogRead(inputPin2)) + "</li>"; 
  // pegar aqui el codigo de los pines analogicos  jairo
  html += "<li>Input 4: " + String(analogRead(inputPin4)) + "</li>";
html += "</ul>";
html += "<a href="/">Back</a>";
html += "</body></html>";
server.send(200, "text/html", html);
}

void handleDigitalInputs() {
// Aquí mostramos valores de entrada digital
String html = "<html><head><title>Digital Inputs</title></head><body>";
html += "<h1>Digital Inputs</h1>";
html += "<ul>";

  // pegar aqui el codigo de los pines digitales  jairo
  // pegar aqui el codigo de los pines digitales  paola
  html += "<li>Input 8: " + String(digitalRead(inputPin8)) + "</li>";
html += "<li>Input 6: " + String(digitalRead(inputPin6)) + "</li>";
html += "<li>Input 7: " + String(digitalRead(inputPin7)) + "</li>";
html += "<li>Input 8: " + String(digitalRead(inputPin8)) + "</li>";
html += "</ul>";
html += "<a href="/">Back</a>";
html += "</body></html>";
server.send(200, "text/html", html);
}

void handleDigitalOutputs() {
// Aquí mostramos  y controlamos valores de salida digital
String html = "<html><head><title>Digital Outputs</title></head><body>";
html += "<h1>Digital Outputs</h1>";
html += "<ul>";
html += "<li>Output 1: " + String(digitalRead(outputPin1)) + " <a href="/digital_outputs?action=toggle&pin=1">Toggle</a></li>";
html += "<li>Output 2: " + String(digitalRead(outputPin2)) + " <a href="/digital_outputs?action=toggle&pin=2">Toggle</a></li>";
html += "<li>Output 3: " + String(digitalRead(outputPin3)) + " <a href="/digital_outputs?action=toggle&pin=3">Toggle</a></li>";
html += "<li>Output 4: " + String(digitalRead(outputPin4)) + " <a href="/digital_outputs?action=toggle&pin=4">Toggle</a></li>";
html += "</ul>";

// Manejamos las acciones del usuario
if (server.hasArg("action")) {
String action = server.arg("action");
if (action == "toggle") {
int pin = server.arg("pin").toInt();
if (pin == 1) {
digitalWrite(outputPin1, !digitalRead(outputPin1));
} else if (pin == 2) {
digitalWrite(outputPin2, !digitalRead(outputPin2));
} else if (pin == 3) {
digitalWrite(outputPin3, !digitalRead(outputPin3));
} else if (pin == 4) {
digitalWrite(outputPin4, !digitalRead(outputPin4));
}
}
}

html += "<a href="/">Back</a>";
html += "</body></html>";
server.send(200, "text/html", html);
}

