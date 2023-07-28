# Industrial Internet of Things Demo

This demo is to demonstrate the real-time percentage of substances in a spherical or cylindrical container which would be transmitted to the server, and trigger SMS with info from Twilio, and other external data sources directly from the hardware layer.

## Build Instructions 

- From the Arduino IDE `1.8.9`, navigate to `Sktech` > `Include Library` > `Manage Libraries`
- Filter using `Firebase Arduino Client Library`
- Install the one by Mobizt, version `2.7.0`
- On the codebase, update network credentials & RTDB credentials:
  - Change the `WIFI_SSID` with yours
  - Change the `WIFI_PASSWORD` with yours
  - Change the `API_KEY` with yours
  - Change the `DATABASE_URL` with yours
- Update `sendDataIntervalMillis`, currently it's set as `10000` which means it sends/stores data to RTDB every 10 seconds
- The codebase on `setup()`:
  - connects the WiFi on the ESP32 to the WiFi Router/Hotspot
  - signs up using `FirebaseAuth` and `FirebaseConfig`
  - assigns the callback function for the long-running token generation task
- The code on `loop()`:
  - generates random values as ints & floats
  - sends/stores those int & float to the database path `Test/random_Float_Val`
- Ensure your setup/IDE has selected the correct ones, i.e. `ESP32 Dev Module` as `Board`
  
## CHANGELOG v1 

### Database Details
- Location: `Singapore (asia-southeast1)`
- Database options: Test mode. **TODO:** Update my security rules within 30 days from 28JUL2023, which is `2023-8-28`
- Database rules:

```json
{
  "rules": {
    ".read": "now < 1693159200000",  // 2023-8-28
    ".write": "now < 1693159200000",  // 2023-8-28
  }
}
```