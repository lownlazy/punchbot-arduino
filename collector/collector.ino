//in
int resetBtnPin = 1;
int startContactPin = 3;

//out
int reactionPin = 13;
int triggerPin = 3;

//encoder vars
volatile int segCounter = 0; 
volatile int segCountMax = 150; 
volatile unsigned long segArray[150];
volatile int segPos[150];
volatile int pos = 0;

//vars
volatile int isOpen = 0;
int openState = 0;    
int lastOpenState = 0;  

void setup() {
 pinMode(triggerPin, INPUT);
  pinMode(resetBtnPin, INPUT);
  attachInterrupt(0,  encoderInterupt, CHANGE);
 //attachInterrupt(1,  encoderInterupt, CHANGE);

 Serial.begin(9600);
}

void loop() 
{
  setIsOpen();
    
  int resetBtnVal = analogRead(resetBtnPin);
      
  if(resetBtnVal > 700){
      reset();
    }

  if( segCounter == segCountMax) 
  {
      int i = 1;  
      for (i = 1; i < segCountMax; i++) 
      { 
        unsigned long first = segArray[i-1] - segArray[0];      
        Serial.println(first); 
      }
      
      Serial.println("end");
      
      segCounter = 999;
      isOpen = 0;  
  }

  delay(500);
} 

void reset()
{
   pos=0;
   segCounter=0;
   Serial.println("reset");
}

void encoderInterupt()
{
  if(segCounter < segCountMax) 
  {
     segArray[segCounter] = micros();
     segCounter++;
  } 
  pos++;
}

void setIsOpen()
{
  int openVal = analogRead(startContactPin);
  openState = openVal<100?1:0;

  if (openState != lastOpenState) 
  {
    isOpen = openState; 
  }
  lastOpenState = openState;
 }


