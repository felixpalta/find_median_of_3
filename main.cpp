#include <iostream>
#include <algorithm>
#include <array>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;


typedef int MedianFinder(int a, int b, int c);

static int find_median_sorting(int a, int b, int c);

long long int test_median_finder_for_speed(MedianFinder f)
{
    srand((unsigned) time(NULL));

    using namespace chrono;

    auto start = system_clock::now();

    for (unsigned i = 0; i < 10000000; ++i)
    {
        f(rand(), rand(), rand());
    }

    auto dur = duration_cast<milliseconds>(std::chrono::system_clock::now() - start);

    return dur.count();
}

void test_median_finder(const string& test_name, MedianFinder f)
{
    bool ok = true;

    srand((unsigned) time(NULL));

    for (unsigned i = 0; i < 1000000; ++i)
    {
        int a = rand(), b = rand(), c = rand();
        auto result = f(a, b, c);
        ok &= result == find_median_sorting(a, b, c);
    }

    cout << "Test\t" << test_name << ": " << (ok ? "OK" : "FAIL") << '\t'
        << test_median_finder_for_speed(f) << "ms" << endl;
}

static int find_median_sorting(int a, int b, int c)
{
    int arr[] = {a, b, c};
    std::sort(begin(arr), end(arr));
    return arr[1];
}

// min 2 comparisons
// max 8 comparisons
static int find_median_comparing(int a, int b, int c)
{
    if ((a >= b && b >= c) || (a <= b && b <= c))
        return b;
    if ((b >= a && a >= c) || (b <= a && a <= c))
        return a;
    else
        return c;
}


// min 2 comparisons
// max 3 comparisons
static int find_median_bubble_sort(int a, int b, int c)
{
    // a, b, c
    if (a > b)
    {
        // b, a, c
        if (a > c)
        {
            // b, c, a(max)
            if (b > c)
            {
                // sorted: c, b, a
                    return b;
            }
            // else sorted: b, c, a
            return c;
        }
        // else
        return a;
    }
    // else a <= b
    if (b > c)
    {
        // a, c, b
        if (a > c)
            return a;
        return c;
    }
    return b;

}

int main()
{
    test_median_finder("Std Sorting: ", find_median_sorting);
    test_median_finder("Comparing: ", find_median_comparing);
    test_median_finder("Bubble Sort: ", find_median_bubble_sort);

    return 0;
}

