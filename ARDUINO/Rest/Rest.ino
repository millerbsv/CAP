#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

YunServer server;
String startString;
long hits = 0;

void setup() {
  Serial.begin(9600,SERIAL_7E2);
  // Bridge startup
  Bridge.begin();
  // Listen for incoming connection only from localhost
  server.listenOnLocalhost();
  server.begin();
}

void loop() {
  // Get clients coming from server
  YunClient client = server.accept();
  // There is a new client?
  if (client){
    // read the command
        String command = client.readStringUntil('/');
    command.trim();        //kill whitespace
    // is "temperature" command?
    if (command=="print"){
      command=client.readStringUntil('/');
      command.trim();
      String instruccion = "PRINT #1, \"";
      instruccion = instruccion +command+"\"";
      Serial.println(instruccion);   
      // set JSON header
      client.println("Status: 200");
      client.println("Content-type: application/json");
      client.println();
      // return ok status
      client.print("{\"ret\":\"ok\"}");
    }
    // Close connection and free resources.
    client.stop();
    hits++;
  }
  delay(50); // Poll every 50ms
}
