
int resetBtnPin = 1;
int startContactPin = 3;

volatile int counter = 0;
volatile int countMax =300;
volatile float array[300];
volatile float x = 0;
volatile boolean isArmOpen = true;


void setup() 
{
  //explicitly prepare arrary blank values
  for (int i = 0; i < countMax; i++)
  {
    array[i] = 0;
  }
  
  attachInterrupt(1,  encoderInterupt, CHANGE);

  Serial.begin(9600);
  setup_T2();
}

void loop()
{
    setIsArmOpen();
  
  if(isArmOpen == false && counter == 999) //start contact strip
  { 
      reset();    
  }
  
  int resetBtnVal = analogRead(1);

  //on button down
  if(resetBtnVal > 700){
      reset();
  }
      
  if ( counter == countMax )
  {
    for (int i = 0; i < countMax; i++)
    {
      Serial.println(array[i]);
      delay(10);
    }
    Serial.println("end");
    counter=999;
  }
}

void encoderInterupt()
{
  if (counter < countMax)
  {
    x = get_T2_count();    
    array[counter] = x;
    counter++;
  }
}

void reset()
{
  if(counter == 999)
  {
     counter=0;
     Serial.println("reset");
     reset_T2();
   }
}

void setIsArmOpen()
{
  float openVal = analogRead(startContactPin);
  isArmOpen = openVal<200?true:false;
}
