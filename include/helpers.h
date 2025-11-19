#include <credentials.h>
#include <config.h>
#include <WiFi.h>

#include <HTTPClient.h>

bool postRequest()

{
    Serial.print("Posting to ");
    Serial.println(WiFi.status());
    HTTPClient http;
    http.begin(BELL_ADDRESS);
    Serial.println(BELL_ADDRESS);
    http.addHeader("x-api-key", API_KEY);
    int httpResponseCode = http.POST("");
    Serial.println("Ding Dong!");
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    http.end();
    return (httpResponseCode == 204);
}

bool connectWifi()

{
    Serial.print("Connecting to WiFi SSID: ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    WiFi.mode(WIFI_STA);

    int retry_count = 0;
    while (WiFi.status() != WL_CONNECTED && retry_count < RETRY_LIMIT)
    {
        delay(1000);
        Serial.print(".");
        WiFi.reconnect();
        retry_count++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("WiFi status: Connected");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        Serial.print("connect to ");
        Serial.println(WiFi.status());
    }

    return WiFi.status() == WL_CONNECTED;
}

void ringTheBell()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        connectWifi();
    }
    postRequest();
    delay(4000); // Simulate the bell ringing duration

    Serial.println("Bell Stopped.");
}