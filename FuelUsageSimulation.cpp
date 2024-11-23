/*
 *Fuel Sim
 *Version 1.0
 *Written by Brandon Kelly(CLion reindented the code for readbility sake)
    */
//Preprocessing Commands
#include <iostream>
#include <string>
#include <vector>
#include <limits>

//Remove need for std:: for function in standard library
using namespace  std;
//Declaration of variables. All values are default values but can be updated at runtime by the user.
int fuel_consumption = 3;//Define the fuel consumption variable. This is units of liters of fuel per trip
int gasTankSize = 5;
int segSize = 10;
int totalFuel = 0;
bool valid_input;//Boolean value to help validate inputs
//Creation of vectors
vector<int> gasTank;//Using vector so that the user can redefine at runtime, otherwise would have used array
vector<int> oldGasTank;//Used to store previous state of gasTank vector for certain

//Main Function
int main() {

    //Welcome String to greet user
    cout<<"Welcome to: \n ______          _    _____ _          \n|  ____|        | |  / ____(_)         \n| |__ _   _  ___| | | (___  _ _ __ ___  \n|  __| | | |/ _ \\ |  \\___ \\| | '_ ` _ \\   \n| |  | |_| |  __/ |  ____) | | | | | | |\n|_|   \\__,_|\\___|_| |_____/|_|_| |_| |_|";
    //Request for user to give fuel consumption per trip. This assumed to be constant for every trip
    cout << "\n Please give the anticipated fuel consumed during a trip. Press Enter for default value of 3 liters" <<
            endl;
    //Following loop recieves user input and validates it.
    do  {
        valid_input=true;
        if (cin.peek() == '\n')
        //Handles Empty line. Keeps the default value.
        //Reference found here:https://stackoverflow.com/questions/10314682/user-inputcin-default-value
        {
            fuel_consumption = 3;
            cout << "Setting Fuel Consumption to 3 liters" <<endl;
        } else if (!(cin >> fuel_consumption)) //Checks type compatibility
        {
            //Causes the loop to iterate again
            valid_input=false;
            cout << "It appears you have entered something other than a number. Please try again!" <<endl<<
                    "Please give the anticipated fuel consumed during a trip. Press Enter for default value of 3 liters"
                    << endl;
        }
        //Clears input buffer
        cin.clear();//Clears input buffer: https://stackoverflow.com/questions/22122337/while-loop-skipping-cin
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }while (valid_input == false);
    //Same process as above but for configuring how many fuel tank segments are used.
    cout << "How many segments do you want your fuel tank to be? Press Enter for a default value of 5 segments"<<endl;
    do  {
        valid_input=true;
        if (cin.peek() == '\n')
        //Handles Empty line. Reference found here:https://stackoverflow.com/questions/10314682/user-inputcin-default-value
        {
            cout << "Setting Fuel Tank size to 5 segments"<< endl;

        }
        else if (!(cin >> gasTankSize)) //Checks type
        {

            valid_input=false;
            cout << "It appears you have entered something other than a number. Please try again!" <<endl<<
                    "How many segments do you want your fuel tank to be? Press Enter for a default value of 5 segments"
                    << endl;
        }
        cin.clear();//Clears input buffer: https://stackoverflow.com/questions/22122337/while-loop-skipping-cin
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }while (valid_input == false);
    //Same process for selecting how large each segment should be.
    cout << "How much should each segments be filled to? Press Enter for a default value of 10 liters"<<endl;
    do  {
        valid_input=true;
        if (cin.peek() == '\n')//Handles Empty line. Reference found here:https://stackoverflow.com/questions/10314682/user-inputcin-default-value
        {
            cout << "Filling each segment to 10 liters";
        } else if (!(cin >> segSize)) //Checks type
        {

            valid_input=false;
            cout << "It appears you have entered something other than a number. Please try again!" <<endl<<
                    "How much should each segments be filled to ? Press Enter for a default value of 10 liters"
                    << endl;
        }
        cin.clear();//Clears input buffer: https://stackoverflow.com/questions/22122337/while-loop-skipping-cin
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }while (valid_input == false);
    for(int i=0; i < gasTankSize; i++)//For loop. Since we index at 0, we can use '<' operator to fill the vector
    {
        gasTank.push_back(segSize);//Adds items to arry
    }
    //Returns information about the fuel tank.
    cout << "Gas Tank Size: " << gasTank.size() <<" segments"<< endl;
    cout << "Calculating total fuel in tank"<<endl;
    //Calculates the full amount of fuel in the tank and then returns it to the user with the next text output
    for (int i=0; i<gasTank.size();i++)
    {
        totalFuel += gasTank[i];
    }
    //Begins trip with message
    cout << "Total Current Fuel is " << totalFuel << " liters" << endl << "Starting Trip!"<< endl;
    for (int tripNum=0;tripNum<10;tripNum++)
    {
        cout<<"------Trip Number "<< tripNum + 1 << "------"<<endl;
        totalFuel=0;//Sets the totalFuel number to zero for purposes of the loop
        static int currentSeg=0; //static(so it persists after loop ends) integer used to track what segment is being used.
        gasTank[currentSeg]-=fuel_consumption;//Subtracts the fuel burned
    fuel_drain://Label for goto since I didn't want to rewrite the following code as a recursive function...Probably bad practice
        if (gasTank[currentSeg]<1)
        {
            if (currentSeg == gasTankSize-1)
            {
                cout << "________________________________" << endl << "Out of Fuel! Please Refill!" << endl << "You completed " << tripNum <<" trips before running out of fuel";
                break;
            }
            currentSeg++;
            gasTank[currentSeg]+= gasTank[currentSeg-1];
            gasTank[currentSeg-1] = 0;
            goto fuel_drain;
            //Before, code could cause the next segment to go negative which would not be processed
            //until the loop ran again. This forces the loop to run again if a segment drops below zero so that it can
            //catch these cases. Example:Fuel consumption is 20, seg size is 10. Before fuel tank looks like 0 -10 10.
            //This fixes that
            //Probably should be a recursive function but this was faster to write and handles it well
        }
        //Calculates total remaining gas
        for (int i=0; i<gasTank.size();i++)
        {
            totalFuel += gasTank[i];
        }
        cout << "Total Current Fuel is " << totalFuel << " liters" <<endl;
        //Outputs each fuel tanks amount of remaining fuel
        for(int i=0; i < gasTank.size(); i++)//For loop. Since we index at 0, we can use '<' operator
        {
            cout << gasTank[i] << " ";
        }
        //Creates newline at end of program
        cout << endl;
    }
    //Finishes program
    return 0;
}
