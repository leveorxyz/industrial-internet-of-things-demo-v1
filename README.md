# Industrial Internet of Things Demo

This demo is to demonstrate the real-time percentage of substances in a spherical or cylindrical container which would be transmitted to the server, and trigger SMS with info from Twilio, and other external data sources directly from the hardware layer.

## Build Instructions 

- From the Arduino IDE `1.8.9`, navigate to `Sktech` > `Include Library` > `Manage Libraries`
- Filter using `Firebase Arduino Client Library`
- Install the one by Mobizt, version `2.7.0`
- On the codebase,
  - Change the `WIFI_SSID` with yours
  - Change the `WIFI_PASSWORD` with yours
  - Change the `API_KEY` with yours
  - Change the `DATABASE_URL` with yours
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


