#include <bits/stdc++.h>
using namespace std;

class ParkingLot
{
    int slots;
    priority_queue<int, vector<int>, greater<int>> availableSlots;
    unordered_map<int, vector<string>> ageToPlates;
    unordered_map<int, pair<string, int>> slotToPlateAndAge;
    unordered_map<int, vector<int>> ageToSlots;
    unordered_map<string, int> plateToSlot;

public:
    ParkingLot(int n)
    {
        slots = n;
        for (int i = 1; i <= slots; i++)
        {
            availableSlots.push(i);
        }
    }

    string parkVehicle(string plateNumber, int age)
    {
        if (availableSlots.size() <= 0)
            return "Parking lot full";
        int slot = availableSlots.top();
        availableSlots.pop();
        plateToSlot[plateNumber] = slot;
        ageToPlates[age].push_back(plateNumber);
        ageToSlots[age].push_back(slot);
        slotToPlateAndAge[slot] = make_pair(plateNumber, age);
        return "Car with vehicle registration number '" + plateNumber + "' has been parked at slot number " + to_string(slot);
    }

    void deleteSlotFromAgeToSlots(int slot, vector<int> &removeElementFromVector)
    {
        for (auto it = removeElementFromVector.begin(); it != removeElementFromVector.end(); ++it)
        {
            if ((*it) == slot)
            {
                removeElementFromVector.erase(it);
                return;
            }
        }
    }

    void deletePlateFromAgeToPlates(string plate, vector<string> &removeElementFromHere)
    {
        for (auto it = removeElementFromHere.begin(); it != removeElementFromHere.end(); ++it)
        {
            if ((*it) == plate)
            {
                removeElementFromHere.erase(it);
                return;
            }
        }
    }

    string emptyTheSpot(int slot)
    {
        if (slotToPlateAndAge.find(slot) == slotToPlateAndAge.end())
        {
            return "No vehicle is parked in this slot.";
        }
        availableSlots.push(slot);
        string registrationPlate = slotToPlateAndAge[slot].first;
        int driverAge = slotToPlateAndAge[slot].second;
        slotToPlateAndAge.erase(slot);
        plateToSlot.erase(registrationPlate);
        deleteSlotFromAgeToSlots(slot, ageToSlots[driverAge]);
        deletePlateFromAgeToPlates(registrationPlate, ageToPlates[driverAge]);
        return "Slot number " + to_string(slot) + " vacated, the car with vehicle registration number '" + registrationPlate + "' left the space, the driver of the car was of age " + to_string(driverAge);
    }

    vector<string> getPlateForGivenAge(int age)
    {
        vector<string> output;
        if (ageToPlates.find(age) == ageToPlates.end())
            return output;
        return ageToPlates[age];
    }

    vector<int> getAllSlotsForGivenAge(int age)
    {
        vector<int> output;
        if (ageToPlates.find(age) == ageToPlates.end())
            return output;
        return ageToSlots[age];
    }

    int getSlotFromPlate(string plateNumber)
    {
        if(plateToSlot.find(plateNumber)==plateToSlot.end())
            return 0;
        return plateToSlot[plateNumber];
    }
};

vector<string> executeIndividualTasks()
{
    vector<string> outputFile;
    fstream readInputFile;
    readInputFile.open("input.txt", ios::in);
    string task;
    ParkingLot *parkingLot = NULL;
    while (getline(readInputFile, task))
    {
        string individualTask;
        stringstream iss(task);
        while (iss >> individualTask)
        {
            if (individualTask == "Create_parking_lot")
            {
                iss >> individualTask;
                ParkingLot *temp = new ParkingLot(stoi(individualTask));
                parkingLot = temp;
                cout<<"Created parking of " + individualTask + " slots"<<endl;
                outputFile.push_back("Created parking of " + individualTask + " slots");
            }
            else if (individualTask == "Park")
            {
                iss >> individualTask;
                string registrationPlate = individualTask;
                iss >> individualTask;
                iss >> individualTask;
                int ageOfDriver = stoi(individualTask);
                string output = parkingLot->parkVehicle(registrationPlate, ageOfDriver);
                cout<<output<<endl;
                outputFile.push_back(output);
            }
            else if (individualTask == "Slot_numbers_for_driver_of_age")
            {
                iss >> individualTask;
                vector<int> slots = parkingLot->getAllSlotsForGivenAge(stoi(individualTask));
                int slotSize = slots.size();
                if (!slotSize)
                {
                    cout<<"No such vehicle in the lot."<<endl;
                    outputFile.push_back("No such vehicle in the lot.");
                    continue;
                }
                string outStr = "";
                for (int i = 0; i < slotSize; i++)
                {
                    outStr += to_string(slots[i]);
                    if (i != slotSize - 1)
                        outStr += ",";
                }
                cout<<outStr<<endl;
                outputFile.push_back(outStr);
            }
            else if (individualTask == "Slot_number_for_car_with_number")
            {
                iss >> individualTask;
                int slot = parkingLot->getSlotFromPlate(individualTask);
                if (!slot)
                {
                    cout<<"No such vehicle in the parking lot."<<endl;
                    outputFile.push_back("No such vehicle in the parking lot.");
                }
                else
                {
                    cout<<to_string(slot)<<endl;
                    outputFile.push_back(to_string(slot));
                }
            }
            else if (individualTask == "Leave")
            {
                iss >> individualTask;
                int spotToBeEmptied = stoi(individualTask);
                string output = parkingLot->emptyTheSpot(spotToBeEmptied);
                cout<<output<<endl;
                outputFile.push_back(output);
            }
            else if (individualTask == "Vehicle_registration_number_for_driver_of_age")
            {
                iss >> individualTask;
                vector<string> registrationNumbers = parkingLot->getPlateForGivenAge(stoi(individualTask));
                int RNVectorSize = registrationNumbers.size();
                if (!RNVectorSize)
                {
                    cout<<"No such vehicle in the lot."<<endl;
                    outputFile.push_back("No such vehicle in the lot.");
                    continue;
                }
                string outStr = "";
                for (int i = 0; i < RNVectorSize; i++)
                {
                    outStr += registrationNumbers[i];
                    if (i != RNVectorSize - 1)
                        outStr += ",";
                }
                cout<<outStr<<endl;
                outputFile.push_back(outStr);
            }
            else
                cout<<"Exceptional task."<<endl;
                outputFile.push_back("Exceptional task.");
        }
    }
    readInputFile.close();
    return outputFile;
}

void setOutputFile(vector<string> output)
{
    std::ofstream outputFile("output.txt");
    std::ostream_iterator<std::string> outputIterator(outputFile, "\n");
    std::copy(output.begin(), output.end(), outputIterator);
    return;
}

int main()
{
    cout << "######################## PARKING LOT ########################" << endl;
    cout << "Note: input.txt(case sensetive) should be in same folder." << endl;
    vector<string> outputFile;
    outputFile = executeIndividualTasks();
    setOutputFile(outputFile);
    cout <<endl<<"P.s: An output file has also been made for download.";
    return 0;
}