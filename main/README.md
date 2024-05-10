# _The following is a README file explaining how to run my code:_

## Collecting the gesture data
The data was collected using the MPU 6050 which was connected to my esp. The code to take measurements from the MPU can be found in the main.c file. In order to automatically take these measurements and put them into folders on my computer, the script.py file must be running at the same time.

Here are the steps of how to collect data using the python script:

1. Build and flash the main.c file WITHOUT monitoring it in the terminal. Do not bother moving the mpu at this time, this is just so that the code is loaded onto the esp.

2. Once the terminal states that the code has finished running, run the python script. The script will tell you that you are to perform the up gesture.

3. At this time, press the restart button on the esp 32 s3. This will re-flash the program on the esp without loading the program onto the esp again. (this is important, the python script will get confused if you have to load it again)

4. Perform the gestures as instructed. You will see the data being logged in the terminal and instructions in the terminal. Results are saved as csv files in the folder titled gesture_data


## Creating the plots
The creation of the plots was simple and can be found in the python file named plotMaker.py which is in the gesture_plots folder. In the gesture_plots folder, you will also find a plots folder, which holds the plots for each of the selected gestures.