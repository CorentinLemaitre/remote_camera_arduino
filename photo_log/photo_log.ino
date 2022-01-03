// Temps par horloge RTC
#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>  // a basic DS1307 library that returns time as a time_t

// Ecriture sur carte SD
#include <SPI.h> // Pour la communication SPI
#include <SD.h>  // Pour la communication avec la carte SD TODO changer de librairie

// Variables SD
File file_log;
bool SD_present = true;

// déclaration pour programme
int logger = A0;
int led = 13;

int counter = 0;

void setup() {
  pinMode(6, OUTPUT); // Carte SD
  pinMode(led, OUTPUT);
  pinMode(logger, INPUT);

  Serial.begin(115200);
  Serial.setTimeout(5);
  delay(4000);
  Serial.println();
  Serial.println(F("V0.1"));
  init_RTC();
  init_SD();

}

void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(logger) == HIGH) {
    if (digitalRead(led) == HIGH) {
      digitalWrite(led, LOW);
    } 
    else {
      digitalWrite(led, HIGH);
    }
    counter = counter + 1;
    while (digitalRead(logger) == HIGH) {
      delay(10);
    }
    if (SD_present) {
      file_log.print(now());
      file_log.print(F(";"));
      file_log.print(millis());
      file_log.print(F(";"));
      file_log.println(counter);
      file_log.flush();
      //Serial.print(F("SD")); // if DEBUG
      digitalWrite(led, LOW); // led est allumé si log non fait
    }
  }
}


void init_SD() {

  // Initialisation de la carte SD ------------------------------------------------

  const char* OUTPUT_FILENAME = "data.csv";
  const byte SDCARD_CS_PIN = A5; //Broche CS de la carte SD

  Serial.print(F("I_SD..."));
  Serial.println(SD.begin(SDCARD_CS_PIN));
  if (!SD.begin(SDCARD_CS_PIN)) {
    Serial.println(F("BUG_SD"));
    SD_present = false;
  }

  /* Ouvre le fichier de sortie en écriture */

  if (SD_present) {

    file_log = SD.open(OUTPUT_FILENAME, FILE_WRITE);
    if (!file_log) {
      Serial.println(F("BUG csv"));
    }
    /* Ajoute l'entête CSV si le fichier est vide */
    else if (file_log.size() == 0) {
      Serial.print(F("NEW log.csv..."));
      file_log.println(F("sec;milli;count")); // TODO
      file_log.flush();
    }
    else Serial.println(F("OK log.csv..."));

  }
}


void init_RTC() {
  // Initialisation de l'horloge ------------------------------------------

  Serial.print(F("I_RTC..."));

  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if (timeStatus() != timeSet)
    Serial.println(F("BUG RTC"));
  else
    Serial.println(F("OK RTC"));
}
