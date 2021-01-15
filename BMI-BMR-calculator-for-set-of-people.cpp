#include<iostream>
#include<fstream>
#include<string>
#include<cmath>

using namespace std;
struct person {
    string name;
    int age;
    float weight;
    float height;
    string gender;
    float BMI;
    float BMR;
    string status;
};
int main()
{
    int N;
    do {
        cout << "please enter the number of people: \n";
        cin >> N;
    } while (N <= 0);

 
    person* index = new person[N];

    cout << "Enter data for each person individually separated by a space \n";
    cout << "The age in years, weight is in kilograms and height is in cm. \n";
    cout << "Name Age Weight Height Gender\n";
    for (int i = 0; i < N; i++)
    {
        cin >> index[i].name >> index[i].age >> index[i].weight >> index[i].height >> index[i].gender;
        if (index[i].age <= 0 || index[i].weight <= 0 || index[i].height <= 0 || (index[i].gender != "male" && index[i].gender != "female"))
        {
            cout << "you entered incorrect data for the #" << i + 1 << " person \n" << "please enter the data again \n";
            cin >> index[i].name >> index[i].age >> index[i].weight >> index[i].height >> index[i].gender;
        }
        if (index[i].gender == "male")
            index[i].BMR = 66 + 13.7 * index[i].weight + 5 * index[i].height - 6.8 * index[i].age;

        else
            index[i].BMR = 655 + 9.6 * index[i].weight + 1.8 * index[i].height - 4.7 * index[i].age;

        index[i].BMI = index[i].weight / (pow(index[i].height / 100, 2));

        if (index[i].BMI < 18.5)
            index[i].status = "underweight";
        else if (index[i].BMI > 25)
            index[i].status = "overweight";
        else
            index[i].status = "optimal";
    }
    ofstream file;
    file.open("Output data.txt");
    cout << "A file with all data is saved to the program's directory \n";

    for (int i = 0; i < N; i++)
    {
        file << "person #" << i + 1 << " data \n";
        file << "name: " << index[i].name << endl << "age: " << index[i].age << endl << "weight: " << index[i].weight << endl << "height: " << index[i].height << endl << "gender: " << index[i].gender << endl;
        file << "BMR: " << index[i].BMR << endl << "BMI: " << index[i].BMI << endl << "weight status: " << index[i].status << endl << "__________________________ \n";
    }

    cout << "Highest BMI values: \n";
    file << "Highest BMI values: \n";
    int counter = 0;
    for (int i = 0; i < N; i++)
    {
        if (index[i].status == "overweight")
        {
            cout << "person #" << i + 1 << " is overweight with a BMI value of: " << index[i].BMI << endl;
            file << "person #" << i + 1 << " is overweight with a BMI value of: " << index[i].BMI << endl;
            counter++;
        }
    }
    float highest = index[0].BMI; int j;

    if (counter == 0)
    {
        for (j = 0; j < N; j++)
            if (index[j].BMI > highest)
                highest = index[j].BMI;
    }
    if (counter == 0)
    {
        cout << "No overweight people but the person #" << j + 1 << " has the highest BMI value which is: " << highest << endl;
        file << "No overweight people but the person #" << j + 1 << " has the highest BMI value which is: " << highest << endl;
    }
    cout << "__________________________ \n";
    file << "__________________________ \n";
    float total_male_BMR = 0, total_female_BMR = 0;
    int num_male = 0, num_female = 0;

    for (int i = 0; i < N; i++)
    {
        if (index[i].status == "optimal" && index[i].gender == "male")
        {
            total_male_BMR += index[i].BMR;
            num_male++;
        }
        else if (index[i].status == "optimal" && index[i].gender == "female")
        {
            total_female_BMR += index[i].BMR;
            num_female++;
        }
    }
    if (num_female != 0)
    {
        float avg_BMR_female = total_female_BMR / num_female;

        cout << "the average BMR for females of optimal weight is: " << avg_BMR_female << endl;
        file << "the average BMR for females of optimal weight is: " << avg_BMR_female << endl;
    }
    else
    {
        cout << "there are no females with optimal weight \n";
        file << "there are no females with optimal weight \n";
    }
    if (num_male != 0)
    {

        float avg_BMR_male = total_male_BMR / num_male;

        cout << "the average BMR for males of optimal weight is: " << avg_BMR_male << endl;
        file << "the average BMR for males of optimal weight is: " << avg_BMR_male << endl;
    }
    else
    {
        cout << "there are no males with optimal weight \n";
        file << "there are no males with optimal weight \n";
    }

    file.close();
    delete[] index;
    return 0;
}