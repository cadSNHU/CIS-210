import re
import string
from collections import Counter

def ReadFile():
    file = open("file.txt", "r")

    user_file = file.readlines()
 
    for i in range(0, len(user_file)):
       user_file[i] = "".join(user_file[i]).rstrip()
    # Dictionary to hold the items and number of purchased in a key value 
    item_list = Counter(user_file)
    return item_list

def DailyReport():     # Prints a multiplication table, ten lines based on input number
    item_list = ReadFile();
    # Print Items and their purchase amounts to screen
    for item in item_list:
       print("{}: {}".format(item,item_list[item]))

      
def itemReport(item_name):      # Prints out a report based on user input (item name)
    item_dict = ReadFile()
    # Makes sure user inputs a valid item name or else returns -1
    try:
        item_detail_report = item_dict.get(item_name, -1)
    except:
        item_detail_report = -1
    return item_detail_report

def dailyReportExport():
    # Opens a file to wrie data to
    f = open("frequency.dat","w+")
    data_list = ReadFile();
    # Loops through a dict and writes each item and quantity to a new line in frequency.dict
    for item in data_list:
       f.write("{} {}\n".format(item,data_list[item]))
    # UI message, could probably move this into cpp file
    print("Now reading frequency.dat\n\n")
    f.close()



    
