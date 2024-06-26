# language: en

Feature: Displaying System Status on HomePage
  As a user
  I want to access the homepage of the ESP01 web server
  So that I can see the updated current status of the water level system

  Background:
    Given the ESP01 is connected to the Arduino via serial communication
    And the ESP01 web server is running
    And the web system presents a textarea at the footer of all pages to display system messages, such as error logs

  Scenario: User Accesses HomePage to View System Status
    When the user accesses the homepage of the ESP01 web server
    Then the ESP01 sends a "#CMD get status" request to the Arduino via serial communication
    And the Arduino receives the request
    And the Arduino assembles a JSON with the current status values including:
      | field                  | example value | type | Range                  |
      | distMinimaAguaLago     | 4             | num  | < distMaximaAguaLago   |
      | distMaximaAguaLago     | 8             | num  | up to 100              |
      | distMinimaAguaFiltro   | 4             | num  | < distMaximaAguaFiltro |
      | distMaximaAguaFiltro   | 20            | num  | up to 100              |
      | ultrasonicFailLimit    | 10            | num  | 0 - 20                 |
      | pumpDelay              | 5000          | num  | 0 - 600000             |
      | ultrasonicReadInterval | 2000          | num  | 2000 - 60000           |
      | pumpLakeStatus         | On            | text | On - Off               |
      | pumpFilterStatus       | On            | text | On - Off               |
      | lakeLevel              | 15            | num  |                        |
      | filterLevel            | 14            | num  |                        |
    And the Arduino sends the JSON to the ESP01 preceded by the response command "#CMD rsp status <JSON_Data>"
    And the ESP01 updates local values with the received JSON
    And the ESP01 displays the system status on the homepage based on the received JSON

  Scenario: Handling No Response from Arduino
    Given the user triggers a command that requires a response from the Arduino
    When the ESP01 sends the command "<CMD>" to the Arduino via serial communication
    And the ESP01 does not receive a response after a specified timeout
    Then the ESP01 includes an error message in the log "No communication with Arduino <CMD>"
