/*
robot_siren

created:   16 mar 2014
modified:  22 mar 2014
by:        tyler stephen
description:
  program waits for a digital high signal on port d10.
  a buzzer is given rapidly increasing and decreasing tones
  to create a siren effect. the siren loops until the signal
  goes down.
*/

const int trigger = 10;
const int buzzer = 12;


void siren(){
  int note_duration = 1000/8; //8th note
  int pause_between_notes = note_duration * 0.2;
  int current_freq = 25;
  int freq_increment = 80;
  
  while(digitalRead(trigger) == HIGH){
    tone(buzzer, current_freq, note_duration);
    delay(pause_between_notes);
    current_freq += freq_increment;
    if(current_freq == 25 || current_freq == 3225){
      freq_increment = -freq_increment;
    }/*if*/
  }/*while*/
  
}/*siren*/


void setup(){
  pinMode(trigger, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop(){
  if(digitalRead(trigger) == HIGH){
    siren(); //will run as long as trigger == HIGH
    //play a song, I guess
  }
}
