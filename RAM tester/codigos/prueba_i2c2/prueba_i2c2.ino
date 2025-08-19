#include <DTWI.h>

DTWI1 myI2C2;  // Usamos I2C2

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Escaneando I2C2...");

  if (!myI2C2.beginMaster(DTWI::FQ400KHz)) {
    Serial.println("Error al inicializar I2C2 como master");
    while (1);
  }

  
}

void loop() {
  uint8_t found = 0;
  for (uint8_t address = 1; address < 127; address++) {
    // Intentar iniciar comunicación como master
    if (myI2C2.startMasterWrite(address)) {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
      found++;
      myI2C2.stopMaster();  // Siempre detener después
    }
  }

  if (found == 0) {
    Serial.println("No se encontraron dispositivos.");
  } else {
    Serial.print("Total encontrados: ");
    Serial.println(found);
  }

  delay(3000);
}
