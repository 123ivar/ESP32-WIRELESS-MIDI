
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <MIDI.h>

#define SERVICE_UUID        "03b80e5a-ede8-4b33-a751-6ce34ec4c700"
#define CHARACTERISTIC_UUID "7772e5db-3868-4112-a1a9-f2669d106bf3"
MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, MIDI);

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;

uint8_t midiPacket[] = {
   0x80,  // header
   0x80,  // timestamp, not implemented 
   0x00,  // status
   0x3c,  // 0x3c == 60 == middle c
   0x00   // velocity
};

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
   midiPacket[2] = MIDI.getType(); //Note
   midiPacket[3] = pitch;
   midiPacket[4] = velocity;  
   pCharacteristic->setValue(midiPacket, 5); 
pCharacteristic->notify();
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
   midiPacket[2] = MIDI.getType();  //Note
   midiPacket[3] = pitch;
   midiPacket[4] = 0;   
   pCharacteristic->setValue(midiPacket, 5); 
pCharacteristic->notify();
}

void Mcc(byte channel, byte number, byte value)
{
 //  midiPacket[1] = 
   midiPacket[2] = MIDI.getType(); 
   midiPacket[3] = number;
   midiPacket[4] = value;  
   pCharacteristic->setValue(midiPacket, 5);
pCharacteristic->notify();
}

void pb(byte channel, int bend)
{
   midiPacket[2] = MIDI.getType(); 
   midiPacket[3] = number;
   midiPacket[4] = bend;  
   pCharacteristic->setValue(midiPacket, 5); 
pCharacteristic->notify();
}
void start()
{
   midiPacket[2] = MIDI.getType();
   midiPacket[3] = number;
   midiPacket[4] = value;  
   pCharacteristic->setValue(midiPacket, 5); 
pCharacteristic->notify();
}
void stopp()
{
   midiPacket[2] = MIDI.getType(); 
   midiPacket[3] = number;
   midiPacket[4] = value;  
   pCharacteristic->setValue(midiPacket, 5); 
pCharacteristic->notify();
}
void aftch(byte channel, byte pressure)
{
   midiPacket[2] = MIDI.getType(); 
   midiPacket[3] = number;
   midiPacket[4] = pressure;  
   pCharacteristic->setValue(midiPacket, 5); 
pCharacteristic->notify();
}
void aftpoly(byte channel, byte note, byte pressure)
{
   midiPacket[2] = MIDI.getType();
   midiPacket[3] = note;
   midiPacket[4] = pressure;
   pCharacteristic->setValue(midiPacket, 5); 
pCharacteristic->notify();  
}

void setup() {

    
    // Midi calls
    MIDI.setHandleNoteOn(handleNoteOn);  
    MIDI.setHandleNoteOff(handleNoteOff);
    MIDI.setHandleControlChange(Mcc);
    MIDI.setHandlePitchBend(pb);
    MIDI.setHandleStart(start);
    MIDI.setHandleStop(stopp);
    MIDI.setHandleAfterTouchChannel(aftch);
    MIDI.setHandleAfterTouchPoly(aftpoly);
  
    MIDI.begin(MIDI_CHANNEL_OMNI);

  BLEDevice::init("Akai MPD32 MIDI Out");
    
  // Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(BLEUUID(SERVICE_UUID));

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
    BLEUUID(CHARACTERISTIC_UUID),
    BLECharacteristic::PROPERTY_READ   |
    BLECharacteristic::PROPERTY_WRITE  |
    BLECharacteristic::PROPERTY_NOTIFY |
    BLECharacteristic::PROPERTY_WRITE_NR
  );

  // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
  // Create a BLE Descriptor
  pCharacteristic->addDescriptor(new BLE2902());

  // Start the service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();
}

void loop() {
  if (deviceConnected) {
    MIDI.read();

}
}
