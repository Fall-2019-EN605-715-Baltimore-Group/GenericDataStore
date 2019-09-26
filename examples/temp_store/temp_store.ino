#include <DataStore.h>


void setup() {
  // Serial Port Setup
  Serial.begin(115200);
  delay(50);
  while(!Serial) ;

  Serial.println("Setup Complete!");
}

void loop() {

  DataStore data_store;

  Serial.println("Storing temperatures...");
  data_store.store_data(605, millis()); delay(10);
  data_store.store_data(612, millis()); delay(10);
  data_store.store_data(680, millis()); delay(10);
  data_store.store_data(324, millis()); delay(10);
  data_store.store_data(-5, millis()); delay(10);
  data_store.store_data(-158, millis()); delay(10);

  Serial.println("Calling to csv...");
  data_store.to_csv();

  Serial.println("Dumping the list...\n");
  data_store.dump_list();

  Serial.println("Done.");
  delay(5000);
}

