Go to File Editor Add-Ons and then do the following changes

### /homeassistant/configuration.yaml
mqtt: !include mqtt.yaml

### /homeassistant/mqtt.yaml
sensor:
  - name: "Temperature"
    state_topic: "sensors/device001"
    unit_of_measurement: "°C"
    value_template: "{{ value_json.temperature }}"

  - name: "Humidity"
    state_topic: "sensors/device001"
    unit_of_measurement: "%"
    value_template: "{{ value_json.humidity }}"