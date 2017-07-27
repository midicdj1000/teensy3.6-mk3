#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>
#include <ResponsiveAnalogRead.h>
Encoder wheel(31, 32);
ResponsiveAnalogRead analogpitch(A9, true);

int bttndel=1;
int winc = 63;
int wdec = 65;
long wheelpos  = -999;
int wheelmove = 0;
int jogflag = 0;
int speedad = 0;
int avgspeed = 0;
int totspeed = 0;
long vel = 0;
unsigned long newtime;
unsigned long oldtime = 0;
int veldelay = 60;
int channel = 1;

int loopinled=35;
int loopinb=34;

int loopoutb=33;
int loopoutled=15;

int hotcueared=55;
int hotcueagreen=54;
int hotcueayellow=56;
int hcab=57;

int hotcuebred=52;
int hotcuebgreen=51;
int hotcuebyellow=50;
int hcbb=53;

int hotcuecred=45;
int hotcuecgreen=46;
int hotcuecyellow=44;
int hccb=43;

int recb=38;

int cdjmodeled=5;
int vinylmodeled=6;
int modeb=4;


int playled=28;
int playb=29;

int jogpressb=30;

int cueled=26;
int cueb=27;

int temporangeb=8;

int mastertempob=9;
int mastertempoled=7;

int trackbb=11;
int trackfb=10;
int scanbb=24;
int scanfb=12;

int pitch=39;
long pitchval=0;
long oldpitchval=0;

int loopexitb=17;
int loopexitled=16;
int wavbb=19;
int wavfb=18;
int callbb=20;
int callforb=21;

int delbtn=2;
int membtn=3;
int timebtn=37;
int txtbtn=36;

int revled=25;
int revbtn=42;
int ejectbtn=22;


int buttons[30] = {loopinb,loopoutb,hcab,hcbb,hccb,recb,modeb,playb,jogpressb,cueb,temporangeb,mastertempob,trackbb,trackfb,scanbb,scanfb,loopexitb,wavbb,wavfb,callbb,callforb,revbtn,delbtn,membtn,timebtn,txtbtn,loopexitb,modeb,ejectbtn};
int leds[30] = {loopinled,loopoutled,hotcueagreen,hotcuebgreen,hotcuecgreen,0,cdjmodeled,playled,0,cueled,0,mastertempoled,0,0,0,0,0,0,0,0,0,revled,0,0,0,0,loopexitled,0,0};
int buttonstat[57] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int jogmode = 10;
int loopint = 22;

int led = 13;
int statOn = 60;

void OnNoteOn(byte channel, byte statOn, byte velocity)
{
  switch(statOn){
    case 5:
    digitalWrite(cdjmodeled, HIGH);
    case 6:
    digitalWrite(vinylmodeled, HIGH);
    case 9:
    digitalWrite(mastertempoled, HIGH);
    break;    
    case 17:
    digitalWrite(loopexitled, HIGH);  
    break;
    case 27:
    digitalWrite(cueled, HIGH);
    break;
    case 29:
    digitalWrite(playled, HIGH);
    break;
    case 33:
    digitalWrite(loopoutled, HIGH);
    break;
    case 34:
    digitalWrite(loopinled, HIGH);
    break;
    case 42:
    digitalWrite(revled, HIGH);  
    break;
    case 43:
    if (velocity==21){
      digitalWrite(hotcuecgreen,HIGH);
      digitalWrite(hotcuecred,LOW);
    }
    if (velocity==105){
      digitalWrite(hotcuecgreen,LOW);
      digitalWrite(hotcuecred,HIGH);
    }
    if (velocity==127){
      digitalWrite(hotcuecgreen,HIGH);
      digitalWrite(hotcuecred,HIGH);
    }
   break;  
   case 53:
    if (velocity==21){
      digitalWrite(hotcuebgreen,HIGH);
      digitalWrite(hotcuebred,LOW);
    }
    if (velocity==105){
      digitalWrite(hotcuebgreen,LOW);
      digitalWrite(hotcuebred,HIGH);
    }
    if (velocity==127){
      digitalWrite(hotcuebgreen,HIGH);
      digitalWrite(hotcuebred,HIGH);
    }
    break;
    case 57:
    if (velocity==21){
      digitalWrite(hotcueagreen,HIGH);
      digitalWrite(hotcueared,LOW);
    }
    if (velocity==105){
      digitalWrite(hotcueagreen,LOW);
      digitalWrite(hotcueared,HIGH);
    }
    if (velocity==127){
      digitalWrite(hotcueagreen,HIGH);
      digitalWrite(hotcueared,HIGH);
    }
   break;
  }   
}

void OnNoteOff(byte channel, byte statOn, byte velocity)
{
  switch(statOn){
    case 5:
    digitalWrite(cdjmodeled, LOW);
    case 6:
    digitalWrite(vinylmodeled, LOW);    
    case 9:
    digitalWrite(mastertempoled, LOW);
    break;    
    case 17:
    digitalWrite(loopexitled, LOW);  
    break;
    case 27:
    digitalWrite(cueled, LOW);
    break;
    case 29:
    digitalWrite(playled, LOW);
    break;
    case 33:
    digitalWrite(loopoutled, LOW);
    break;
    case 34:
    digitalWrite(loopinled, LOW);
    break;
    case 42:
    digitalWrite(revled, LOW);  
    break;    
    case 43:
      digitalWrite(hotcuecgreen,LOW);
      digitalWrite(hotcuecred,LOW);
    break;    
    case 53:
      digitalWrite(hotcuebgreen,LOW);
      digitalWrite(hotcuebred,LOW);
    break; 
    case 57:
      digitalWrite(hotcueagreen,LOW);
      digitalWrite(hotcueared,LOW);
    break;     
   
  }
}






// the setup routine runs once when you press reset:
void setup() {
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn) ;
  pinMode(2, INPUT_PULLUP); 
  pinMode(3, INPUT_PULLUP); 
  pinMode(4, INPUT_PULLUP); 
  pinMode(5, OUTPUT); 
  pinMode(6, OUTPUT); 
  pinMode(7, OUTPUT); 
  pinMode(8, INPUT_PULLUP);  
  pinMode(9, INPUT_PULLUP);  
  pinMode(10, INPUT_PULLUP); 
  pinMode(11, INPUT_PULLUP);  
  pinMode(12, INPUT_PULLUP);   
  pinMode(13, OUTPUT);
  //pinMode(14, OUTPUT);  
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, INPUT_PULLUP); 
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  pinMode(20, INPUT_PULLUP);
  pinMode(21, INPUT_PULLUP); 
  pinMode(22, INPUT_PULLUP); 
  //pinMode(23, OUTPUT);
  pinMode(24, INPUT_PULLUP);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, INPUT_PULLUP);
  pinMode(28, OUTPUT);
  pinMode(29, INPUT_PULLUP); 
  pinMode(30, INPUT_PULLUP);
  //pinMode(31, OUTPUT); 
  //pinMode(32, INPUT_PULLUP); 
  pinMode(33, INPUT_PULLUP);
  pinMode(34, INPUT_PULLUP);
  pinMode(35, OUTPUT);
  pinMode(36, INPUT_PULLUP);
  pinMode(37, INPUT_PULLUP);
  pinMode(38, INPUT);
  //pinMode(39, INPUT_PULLUP);
  //pinMode(40, INPUT_PULLUP);
  //pinMode(41, INPUT_PULLUP);
  pinMode(42, INPUT_PULLUP);
  pinMode(43, INPUT_PULLUP);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
  //pinMode(47, INPUT_PULLUP);
  //pinMode(48, INPUT_PULLUP);
  //pinMode(49, INPUT_PULLUP);
  pinMode(50, OUTPUT);
  pinMode(51, OUTPUT);
  pinMode(52, OUTPUT);
  pinMode(53, INPUT_PULLUP);
  pinMode(54, OUTPUT);
  pinMode(55, OUTPUT);
  pinMode(56, OUTPUT);
  pinMode(57, INPUT_PULLUP);

  digitalWrite(13, HIGH);
  jogmode = 10;
}

// the loop routine runs over and over again forever:
void loop() {
  usbMIDI.read();
  analogpitch.update();
  long newwheel;
  newtime = millis();
  newwheel = wheel.read();
  wheelmove = 0;
  vel = 0;
  if (newwheel > wheelpos) {
    vel = ((newwheel - wheelpos)  / (newtime - oldtime)) *2 ;
    if (vel>60) vel =60;
    if (vel <=0 ) vel = 0;
    if (buttonstat[8]==1){
      usbMIDI.sendControlChange(0, 127-vel, channel);
    } else {
      usbMIDI.sendControlChange(0, 127, channel);
    }
    wheelpos = newwheel;
  }
  if (newwheel < wheelpos) {
    vel = ((wheelpos - newwheel) / (newtime - oldtime)) * 2;
       if (vel>60) vel =60;
       if (vel <=0 ) vel = 0;
      if (buttonstat[8]==1){
        usbMIDI.sendControlChange(0, 1+vel, channel);
      } else {
        usbMIDI.sendControlChange(0, 1, channel);
      }
    wheelpos = newwheel;
  }
  oldtime = newtime;

       
for (int x=0;x<29;x++){
  if (digitalRead(buttons[x])==LOW){
    if (buttonstat[x]==0){
      buttonstat[x]=1;
      usbMIDI.sendNoteOn(buttons[x], 99, channel);    
      delay(bttndel);
    }  
  } else {
    if (buttonstat[x]==1){
      usbMIDI.sendNoteOff(buttons[x], 0, channel);       
      buttonstat[x]=0;
      delay(bttndel);
    }
  }
}

  if(analogpitch.hasChanged()) {
     pitchval=analogpitch.getValue()*16.015;
   //Serial.println(pitchval);  
    usbMIDI.sendPitchBend(pitchval, channel);
  }

usbMIDI.send_now();

  delay(1);
}


