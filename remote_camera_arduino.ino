// BUT : prise de photo toutes les secondes + possibilité de pause avec intervale d'une seconde qui continue à etre suivi
// Capteur de tour + Bouton photo + Prise de photo (D9 D10 D11)
// cable blanc un sur le GND, l'autre sur le 9
// cable
int bouton = 10;   // bouton de prise de photo
int action_pin = 11;   // actionneur de photo
int led = 13; // la led qui sera activé quand on fait un tour
int capture = 1;
unsigned long action_time = 3000;


void setup() {
  pinMode(bouton, INPUT_PULLUP);
  pinMode(action_pin, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(action_pin, LOW);
}


void loop() {

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

void prendre_photo()
{
  digitalWrite(action_pin, HIGH); // shunt interupteur de prise de photo via optocoupleur
  digitalWrite(led, HIGH);
  delay(100);                     // délai pour prise en compte de l'appui prise de photo
  digitalWrite(action_pin, LOW);
  digitalWrite(led, LOW);
}
