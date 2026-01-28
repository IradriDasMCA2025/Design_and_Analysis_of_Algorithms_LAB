#include <iostream>
#include <vector>
#include <filesystem>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
namespace fs = std::filesystem;

/* ----------------------- STRUCT ----------------------- */

struct Game
{
    long rank;
    string name;
    string platform;
    string year;
    string genre;
    string publisher;
    double NA_Sales;
    double EU_Sales;
    double JP_Sales;
    double Other_Sales;
    double Global_Sales;
};

/* ----------------------- STRING TRIM ----------------------- */

string trim(const string &s)
{
    size_t start = s.find_first_not_of(" \t\r\n\"");
    size_t end = s.find_last_not_of(" \t\r\n\"");
    if (start == string::npos || end == string::npos)
        return "";
    return s.substr(start, end - start + 1);
}

/* ----------------------- SAFE CONVERSIONS ----------------------- */

int safe_stoi(string s)
{
    s = trim(s);
    if (s.empty() || s == "N/A")
        return 0;
    return stoi(s);
}

double safe_stod(string s)
{
    s = trim(s);
    try
    {
        if (s.empty() || s == "N/A")
            return 0.0;
        return stod(s);
    }
    catch (...)
    {
        return 0.0;
    }
}

/* ----------------------- CSV READER ----------------------- */

vector<Game> read_records_from_CSV(const string &filename)
{
    vector<Game> record;
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

        string rank, name, platform, year, genre, publisher;
        string NA_Sales, EU_Sales, JP_Sales, Other_Sales, Global_Sales;

        getline(ss, rank, ',');
        getline(ss, name, ',');
        getline(ss, platform, ',');
        getline(ss, year, ',');
        getline(ss, genre, ',');
        getline(ss, publisher, ',');
        getline(ss, NA_Sales, ',');
        getline(ss, EU_Sales, ',');
        getline(ss, JP_Sales, ',');
        getline(ss, Other_Sales, ',');
        getline(ss, Global_Sales, ',');

        record.push_back({safe_stoi(rank),
                          trim(name),
                          trim(platform),
                          trim(year),
                          trim(genre),
                          trim(publisher),
                          safe_stod(NA_Sales),
                          safe_stod(EU_Sales),
                          safe_stod(JP_Sales),
                          safe_stod(Other_Sales),
                          safe_stod(Global_Sales)});
    }

    return record;
}

/* ----------------------- CSV WRITER ----------------------- */

void write_sorted_records_to_CSV(
                                const vector<Game> &record,
                                int run,
                                int n,
                                const string &directory)
{
    string filename = directory +
                      "/sorted_dataset_n" +
                      to_string(n) +
                      "_run_" +
                      to_string(run) +
                      ".csv";

    ofstream fout(filename);

    fout << "Rank,Name,Platform,Year,Genre,Publisher,"
         << "NA_Sales,EU_Sales,JP_Sales,Other_Sales,Global_Sales\n";

    for (const auto &g : record)
    {
        fout << g.rank << ","
             << g.name << ","
             << g.platform << ","
             << g.year << ","
             << g.genre << ","
             << g.publisher << ","
             << g.NA_Sales << ","
             << g.EU_Sales << ","
             << g.JP_Sales << ","
             << g.Other_Sales << ","
             << g.Global_Sales << "\n";
    }
}

/* ----------------------- INSERTION SORT ----------------------- */

void insertionSort_byNA_sales(vector<Game> &list, long long &comparisons)
{
    int n = list.size();

    for (int i = 1; i < n; i++)
    {
        Game key = list[i];
        int j = i - 1;

        while (j >= 0)
        {
            comparisons++;
            if (list[j].NA_Sales > key.NA_Sales)
            {
                list[j + 1] = list[j];
                j--;
            }
            else
            {
                break;
            }
        }
        list[j + 1] = key;
    }
}

/* ----------------------- MAIN ----------------------- */

int main()
{
    string outputDir = "results_for_InsertionSort_byNA_Sales";

    if (!fs::exists(outputDir))
        fs::create_directory(outputDir);

    ofstream results("average_comparisons_NA_Sales.csv");
    results << "n,avg_comparisons\n";

    for (int n = 10; n <= 100; n += 10)
    {
        long double totalComparisons = 0;

        for (int run = 1; run <= 10; run++)
        {
            string datasetFile =
                "datasets/R_No_20_P2_IradriDas_data_" +
                to_string(n) + "_" +
                to_string(run) + ".csv";

            vector<Game> games = read_records_from_CSV(datasetFile);

            long long comparisons = 0;
            insertionSort_byNA_sales(games, comparisons);

            totalComparisons += comparisons;

            write_sorted_records_to_CSV(games, n, run, outputDir);
        }

        results << n << "," << (totalComparisons / 10.0) << "\n";
    }

    return 0;
}
