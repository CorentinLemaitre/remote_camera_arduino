// Version 3 du 25/01/2020

// Capteur de tour + Bouton photo + Prise de photo (D9 D10 D11)
// cable blanc un sur le GND, l'autre sur le 9
// cable 
int tour = {9};     // compteur de tour
int bouton = {10};   // bouton de prise de photo
int shoot = {11};   // actionneur de photo
int shootled = {8}; //la led qui sera activé quand on prend une photo
int tourled = {13}; // la led qui sera activé quand on fait un tour 
int tmax = 9; // pour faire 5 tours de roues avant de déclencher soit 10m (roue de 700)
// int tmax = 8;  pour faire 8 tours de roues avant de déclencher soit 10m (roue de brompton)
// appui sur clavier = 16 ms au moins (5% à


void setup() {
    pinMode(bouton, INPUT_PULLUP); 
    pinMode(tour, INPUT_PULLUP);
    pinMode(shoot, OUTPUT);
    pinMode(shootled, OUTPUT);
    pinMode(tourled, OUTPUT);
    digitalWrite(shoot, LOW);
}



// the loop function runs over and over again forever
void loop() {
  
    for (int ntour = 0; ntour < tmax;) {  // on peut ne pas mettre de 3eme membre?
        ntour++;
        delay(100);
        if (digitalRead(bouton) == LOW) {
            digitalWrite(tourled, HIGH);
            ntour = tour+ tmax;
            while (digitalRead(bouton) == LOW){
                delay(10);
            }
            digitalWrite(tourled, LOW);
        }
    }
    digitalWrite(shoot, HIGH); //le but est de shunter un interupteur
    digitalWrite(tourled, HIGH);
    delay(101);
    digitalWrite(shoot, LOW); // reste appuyer jusqu'a la prochaine photo
    digitalWrite(tourled, LOW);
}


/*
// the setup function runs once when you press reset or power the board
void setup() {
    pinMode(bouton, INPUT_PULLUP); 
    pinMode(tour, INPUT_PULLUP);
    pinMode(shoot, OUTPUT);
    pinMode(shootled, OUTPUT);
    pinMode(tourled, OUTPUT);
    digitalWrite(shoot, HIGH);
}



// the loop function runs over and over again forever
void loop() {
    digitalWrite(shoot, HIGH); //le but est de shunter un interupteur
    digitalWrite(tourled, HIGH);
    delay(100);
    digitalWrite(tourled, LOW);
    delay(100);
    digitalWrite(tourled, HIGH);
    delay(100);
    digitalWrite(shoot, LOW); // reste appuyer jusqu'a la prochaine photo
    digitalWrite(tourled, LOW);
    
    for (int ntour = 0; ntour < tmax;) {  // on peut ne pas mettre de 3eme membre?
        if (digitalRead(tour) == LOW) {
            digitalWrite(tourled, HIGH);
            ntour++;
            while (digitalRead(tour) == LOW){
                delay(10);
            }
           digitalWrite(tourled, LOW);
        }
        if (digitalRead(bouton) == LOW) {
            digitalWrite(tourled, HIGH);
            ntour = tour+ tmax;
            while (digitalRead(bouton) == LOW){
                delay(10);
            }
            digitalWrite(tourled, LOW);
        }
    }
}
*/
