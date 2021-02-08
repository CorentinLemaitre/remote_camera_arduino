// Version 4 du 27/01/2020

// BUT : prise de photo toutes les secondes + possibilité de pause avec intervale d'une seconde qui continue à etre suivi
// Capteur de tour + Bouton photo + Prise de photo (D9 D10 D11)
// cable blanc un sur le GND, l'autre sur le 9
// cable 
int bouton = {10};   // bouton de prise de photo
int shoot = {11};   // actionneur de photo
int tourled = {13}; // la led qui sera activé quand on fait un tour 
int capture = 1;
unsigned long time_saved = 3000;
unsigned long time;


void setup() {
    pinMode(bouton, INPUT_PULLUP); 
    pinMode(shoot, OUTPUT);
    pinMode(tourled, OUTPUT);
    digitalWrite(shoot, LOW);
}



// the loop function runs over and over again forever
void loop() {
  time = millis();
  if (time > time_saved) {
    if (capture == 1) {
      digitalWrite(shoot, HIGH); //le but est de shunter un interupteur
      digitalWrite(tourled, HIGH);
      delay(100);
      digitalWrite(shoot, LOW); // reste appuyer jusqu'a la prochaine photo
      digitalWrite(tourled, LOW); 
    }
    time_saved = time_saved + 1000;
  }
  
  if (digitalRead(bouton) == LOW) {
    digitalWrite(tourled, HIGH);
    while (digitalRead(bouton) == LOW){
      delay(10);
    }
    digitalWrite(tourled, LOW);
    if (capture == 1) {
      capture = 0;
    }
    else {
      capture = 1;
    }
  }
  delay(10);   
}
