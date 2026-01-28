#include <iostream>
#include <vector>
#include <filesystem>
#include <string>
#include <random>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

struct Person
{
    string name;
    double age;
};

void generate_data()
{
    /*
        Function: generate_data
        Purpose : Generates synthetic CSV datasets containing random (name, age)
                  records for multiple input sizes and instances.

        Approach:
          - Uses predefined name and age pools.
          - Randomly selects names and ages using Mersenne Twister.
          - Creates a directory named "datasets".
          - For n = 10 to 100 (step 10), generates 10 CSV files per n.
          - Each file contains n randomly generated records.

        Output:
          - CSV files stored in the "datasets" directory.
          - File format: name,age
    */

    // Pool of names and ages for random selection
    vector<string> names = {"Reeta", "Hemant", "Pankaj", "Suman", "Ritam", "Raj", "Ayan", "Iradri", "Abhinav", "Shivashish"};
    vector<double> ages = {28.7, 26.2, 27.6, 27.5, 20.1, 27.5, 28.8, 21.1, 25.7, 22.6, 26.3, 25.4, 29.2, 23.4, 24.1, 26.1};

    // random_device uses hardware entropy (if available). Prevents predictable sequences
    random_device rd;
    mt19937_64 gen(rd());

    // Uniform distribution for selecting random indices
    uniform_int_distribution<int> random_name(0, names.size() - 1); // Produces random integer values i, uniformly distributed on the closed interval [min, max]
    uniform_int_distribution<int> random_age(0, ages.size() - 1);

    // Create directory to store generated datasets (requires C++17 or higher)
    fs::create_directory("datasets");

    for (int n = 10; n < 101; n = n + 10)
    {
        for (int run = 1; run < 11; run++)
        {
            string file_name = "datasets/R_No_20_P1_IradriDas_dataset_n" + to_string(n) + "_instance_" + to_string(run) + ".csv";
            ofstream fout(file_name);
            fout << "name,age\n"; // heading for the csv file

            for (int c = 0; c < n; c++)
            {
                double age = ages[random_age(gen)];
                string record = names[random_name(gen)] + "," + to_string(age) + "\n";
                fout << record;
            }
        }
    }
}

void write_sorted_records_to_CSV(vector<Person> record, int n, int run, const string directory)
{
    /*
        Function: write_sorted_records_to_CSV
        Purpose : Writes sorted Person records to a CSV file.

        Params  :
          - record    : vector containing sorted Person records
          - n         : number of records in the dataset
          - run       : instance number of the dataset
          - directory : directory path where the CSV file will be stored

        Output:
          - A CSV file named according to dataset size and instance number.
          - File format: name,age
    */

    string file_name = directory + "/R_No_20_P1_IradriDas_sorted_dataset_n" + to_string(n) + "_instance_" + to_string(run) + ".csv";
    ofstream fout(file_name);
    fout << "name,age\n"; // heading for the csv file

    for (int i = 0; i < record.size(); i++)
    {
        // Convert Person object to CSV row format
        string entry = record[i].name + "," + to_string(record[i].age) + "\n";

        fout << entry;
    }
}

vector<Person> read_records_from_CSV(const string &filename)
{
    /*
        Function: read_records_from_CSV
        Purpose : Reads Person records from a CSV file and stores them in a vector.

        Params  :
          - filename : path to the CSV file to be read

        Returns :
          - A vector of Person objects populated from the CSV file.
          - Returns an empty vector if the file cannot be opened.

        Approach:
          - Opens the CSV file using an input file stream.
          - Skips the header line.
          - Parses each subsequent line to extract name and age fields.
          - Converts age from string to double before storing.
    */

    vector<Person> record;   // Stores parsed Person records
    ifstream file(filename); // Input file stream for CSV file
    string line;             // Holds each line read from the file

    // Check if file opened successfully
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return record;
    }

    getline(file, line); // skip header

    while (getline(file, line))
    {
        stringstream ss(line); // Stream to parse CSV line

        string name, ageStr;
        getline(ss, name, ',');
        getline(ss, ageStr, ',');
        record.push_back({name, stod(ageStr)});
    }

    return record;
}

void insertionSort_byAge(vector<Person> &list, long long &compare_counter, long long &assign_counter)
{
    int n = list.size();

    for (int i = 1; i < n; i++)
    {
        Person key = list[i];
        assign_counter++;

        int prevIndex = i - 1;

        while (prevIndex >= 0)
        {
            compare_counter++;
            if (list[prevIndex].age > key.age)
            {
                list[prevIndex + 1] = list[prevIndex];
                assign_counter++;
                prevIndex--;
            }
            else
            {
                break;
            }
        }
        list[prevIndex + 1] = key;
        assign_counter++;
    }
}

void insertionSort_byName(vector<Person> &list, long long &compare_counter, long long &assign_counter)
{
    int n = list.size();

    for (int i = 1; i < n; i++)
    {
        Person key = list[i];
        assign_counter++;
        int prevIndex = i - 1;

        while (prevIndex >= 0)
        {
            compare_counter++;
            if (list[prevIndex].name > key.name)
            {
                list[prevIndex + 1] = list[prevIndex];
                assign_counter++;
                prevIndex--;
            }
            else
            {
                break;
            }
        }
        list[prevIndex + 1] = key;
        assign_counter++;
    }
}

void insertionSort_byAge_Name(vector<Person> &list, long long &compare_counter, long long &assign_counter)
{
    // At first sorting on the basis of age then by name so that the ordering on age is maintained
    insertionSort_byAge(list, compare_counter, assign_counter);
    insertionSort_byName(list, compare_counter, assign_counter);
}

int main()
{

    vector<Person> record1;
    record1.push_back({"Reeta", 18.5});
    record1.push_back({"Geeta", 18.3});
    record1.push_back({"Reeta", 17.3});

    long long comp_counter_age = 0;
    long long assign_counter_age = 0;

    insertionSort_byAge(record1, comp_counter_age, assign_counter_age);

    for (auto &&p : record1)
    {
        cout << p.name << " " << p.age << endl;
    }

    cout << "Comparision: " << comp_counter_age << endl;
    cout << "Assignment: " << assign_counter_age << endl
         << endl;

    vector<Person> record2;
    record2.push_back({"Reeta", 18.5});
    record2.push_back({"Geeta", 18.3});
    record2.push_back({"Reeta", 17.3});

    long long comp_counter_name = 0;
    long long assign_counter_name = 0;

    insertionSort_byName(record2, comp_counter_name, assign_counter_name);

    for (auto &&p : record2)
    {
        cout << p.name << " " << p.age << endl;
    }

    cout << "Comparision: " << comp_counter_name << endl;
    cout << "Assignment: " << assign_counter_name << endl
         << endl;

    vector<Person> record3;
    record3.push_back({"Reeta", 18.5});
    record3.push_back({"Geeta", 18.3});
    record3.push_back({"Reeta", 17.3});

    long long comp_counter_age_name = 0;
    long long assign_counter_age_name = 0;

    insertionSort_byAge_Name(record3, comp_counter_age_name, assign_counter_age_name);

    for (auto &&p : record3)
    {
        cout << p.name << " " << p.age << endl;
    }

    cout << "Comparision: " << comp_counter_age_name << endl;
    cout << "Assignment: " << assign_counter_age_name << endl
         << endl;

    return 0;
}