#Lesson 7

To build lesson 7, use the following commands in your serial terminal or ssh session.

```bash
g++ -I /usr/include/upm -lmraa -lupm-i2clcd -lump-adc121c021 -pthread -lboost_system -std=c++11 lesson_7.cpp relay.cpp -o thermostat
```