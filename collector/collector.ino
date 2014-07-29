//in
int resetBtnPin = 1;
int startContactPin = 3;

//out
int reactionPin = 13;
int triggerPin = 3;

//encoder vars
volatile int segCounter = 0; 
volatile int segCountMax = 100; 
volatile unsigned long segArray[100];
volatile int segPos[100];
volatile int pos = 0;
unsigned long start = 550;

//vars
volatile int isOpen = 0;
int openState = 0;    
int lastOpenState = 0;  

void setup() {
 pinMode(triggerPin, INPUT);
  pinMode(resetBtnPin, INPUT);
  attachInterrupt(0,  encoderInterupt, RISING);
 //attachInterrupt(1,  encoderInterupt, CHANGE);

 Serial.begin(9600);
}

void loop() 
{
  setIsOpen();
  
  if(isOpen == 0 )
  {
    start = micros();
    
    if(segCounter == 999)
    {
       Serial.println("reset");
    }
    
    pos=0;
    segCounter=0;    
  }
  
  int resetBtnVal = analogRead(resetBtnPin);
      
  if(resetBtnVal > 700){
      reset();
    }

  if( segCounter == segCountMax) 
  {
      Serial.println(0);
      
      int segArrayZero = (segArray[1]-start)/2+1;
      Serial.println(segArrayZero);
      
      for (int i = 1; i < segCountMax; i++) 
      { 
        unsigned long val = segArray[i] - start;      
        Serial.println(val); 
      }
      
      Serial.println("end");
      
      segCounter = 999;
      isOpen = 0;  
  }

  //delay(50);
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
  float openVal = analogRead(startContactPin);
  isOpen = openVal<200?1:0;
}

