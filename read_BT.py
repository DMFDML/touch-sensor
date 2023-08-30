import threading # for threading
import serial.tools.list_ports # for listing ports
import read_serial_func # for reading serial data

def process_data(data): # process data
    return data == "1" # return True if data is 1, else False

def read_serial_and_update(): # read serial data and update
    b1 = False # button 1
    # read serial data
    for data in read_serial_func.read_serial_func(COM_PORT, BAUD_RATE):
        b1 = True if process_data(data) else False # true if data == 1
        print(b1) # print button 1

# if run directly
if __name__ == "__main__":
    COM_PORT = 'COM6' # COM port (see github readme for help)
    BAUD_RATE = 9600 # baud rate

    # Setting the thread as a daemon means that the thread will automatically 
    # exit when the main program (or main thread) finishes. Daemon threads are 
    # generally used for background tasks that shouldn't block the program from 
    # exiting.
    update_thread = threading.Thread(target=read_serial_and_update)
    update_thread.daemon = True
    update_thread.start()
    update_thread.join()
