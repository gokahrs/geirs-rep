// Pins for Multiplexer kontroll
const int S0 = 1;
const int S1 = 2;
const int S2 = 3;
const int S3 = 4;
const int SIG_PIN = 0;   // Analog lesing fra multiplexer
const int SENSOR_VCC = 5; // Pin for å gi strøm til sensorene

void setup() {
  Serial.begin(115200);
  
  // Sett kontrollpinner som utganger
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(SENSOR_VCC, OUTPUT);
  
  digitalWrite(SENSOR_VCC, LOW); // Start med sensorene av
  Serial.println("Systemet starter - Test av 3 sensorer");
}

void loop() {
  // 1. Skru på strøm til sensorene
  digitalWrite(SENSOR_VCC, HIGH);
  delay(100); // La sensorene stabilisere seg (viktig for kapasitive sensorer)

  // 2. Les de 3 første kanalene på multiplexeren
  for (int i = 0; i < 3; i++) {
    selectChannel(i);
    int rawValue = analogRead(SIG_PIN);
    
    Serial.print("Plante ");
    Serial.print(i + 1);
    Serial.print(" - Fuktighet (råverdi): ");
    Serial.println(rawValue);
  }

  // 3. Skru av sensorene for å spare strøm (simulering av dvale)
  digitalWrite(SENSOR_VCC, LOW);
  
  Serial.println("-------------------------");
  delay(5000); // Vent 5 sekunder før neste måling
}

// Funksjon for å velge kanal på 74HC4067
void selectChannel(int channel) {
  digitalWrite(S0, bitRead(channel, 0));
  digitalWrite(S1, bitRead(channel, 1));
  digitalWrite(S2, bitRead(channel, 2));
  digitalWrite(S3, bitRead(channel, 3));
}
