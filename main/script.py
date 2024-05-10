import serial
port = '/dev/cu.usbserial-1120'


ser = serial.Serial(port, 115200)

#Open data.txt file if it exists, if not create it


movements = ['up', 'down', 'left', 'right']
maxLinesPerFile = 1001 #column names + readings
numFilesPerMovement = 21

for movement in movements: #read measurements for all gestures
    print('NEW MOVEMENT: ' , movement)
    for fileNum in range(numFilesPerMovement): #read measurements for that gesture type
        
        storageFile = 'gesture_data/' + str(movement) + '_gestures/' + str(movement) + '_' + str(fileNum) + '.csv'
        myFile = open(storageFile, 'w')
            
        readLineNum = 0
        fileStarted = False
        while readLineNum < maxLinesPerFile: #read measurements for that exact gesture

            data = ser.readline()
            print(data)

            #convert data to string and write to file
            data = data.decode('utf-8')
            if not fileStarted and "Time,acce_x,acce_y,acce_z,gyro_x,gyro_y, gyro_z" in data:
                fileStarted = True
            
            if fileStarted:
                myFile.write(data)
                readLineNum += 1
        
        print('done reading for gesture')
        myFile.close()


print("done")


'''
adjust for drone:

be reading input
at the same time, be making a guess of what the gesture is
when you recognize what the gesture is
    call the appropriate drone movement function

'''