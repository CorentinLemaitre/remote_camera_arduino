// BUT : prise de photo toutes les secondes + possibilité de pause avec intervale d'une seconde qui continue à etre suivi
// Capteur de tour + Bouton photo + Prise de photo (D9 D10 D11)
// cable blanc un sur le GND, l'autre sur le 9
// cable
int bouton = 10;        // bouton de prise de photo
int action_pin = 11;    // actionneur de photo
int led = 13;
int capture = 1;
unsigned long action_time = 3000;
bool auto_mode = true;

int capteur = 9;     // compteur de tour
int tmax = 7;    // 2 aimants pour une roue de 700 : 0,5 tour = 1,065m / 1 aimant pour une roue de brompton 1 tour = 1,33


void setup() {
  pinMode(bouton, INPUT_PULLUP);
  pinMode(action_pin, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(action_pin, LOW);

  pinMode(capteur, INPUT_PULLUP);
  pinMode(action_pin, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(action_pin, LOW);
}


void loop() {

  if (auto_mode) {
    if ( millis() >= action_time) {
      if (capture == 1) {
        prendre_photo();
      }
      action_time = action_time + 1000L;
    }

    if (digitalRead(bouton) == LOW) {
      digitalWrite(led, HIGH);
      while (digitalRead(bouton) == LOW) {
        delay(10);
      }
      digitalWrite(led, LOW);
      if (capture == 1) {
        capture = 0;
      }
      else {
        capture = 1;
        action_time = millis();
      }
    }
    delay(10);
  }
  else
  {
    int ntour = 0;
    while (ntour < tmax) {
      if (digitalRead(capteur) == LOW) {
        digitalWrite(led, HIGH);
        ntour++;
        while (digitalRead(capteur) == LOW) {
          delay(10);
        }
        digitalWrite(led, LOW);
      }
      if (digitalRead(bouton) == LOW) {
        digitalWrite(led, HIGH);
        ntour = tmax;
        while (digitalRead(bouton) == LOW) {
          delay(10);
        }
        digitalWrite(led, LOW);
      }
    }
    prendre_photo();
  }

}

void prendre_photo()
{
  digitalWrite(action_pin, HIGH); // shunt interupteur de prise de photo via optocoupleur
  digitalWrite(led, HIGH);
  delay(100);                     // délai pour prise en compte de l'appui prise de photo
  digitalWrite(action_pin, LOW);
  digitalWrite(led, LOW);
}
