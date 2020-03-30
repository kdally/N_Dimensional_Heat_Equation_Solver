#include <iostream>
#include <chrono>
//#include <fstream> // (disabled for Inginious upload)

#include "heat.hpp"

using namespace std;

// 'MATLAB' style tic-toc functions
chrono::time_point<std::chrono::system_clock> clk;
inline void tic() {
    clk = std::chrono::system_clock::now();
}
inline auto toc() {
    auto toc = std::chrono::system_clock::now();
    return std::chrono::duration<double>(toc - clk).count();
}

// Find max
template<typename T>
T findMax(const Vector<T>& vector) {
    T max = (T) 0;
    for (auto & el : vector) {
        if (el > max)
            max = el;
    }
    return max;
}

// Dump results to file (disabled for Inginious upload)
/*
template<typename T>
void saveToFile(const char* fileName, Vector<T> solution) {
    ofstream file;
    file.open(fileName);

    for (auto & element : solution) {
        file << element << " ";
    }

    file << endl;
    file.close();
}*/

int main() {

    /** 1D test **/
    // Test base 1D case (alpha = .3125, m = 3, dt = .1)
    Heat<1, double> heatSimple1D = Heat<1, double>(.3125, 3, .1);
    cout << "Matrix for heatSimple1D (n = 1, alpha = .3125, m = 3, dt = .1): " << endl;
    heatSimple1D.M.dump(); // Print matrix to console

    Heat<1, double> heat1D = Heat<1, double>(.3125, 99, .001);
    double heat1DExactTime, heat1DSolveTime;
    tic(); auto heat1DExact = heat1D.exact(1); heat1DExactTime = toc(); // exact() solver
    tic(); auto heat1DSolve = heat1D.solve(1); heat1DSolveTime = toc(); // solve() solver
    auto error1D = heat1DSolve - heat1DExact;

    // Print timings and error
    cout << "Heat1D exact time: " << heat1DExactTime << "s" << endl;
    cout << "Heat1D solve time: " << heat1DSolveTime << "s" << endl;
    cout << "Heat1D max error:  " << findMax(error1D) << endl;

    cout << "=====" << endl;

    /** 2D test **/
    // Test base 2D case (alpha = .3125, m = 3, dt = .1)
    Heat<2, double> heatSimple2D = Heat<2, double>(.3125, 3, .1);

    cout << "Matrix for heatSimple2D (n = 2, alpha = .3125, m = 3, dt = .1): " << endl;
    heatSimple2D.M.dump(); // Print matrix to console

    // Initialize proper 2D test
    Heat<2, double> heat2D = Heat<2, double>(.3125, 99, .001);
    double heat2DExactTime, heat2DSolveTime;
    tic(); auto heat2DExact = heat2D.exact(0.5); heat2DExactTime = toc(); // exact() solver
    tic(); auto heat2DSolve = heat2D.solve(0.5); heat2DSolveTime = toc(); // solve() solver
    auto error2D = heat2DSolve - heat2DExact;

    // Print timings and error
    cout << "Heat2D exact time: " << heat2DExactTime << "s" << endl;
    cout << "Heat2D solve time: " << heat2DSolveTime << "s" << endl;
    cout << "Heat2D max error:  " << findMax(error2D) << endl;
    // Save to file (disabled for Inginious upload)
    //saveToFile("heat1DExact.txt", heat1DExact);
    //saveToFile("heat1DSolve.txt", heat1DSolve);
    //saveToFile("heat2DExact.txt", heat2DExact);
    //saveToFile("heat2DSolve.txt", heat2DSolve);

    return 0;
}