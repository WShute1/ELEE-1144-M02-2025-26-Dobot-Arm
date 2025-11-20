#define s0 8        //Module pins wiring
#define s1 9
#define s2 10
#define s3 11
#define out 12

int Red = 0, Blue = 0, Green = 0;  //RGB values 

void setup() 
{
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);

  Serial.begin(9600);

  digitalWrite(s0, HIGH);   //100% frequency scaling
  digitalWrite(s1, HIGH);
}

void loop() {

  GetColors();  //Reads RGB values from the sensor

  // ----------------------------------------------------
  // PRINT RAW COLOR LEVELS
  // ----------------------------------------------------
  Serial.print("Red: ");
  Serial.print(Red);
  Serial.print("   Green: ");
  Serial.print(Green);
  Serial.print("   Blue: ");
  Serial.println(Blue);

  // ----------------------------------------------------
  // COLOR IDENTIFICATION
  // ----------------------------------------------------
  if (Red <= 15 && Green <= 15 && Blue <= 15)
      Serial.println("Detected Color: White");

  else if (Red < Blue && Red <= Green && Red < 23)
      Serial.println("Detected Color: Red");

  else if (Blue < Green && Blue < Red && Blue < 20)
      Serial.println("Detected Color: Blue");

  else if (Green < Red && Green - Blue <= 8)
      Serial.println("Detected Color: Green");

  else
      Serial.println("Detected Color: Unknown");

  Serial.println("----------------------------------");
  delay(2000);
}

void GetColors()  
{    
  digitalWrite(s2, LOW);    
  digitalWrite(s3, LOW);    
  Red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  delay(20);  

  digitalWrite(s3, HIGH);   
  Blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  delay(20);  

  digitalWrite(s2, HIGH);  
  Green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  delay(20);  
}