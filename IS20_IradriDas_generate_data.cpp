#include <filesystem>
#include <string>
#include <vector>
#include <random>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

void generate_data()
{

    vector<string> names = {"Reeta", "Geet", "Pankaj", "Suman", "Ritam", "Raj", "Ayan", "Iradri", "Abhinav", "Shivashish"};

    // random_device uses hardware entropy (if available). Prevents predictable sequences
    random_device rd;
    mt19937_64 gen(rd());

    uniform_int_distribution<int> random_name(0, names.size() - 1); // Produces random integer values i, uniformly distributed on the closed interval [min, max]
    uniform_real_distribution<double> random_age(20.0, 30.0);       // Produces random floating-point values x, uniformly distributed on the interval [min, max)

    fs::create_directory("datasets");

    for (int n = 10; n < 101; n = n + 10)
    {
        for (int run = 1; run < 11; run++)
        {
            string file_name = "datasets/IS20_IradriDas_dataset_n" + to_string(n) + "_instance_" + to_string(run) + ".csv";
            ofstream fout(file_name);
            fout << "name,age\n";

            for (int c = 0; c < n; c++)
            {
                // If the fractional part is less than 0.5, it returns the previous integer.
                // If the fractional part is greater or equal to 0.5, it returns the next integer.
                double age = random_age(gen);
                age = round(age * 10.0) / 10.0;

                string record = names[random_name(gen)] + "," + to_string(age) + "\n";
                fout << record;
            }
        }
    }
}
