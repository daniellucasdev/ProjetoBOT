#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "wifi";
const char* password = "pass";
const char* openai_token = null;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("On");
}

void loop() {
  
  Serial.println("Dectetando audio");
  String audioBase64 = capturaAudioBase64(); 

  String textoUsuario = enviarParaSTT(audioBase64);
  Serial.println(textoUsuario);

  String resposta = enviarParaGPT(textoUsuario);
  Serial.println(resposta);

  tocarAudioDaResposta(resposta);

  delay(10000);
}

String capturaAudioBase64() {
  return "AUDIO_EM_BASE64";
}


String enviarParaSTT(String audioBase64) {
  HTTPClient http;
  http.begin("https://api.openai.com/v1/audio/transcriptions");
  http.addHeader("Authorization", openai_token);
  http.addHeader("Content-Type", "multipart/form-data");

  return "Teste 123, responda '5'";
}



String enviarParaGPT(String texto) {
  HTTPClient http;
  http.begin("https://api.openai.com/v1/chat/completions");
  http.addHeader("Authorization", openai_token);
  http.addHeader("Content-Type", "application/json");

  String payload = "{\"model\": \"gpt-3.5-turbo\",\"messages\": [{\"role\": \"user\", \"content\": \"" + texto + "\"}]}";
  http.POST(payload);
  String resposta = http.getString();

  DynamicJsonDocument doc(1024);
  deserializeJson(doc, resposta);
  return doc["choices"][0]["message"]["content"].as<String>();
}

void tocarAudioDaResposta(String texto) {

  return "Por enquanto nada";
  

}
