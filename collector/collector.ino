//in
int resetBtnPin = 1;
int startContactPin = 3;

//out
int reactionPin = 13;
int triggerPin = 3;

//encoder vars
volatile int riseCounter = 0; 
volatile int fallCounter = 0; 
volatile int countMax = 50; 
volatile float riseArray[50];
volatile float fallArray[50];
unsigned long start = 0;
volatile boolean isArmOpen = true;


void setup() {
 pinMode(triggerPin, INPUT);
  pinMode(resetBtnPin, INPUT);
  attachInterrupt(0,  encoderInteruptR, CHANGE);
  attachInterrupt(1,  encoderInteruptF, CHANGE);

 setup_T2();
 Serial.begin(9600);
}

void loop() 
{
  setIsArmOpen();
  
  if(isArmOpen == true ) //start contact strip
  { 
    if(riseCounter == 999)
    {
      //reset();
    }    
  }
  
  int resetBtnVal = analogRead(resetBtnPin);
  
  if(resetBtnVal > 700){
      reset();
    }

  if( riseCounter == countMax && fallCounter == countMax) 
  {
      //Serial.println(0);
      //remember: the time between 0 and index[0] is unknown and
      //should never be used for a calculation
      
      Serial.println("rise-start");
      for (int i = 0; i < countMax; i++) 
      {     
        float val = riseArray[i] - riseArray[0];   
        Serial.println(val);
       delay(10);
      }
      Serial.println("rise-end");
      
      Serial.println("fall-start");
      for (int j = 0; j < countMax; j++) 
      {     
        float val1 = fallArray[j] - fallArray[0];   
        Serial.println(val1);
       delay(10);
      }
      Serial.println("fall-end");
      
      riseCounter = 999;

  }

  
} 

// helpers -------------------

void reset()
{
if(riseCounter == 999)
{
     riseCounter=0;
     fallCounter=0;
     Serial.println("reset (method)");
     reset_T2();
}
}

void setIsArmOpen()
{
  float openVal = analogRead(startContactPin);
  isArmOpen = openVal<200?true:false;
}

//interupts--------------------

void encoderInteruptR()
{
  if(riseCounter < countMax) 
  {
     riseArray[riseCounter] = get_T2_micros()*10; //micros();
     riseCounter++;
  } 
}

void encoderInteruptF()
{
  if(fallCounter < countMax) 
  {
     fallArray[fallCounter] = get_T2_micros(); //micros();
     fallCounter++;
  } 
}





