# <img src="https://github.com/RealRoti/bereal-predictor/assets/68821691/2ee58a72-a746-4e9c-8e9e-a751d58bcccd" width="50"> BeReal Algorithm Predictor ⚠

This script is a simple C++ program that predicts the next occurrence of a BeReal based on the provided event times. The program reads event times from specific files corresponding to different timezones and calculates the time difference between the current time and the last valid event time. The prediction considers events that occur between 9:00 AM and 11:59 PM.

**Disclaimer: this service is NOT official and not affiliated with BeReal. Data is collected and provided for educational purposes only.** 

## Before starting, there's a thing...

❌ At the moment, predictions can be made using **non-real-time updated historical data** (i.e., the timings in the /data folder). 

For testing purposes you can use the /data folder's file.

🔜 We'll implement an API that will update the timings in real-time soon.


## Requirements

- C++ compiler
- Windows operating system (due to the use of some Windows-specific commands)

## How to Use

1. Clone or download the repository from GitHub: [github.com/realroti/bereal-predictor](https://github.com/realroti/bereal-predictor)

2. Open a terminal or command prompt in the project directory.

3. Compile the C++ program using a C++ compiler. For example, with **g++**: `g++ bereal_predictor.cpp -o bereal_predictor`


4. Run the compiled executable:

`bereal_predictor`

5. The program will prompt you to select your timezone:

- `a) America`
- `b) Europe`
- `c) East Asia`
- `d) West Asia`

6. Enter the corresponding letter (a, b, c, or d) for your timezone and press Enter.

7. The program will then read the event times from the selected timezone's data file and determine the next BeReal event occurrence. It will display one of the following messages:

- If there is a valid BeReal event occurring today:
  ```
  The next BeReal event may occur <time-frame>.
  ```
  `<time-frame>` could be one of the following:
  - "in less than an hour"
  - "during the morning time frame"
  - "during the afternoon time frame"
  - "during the late afternoon time frame"

- If there are no valid BeReal events today:
  ```
  There are no valid BeReal events today.
  ```

- If there are no valid BeReal events in the past days:
  ```
  There are no valid BeReal events in the past days.
  ```

## Timezone Data Files

The program reads event times from specific data files based on the selected timezone. These files are stored in the "/data" folder, and they're named as follows: 

- `data/america.txt` for America timezone
- `data/europe.txt` for Europe timezone
- `data/eastasia.txt` for East Asia timezone
- `data/westasia.txt` for West Asia timezone

Each data file contain event times in the format "YYYY-MM-DD HH:MM:SS" separated by newlines.

‼ *Note: the system time and the timezone selected have to match, unless the prediction won't be accurate.*

## License

This program is open-source under the MIT License. You can find the full license text in the `LICENSE` file. Feel free to use, modify, and distribute the code as per the terms of the MIT License. Contributions to the project are also welcome!
