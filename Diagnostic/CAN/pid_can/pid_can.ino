#include <CAN.h>


const bool useStandardAddressing = true;

void setup() {
  Serial.begin(9600);

  Serial.println("CAN OBD-II supported pids");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }

  // add filter to only receive the CAN bus ID's we care about
  if (useStandardAddressing) {
    CAN.filter(0x7e8);
  } else {
    CAN.filterExtended(0x18daf110);
  }
}

void loop() {
  for (int pid = 0x00; pid < 0xe0; pid += 0x20) {
    if (useStandardAddressing) {
      CAN.beginPacket(0x7df, 8);

    } else {
      CAN.beginExtendedPacket(0x18db33f1, 8);
    }
    CAN.write(0x02); // number of additional bytes
    CAN.write(0x42); // show current data
    CAN.write(0x49);  // PID
    CAN.endPacket();

    // wait for response
    while (CAN.parsePacket() == 0 ||
           CAN.read() < 6 ||         // correct length
           CAN.read() != 0x41 ||     // correct mode
           CAN.read() !=49);      // correct PID

    unsigned long pidsSupported = 0;

    for (int i = 0; i < 4; i++) {
      pidsSupported <<= 8;
      pidsSupported |= CAN.read();
    }

    for (unsigned int i = 31; i > 0; i--) {
      if (pidsSupported & (1UL << i)) {
        int pidSupported = pid + (32 - i);

        Serial.print("0x");
        if (pidSupported < 16) {
          Serial.print("0");
        }
        Serial.println(pidSupported, HEX);     
      }
    }

    if ((pidsSupported & 0x00000001) == 0x00000000) {
      // next round not supported, all done
      break;
    }
  }

  Serial.println("That's all folks!");

  while (1); // all done
}