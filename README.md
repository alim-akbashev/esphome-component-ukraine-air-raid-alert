# `esphome-component-ukraine-air-raid-alert`

The `esphome-component-ukraine-air-raid-alert` is a binary sensor component for the esphome platform.
It allows you to check the current status of the Air Raid Alert in Ukraine using the official API
provided by https://api.ukrainealarm.com/.

## Limitations

* The component supports monitoring one region per sensor.
* An API token is required to use the component. You can request the token at https://api.ukrainealarm.com/.

## Status

* The component currently works on esp8266 devices. Support for esp32 is planned but not yet implemented.
*  It has been tested with esphome@2023.6.3 and is expected to work with previous versions as well,
but extensive testing hasn't been performed :)

## Example

For an example configuration, refer to the [air-raid-alert.yaml.example](air-raid-alert.yaml.example)
and [secrets.yaml.example](secrets.yaml.example).

Feel free to ask any questions or provide feedback if needed.

## Disclaimer
Please note that the esphome-component-ukraine-air-raid-alert is a third-party component developed by independent
contributors and is not officially affiliated with or endorsed by UkraineAlarm or any government organization.
The component relies on the availability and accuracy of the API provided by https://api.ukrainealarm.com/.
Therefore, the developers of this component cannot guarantee the reliability, accuracy, or timeliness of the
information retrieved from the API.

Additionally, it is important to understand that the Air Raid Alert status provided by the component may be subject
to delays, inaccuracies, or other technical issues beyond the control of the component developers.
Therefore, it is advisable to use this component for informational purposes only and not solely rely on it for
critical or life-saving decisions.

By using the esphome-component-ukraine-air-raid-alert, you acknowledge and accept the above-mentioned limitations 
and understand that the component developers cannot be held responsible for any consequences arising from the usage
of the component or reliance on the information provided by the API.
