# language: en

Feature: System Configuration via WebServer
  As a user
  I want to access the configuration page of the ESP01 web server
  So that I can view and modify the system configuration values

  Background: 
    Given the ESP01 is connected to the Arduino via serial communication
    And the ESP01 web server is running
    And the communication between Arduino and ESP01 is serial communication  
    And the web system presents a textarea at the footer of all pages to display system messages, such as error logs
    And Every command sent by the ESP01 to Arduino that requires a response, and the response does not occur, 
    the ESP01 will send a log message "No communication with Arduino <CMD>" where CMD is the command sent

  Scenario: Viewing Current Configuration on the Configuration Page
    Given the user accesses the configuration page of the ESP01 web server
    When the ESP01 sends a "#CMD get config" request to the Arduino 
    And the Arduino receives the request
    Then the Arduino assembles a JSON with the current configuration values including:
      | field                  | example value | type | Range                  |
      | distMinimaAguaLago     | 4             | num  | < distMaximaAguaLago   |
      | distMaximaAguaLago     | 8             | num  | up to 100              |
      | distMinimaAguaFiltro   | 4             | num  | < distMaximaAguaFiltro |
      | distMaximaAguaFiltro   | 20            | num  | up to 100              |
      | ultrasonicFailLimit    | 10            | num  | 0 - 20                 |
      | pumpDelay              | 5000          | num  | 0 - 600000             |
      | ultrasonicReadInterval | 2000          | num  | 2000 - 60000           |
    And the Arduino sends the JSON to the ESP01 preceded by the response command "#CMD rsp config"
    And the ESP01 displays the configuration values on the configuration page in editable text boxes

  Scenario: Updating Configuration via the Configuration Page
    Given the user modifies one or more configuration values on the configuration page
    And system validates the data in the form according to the table
    Then system activates the submit button if data is correct, otherwise it reports the error next to the field
    When the user submits the updated configuration via the "/config" endpoint with a POST request
    And the ESP01 sends to Arduino a message with the command "#CMD set config <JSPconfig>"
    Then the Arduino updates the system configuration with the received values
    And responds with a success message to ESP01 with the command "#CMD ack config"
    And the ESP01 displays "Dados de configuração salvos no Arduino" in the system message log
    But if the Arduino fails to update the configuration
    Then the ESP01 displays message in the system message log
