# visor-drive
LOLIN D32 mit 3.7V LiPo-Akku steuert ein RC-Servos

Based on Skeleton Embedded Application ([wiring-skeleton](https://github.com/dniklaus/wiring-skeleton-wifi)) , powered by [PlatformIO](http://platformio.org "Cross-platform build system").

The project is configured to run on the following controller board:

* [LOLIN D32](https://www.wemos.cc/en/latest/d32/d32.html)


### Connect Terminal Emulation

In order to test and run the CLI commands, a terminal emulation program shall be used. The one giving you the best experience will be the [HTerm](http://www.der-hammer.info/terminal/). 

Load the _hterm-com10.cfg_ file (to be found in the project root directory) to configure HTerm properly. Alter the *COM10* accordingly to the one that has been selected on your computer.

## Debug Features
### Debug CLI Commands
#### Command Tree
    dbg                      Debug CLI root node
      tr                     Debug Trace Port config access
        heap                 Particular Trace Port (heap: see below in chapter Trace Port)
          out                Trace Output config access for the current trace port
            get              Show the assigned Trace Output
            set <outName>    Set a particular Trace Output name
            list             Show all available Trace Output names (& currently selected)
          lvl                Trace Level config access for the current trace port
            get              Show the current trace level
            set <level>      Set a particular trace level
            list             Show all available trace levels (& currenntly selected)
        led
          out
            ...
          lvl
            ...    
      wifi
      mqtt
      led                    Built in LED access
        set                  Set LED state (Usage: dbg led set [blink[ <blinkTimeMillis>]|on|off])
        pulse                Send a pulse  (Usage: dbg led pulse[ <pulseLengthMillis>])
      srvpwr                 Servo Power Enable.
        set                  Set the servo power enable (Usage: dbg srvpwr set [on|off])
      ax{0..3}               Axis debug commands.
        set                  (Usage: dbg ax<i> <angle> <velocity>; i: 0..3, angle: -90..90, velocity: 1..500)


#### Example commands
* `dbg tr heap lvl set debug`
* `dbg led set on`
* `dbg led set blink`


### Trace Port

|Trace Port|default level|functionality|
|----------|-------------|:------------|
|heap|info|if set to debug level: automatically print free heap memory [bytes], every 10 seconds|
|led |notice|used for _dbg led_ CLI commands print out (which level is defined as _alert_)|
|srvpwr|notice|used for _dbg srvpwr_ CLI commands print out (which level is defined as _alert_)|
|batt|notice|if set to debug level: automatically print battery status info, every 10 seconds|
|mqttctrl|||
|conmon|||
|mqttrx|||
|mqttled|||
|mqttdfltsub|||
|tax<0..3>|||
|ax<0..3>|||
