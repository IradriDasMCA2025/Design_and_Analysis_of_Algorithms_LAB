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

    vector<string> names = {"Reeta", "Hemant", "Pankaj", "Suman", "Ritam", "Raj", "Ayan", "Iradri", "Abhinav", "Shivashish"};

    // random_device uses hardware entropy (if available). Prevents predictable sequences
    random_device rd;
    mt19937_64 gen(rd());

    uniform_int_distribution<int> random_name(0, names.size() - 1); // Produces random integer values i, uniformly distributed on the closed interval [min, max]
    uniform_real_distribution<double> random_age(20.0, 30.0);       // Produces random floating-point values x, uniformly distributed on the interval [min, max)

    fs::create_directory("datasets"); // c++ 17

    for (int n = 10; n < 101; n = n + 10)
    {
        for (int run = 1; run < 11; run++)
        {
            string file_name = "datasets/IS20_IradriDas_dataset_n" + to_string(n) + "_instance_" + to_string(run) + ".csv";
            ofstream fout(file_name);
            fout << "name,age\n"; // heading for the csv file

            for (int c = 0; c < n; c++)
            {
                double age = random_age(gen);
                // If the fractional part is less than 0.5, round() returns the previous integer.
                // If the fractional part is greater or equal to 0.5, round() returns the next integer.
                age = round(age * 10.0) / 10.0;

                string record = names[random_name(gen)] + "," + to_string(age) + "\n";
                fout << record;
            }
        }
    }
}

void write_sorted_records_to_CSV(vector<Person> record, int n, int run, const string directory)
{

    string file_name = directory + "/IS20_IradriDas_sorted_dataset_n" + to_string(n) + "_instance_" + to_string(run) + ".csv";
    ofstream fout(file_name);
    fout << "name,age\n"; // heading for the csv file

    for (int i = 0; i < record.size(); i++)
    {
        string entry = record[i].name + "," + to_string(record[i].age) + "\n";
        fout << entry;
    }
}

vector<Person> read_records_from_CSV(const string &filename)
{
    vector<Person> record;
    ifstream file(filename);
    string line;

    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return record;
    }

    getline(file, line); // skip header

    while (getline(file, line))
    {
        stringstream ss(line);
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

    insertionSort_byAge(list, compare_counter, assign_counter);
    insertionSort_byName(list, compare_counter, assign_counter);

    // int n = list.size();

    // for (int i = 1; i < n; i++)
    // {
    //     Person key = list[i];
    //     assign_counter++;

    //     int prevIndex = i - 1;

    //     while (prevIndex >= 0)
    //     {
    //         compare_counter++;
    //         if (list[prevIndex].age > key.age)
    //         {
    //             list[prevIndex + 1] = list[prevIndex];
    //             assign_counter++;
    //             prevIndex--;
    //         }
    //         else if (list[prevIndex].age == key.age)
    //         {

    //             if (list[prevIndex].name > key.name)
    //             {
    //                 list[prevIndex + 1] = list[prevIndex];
    //                 assign_counter++;
    //                 prevIndex--;
    //             }
    //             else
    //             {
    //                 break;
    //             }
    //         }
    //         else
    //         {
    //             break;
    //         }
    //     }
    //     list[prevIndex + 1] = key;
    //     assign_counter++;
    // }
}

int main()
{
    generate_data();

    string directory;

    // <a> write a function to sort on age
    directory = "results_for_InsertionSort_byAge";
    fs::create_directory(directory);

    ofstream out_age("IS20_IradriDas_results_age.csv");
    out_age << "n,avg_comparisons,avg_assignment\n";

    for (int n = 10; n <= 100; n = n + 10)
    {
        long double totalComparisons = 0;
        long double totalAssignment = 0;
        for (int run = 1; run <= 10; run++)
        {
            string file_name = "datasets/IS20_IradriDas_dataset_n" + to_string(n) + "_instance_" + to_string(run) + ".csv";
            vector<Person> record = read_records_from_CSV(file_name);

            long long comp_counter = 0;
            long long assign_counter = 0;
            insertionSort_byAge(record, comp_counter, assign_counter);
            totalComparisons += comp_counter;
            totalAssignment += assign_counter;

            write_sorted_records_to_CSV(record, n, run, directory);
        }

        out_age << n << "," << (totalComparisons / 10.0) << "," << (totalAssignment / 10.0) << "\n";
    }

    // <b> write a function to sort on names
    directory = "results_for_InsertionSort_byName";
    fs::create_directory(directory);

    ofstream out_name("IS20_IradriDas_results_name.csv");
    out_name << "n,avg_comparisons,avg_assignment\n";

    for (int n = 10; n <= 100; n = n + 10)
    {
        long long totalComparisons = 0;
        long double totalAssignment = 0;
        for (int run = 1; run <= 10; run++)
        {
            string file_name = "datasets/IS20_IradriDas_dataset_n" + to_string(n) + "_instance_" + to_string(run) + ".csv";
            vector<Person> record = read_records_from_CSV(file_name);

            long long comp_counter = 0;
            long long assign_counter = 0;
            insertionSort_byName(record, comp_counter, assign_counter);
            totalComparisons += comp_counter;
            totalAssignment += assign_counter;

            write_sorted_records_to_CSV(record, n, run, directory);
        }
        out_name << n << "," << (totalComparisons / 10.0) << "," << (totalAssignment / 10.0) << "\n";
    }

    // <c> sort on age and then on names so that the ordering on age is maintained
    directory = "results_for_InsertionSort_byAge_Name";
    fs::create_directory(directory);

    ofstream out_age_name("IS20_IradriDas_results_age_name.csv");
    out_age_name << "n,avg_comparisons,avg_assignment\n";

    for (int n = 10; n <= 100; n = n + 10)
    {
        long long totalComparisons = 0;
        long double totalAssignment = 0;

        for (int run = 1; run <= 10; run++)
        {
            string file_name = "datasets/IS20_IradriDas_dataset_n" + to_string(n) + "_instance_" + to_string(run) + ".csv";
            vector<Person> record = read_records_from_CSV(file_name);

            long long comp_counter = 0;
            long long assign_counter = 0;
            insertionSort_byAge_Name(record, comp_counter, assign_counter);
            totalComparisons += comp_counter;
            totalAssignment += assign_counter;

            write_sorted_records_to_CSV(record, n, run, directory);
        }
        out_age_name << n << "," << (totalComparisons / 10.0) << "," << (totalAssignment / 10.0) << "\n";
    }

    return 0;
}