graph TD
  App[App (Zentrale Steuerung)] -->|initialisiert| ProductDebug
  App -->|initialisiert| IndicatorFactory
  App -->|initialisiert| Battery
  App -->|initialisiert| Axis
  App -->|initialisiert| MQTTClient
  App -->|verarbeitet| CLI[Serielle CLI]
  App -->|verarbeitet| Timer
  ProductDebug -->|stellt bereit| CLIKommandos
  IndicatorFactory -->|erstellt| LedIndicator
  IndicatorFactory -->|erstellt| ServoPwrEnIndicator
  Battery -->|überwacht| Spannung
  Axis -->|steuert| Servo
  Axis -->|meldet| TargetReachedNotifier
  MQTTClient -->|kommuniziert| MQTTBroker
  CLI -->|steuert| App
  Timer -->|steuert| App