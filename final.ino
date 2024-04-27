#include <Wire.h>
#define echoPin 12               
#define trigPin 14               

int LDRSensor = 2;  // LDR sensor is connected to pin 2  (tiny light-sensing devices)
int motorPin = 26; //motor vibration is connected to pin 26

// Déclaration des broches pour les LED verte et rouge
int greenLED = 5; // LED verte
int redLED = 4;   // LED rouge
long duration, distance;
void setup(){
  // Définir le débit en bauds pour la communication série
  Serial.begin (9600);
  

 // Initialiser le capteur (broche 2) en tant qu'ENTRÉE.
  pinMode(LDRSensor, INPUT);

  // Déclarer motor vibration as output 
  pinMode(motorPin, OUTPUT);
  
  // Initialiser les broches des LED en tant que SORTIEs
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  
  // Éteindre les deux LED au démarrage
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);
   
   // Initialiser le capteur ultrason
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
  void loop() {
  // Lire la valeur de sortie numérique du capteur LDR
  int sensorData = digitalRead(LDRSensor);

  // Afficher la valeur du capteur LDR sur le moniteur série
  Serial.print("Valeur du capteur LDR: ");
  Serial.println(sensorData);

  // Lire la distance mesurée par le capteur à ultrasons
  int distance = getDistance();

  // Afficher la distance sur le moniteur série
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  // la marge de sécurité 
  if (distance < 160)
  {
   
    digitalWrite(motorPin, HIGH); // Alerte
    
  }
  else
  {
   digitalWrite(motorPin, LOW); // safe
  }
  
  // Délai pour observer les changements des LED
  delay(100);
   // Lire la distance mesurée par le capteur à ultrasons

  // Afficher la distance sur le moniteur série
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Logique de détection lumière et obscurité
  if (sensorData == LOW)
  {
    // C'est le jour
    digitalWrite(redLED, HIGH); // Allumer la LED rouge
    digitalWrite(greenLED, LOW);    // Éteindre la LED verte
  }
  else
  {
    // C'est la nuit
    digitalWrite(redLED, LOW);   // Éteindre la LED rouge
    digitalWrite(greenLED, HIGH);    // Allumer la LED verte 
  }
  
  // Délai pour observer les changements des LED
  delay(100);

}

  int getDistance() {
  // Envoi d'une impulsion de 10 µs sur la broche de déclenchement
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Mesure du temps nécessaire pour que le signal arrive
  long duration = pulseIn(echoPin, HIGH);

  // Conversion de la durée en distance (en cm)
  int distance = duration * 0.034 / 2;

  return distance;}

  