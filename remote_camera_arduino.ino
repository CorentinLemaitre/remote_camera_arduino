// BUT : prise de photo toutes les secondes + possibilité de pause avec intervale d'une seconde qui continue à etre suivi
// Capteur de tour + Bouton photo + Prise de photo (D9 D10 D11)
// cable blanc un sur le GND, l'autre sur le 9
// cable
int bouton = 10;        // bouton de prise de photo
int action_pin = 11;    // actionneur de photo
int led = 13;
int capture = 1;
int logger = A0;
unsigned long action_time = 3000;
bool auto_mode = true;
int ntour = 0;
int capteur = 9;     // compteur de tour
int tmax = 7;    // 2 aimants pour une roue de 700 : 0,5 tour = 1,065m / 1 aimant pour une roue de brompton 1 tour = 1,33
unsigned long button_timer ;


void setup() {
  pinMode(bouton, INPUT_PULLUP);
  pinMode(action_pin, OUTPUT);
  pinMode(logger, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(action_pin, LOW);
  digitalWrite(logger, LOW);
  
  pinMode(capteur, INPUT_PULLUP);
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
      button_timer = millis();
      while (digitalRead(bouton) == LOW && millis() - button_timer <= 2000L) {
        delay(10);
      }
      digitalWrite(led, LOW);
      if (millis() - button_timer > 2000L) {
        changement_mode();
      }
      else if (capture == 1) {  // commutation prise de vue en continu ou pas
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
    if (ntour >= tmax) {
      prendre_photo();
      ntour = 0;
    }
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
      button_timer = millis();
      while (digitalRead(bouton) == LOW && millis() - button_timer <= 2000L) {
        delay(10);
      }
      digitalWrite(led, LOW);
      if (millis() - button_timer > 2000L) {
        changement_mode();
      }
      else {
        ntour = tmax;
      }
    }
  }

}

void prendre_photo()
{
  digitalWrite(action_pin, HIGH); // shunt interupteur de prise de photo via optocoupleur
  digitalWrite(logger, HIGH); // lance un log sur le arduino 2
  digitalWrite(led, HIGH);
  delay(100);                     // délai pour prise en compte de l'appui prise de photo
  digitalWrite(action_pin, LOW);
  digitalWrite(logger, LOW);
  digitalWrite(led, LOW);
}

void changement_mode () {
  if (auto_mode) {
    auto_mode = false;
    clignoter();
  }
  else {
    auto_mode = true;
    clignoter();
    // capture = 1;                   // on active si désiré le mode prise de vue ayu redémarage
    action_time = millis() + 1000L;   // on règle la valeur du compteur pour une prise de vue
  }
}

void lire_bouton () {       // fonction a activer après modif de la pause en mode auto

  button_timer = millis();
  if (digitalRead(bouton) == LOW) {
    digitalWrite(led, HIGH);
    while (digitalRead(bouton) == LOW && millis() - button_timer <= 2000L) {
      delay(10);
    }
    digitalWrite(led, LOW);
  }
}

void clignoter()
{
  digitalWrite(led, LOW);
  delay (1000);
  digitalWrite(led, HIGH);
  delay (250);
  digitalWrite(led, LOW);
  delay (250);
  digitalWrite(led, HIGH);
  delay (250);
  digitalWrite(led, LOW);
  delay (250);
}
