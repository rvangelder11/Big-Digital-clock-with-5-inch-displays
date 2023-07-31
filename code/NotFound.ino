//-----------------------------------
// This sends back a 404 message in case of an error
void notFound(AsyncWebServerRequest * request) {                // error handling
  request->send(404, "text/plain", "Not found");
}
