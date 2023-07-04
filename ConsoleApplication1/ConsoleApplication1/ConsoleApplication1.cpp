#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

void hist(const vector<double>& dogi, size_t bin_count, size_t number_count) {

    vector<size_t> bons(bin_count);

    double min = dogi[0];
    double max = dogi[0];
    for (double x : dogi) {
        if (x < min) {
            min = x;
        }
        else if (x > max) {
            max = x;
        }
    }

    double bin_size = round((static_cast<double>(max - min) / bin_count) * 100.0) / 100.0;
    size_t segment;

    size_t max_count = 0, max_len = 0, len_segment;

    for (size_t i = 0; i < number_count; i++) {
        bool found = false;
        size_t j;
        for (j = 0; (j < bin_count - 1) && !found; j++) {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if ((lo <= dogi[i]) && (dogi[i] < hi)) {
                bons[j]++;
                found = true;
                if (bons[j] > max_count)
                    max_count = bons[j];
            }
        }
        if (!found) {
            bons[bin_count - 1]++;
            if (bons[bin_count - 1] > max_count)
                max_count = bons[bin_count - 1];
        }
    }
    for (double j = min; j < max; j += bin_size) {
        segment = static_cast<size_t>(j * 100);
        while (segment % 10 == 0)
            segment = segment / 10;
        len_segment = to_string(segment).length();
        if (j != segment)
            len_segment++;
        if (len_segment > max_len)
            max_len = len_segment;
    }

    double scaling_factor = 1;
    size_t height;
    double val_size = min;
    string sp(max_len, ' ');
    if (max_count > 76)
        scaling_factor = 76 / static_cast<double>(max_count);
    for (int i = 0; i < bin_count; i++) {
        if (bons[i] < 100) {
            cout << ' ';
        }
        if (bons[i] < 10) {
            cout << ' ';
        }

        cout << sp << bons[i] << '|';

        height = static_cast<int>(scaling_factor * bons[i]);
        for (int j = 0; j < height; j++)
            cout << '*';
        cout << '\n';
        val_size = val_size + bin_size;

        if (i < (bin_count - 1)) {
            cout << val_size << endl;
        }
    }

}

int main()
{
    setlocale(LC_ALL, "Russian");

    size_t number_count, bin_count;

    cerr << "Введите кол-во чисел: ";
    cin >> number_count;

    vector<double> dogi(number_count);
    dogi.resize(number_count);

    cerr << "Введите числа: ";
    for (int i = 0; i < number_count; i++) {
        cin >> dogi[i];
    }

    cerr << "Введите кол-во корзин: ";
    cin >> bin_count;
    cerr << '\n';

    hist(dogi, bin_count, number_count);
}