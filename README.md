# RpsRpi
## Measuring motor cycles per second with a Raspberry Pi 3 and IR-Emitter/IR-Receiver
This project is composed of two individual project parts combined to be able to measure and display the rounds per second of a revving motor. Bouncing and timeoverflow is configurable.

These two parts are available as branches:
* [RpsSQLiteNodejs](https://github.com/emmerlin1/RpsRpi/tree/RpsSQLiteNodejs)
* [rotational_speed](https://github.com/emmerlin1/RpsRpi/tree/rotational_speed)


![IR Receiver](images/ir_measurement.jpg)

The cycle rotation is measured by a IR-receiver applied with a 0.5W Infrared-LED which is interrupted by a black sliced disc. One rotation --> one rising/falling edge to compute.

![Rounds per Second](images/ir_receiver.png)

### First Part - QTProject
The first part of the project ([rotational_speed](https://github.com/emmerlin1/RpsRpi/tree/rotational_speed)
) is a QT-console-project measuring/computing the IR-signals and writing the results (rounds per second) to a SQLite-database. This git branch utilizes 3 threads and 2 fifo-queues within the QT-console-project. 

The first (high-priority) thread measures the timing of the IR-signal via wiringPi-ISR, the second computes the time values received and the third writes the corresponding SQLite-database entries.

### Second Part - NodeJS-Project with Express, ChartJS ...
The second part of this project ([RpsSQLiteNodejs](https://github.com/emmerlin1/RpsRpi/tree/RpsSQLiteNodejs)) visualizes the SQLite-Database entries in form of a ChartJS-Linechart. The Data is refreshed every 5 seconds, so each time 5 data entries will be added to the chart, because one entry corresponds to one second.

![Rounds per Second](images/rps_diagram.png)
