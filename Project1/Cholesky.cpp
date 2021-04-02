// Cholesky Decomposition

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <excpt.h>

#include <iomanip> 

using namespace std;


double** Cholesky_Decomposition(double** &matrix)
{
    int n = 0;
    double temp;
    //count the matrix dim.
    __try {
        while (true) {
            temp = matrix[n][0];
            n++;
        }
    }
        // __except will end the count of n at the end of the matrix.
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
    
    //make an array to store the result.
    double** lower = new double*[n];
    for (int i = 0; i < n; i++) {
        lower[i] = new double[n];
    }
    double sum;

    //the cholesky decomposition calculation according to the formulas in the russian wikipedia page.
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            if (i == j) {
                sum = 0;
                for (int k = 0; k < i; k++) {
                    sum += pow(lower[i][k], 2);
                }
                sum = matrix[i][i] - sum;
                lower[i][i] = sqrt(abs(sum));
            }
            else if (j > i) {
                sum = 0;
                for (int k = 0; k < i; k++) {
                    sum += lower[i][k] * lower[j][k];
                }
                sum = matrix[j][i] - sum;
                lower[j][i] = sum / lower[i][i];
            }
            else
                lower[j][i] = 0;
        }
    }
    return lower;
}


int main()
{
    string line;
    string c = ",";
    size_t pos = 0;
    string token;
    vector<double> temp;
    int n = 0;

    //open the file to read
    ifstream dataFile("data1.txt"); 
    if (dataFile.fail()) {
        cerr << "Error opening file" << endl;
        exit(1);
    }
    cout << "start reading the data" << endl;

    //get data from file and count the number of rows.
    while (getline(dataFile, line)) {
        n++;
        while ((pos = line.find(c)) != string::npos) {
            token = line.substr(0, pos);
            //store the data in a temp vector type.
            temp.push_back(stod(token));
            line.erase(0, pos + c.length());
        }

        temp.push_back(stod(line));
    }
    cout << "finish reading the data" << endl;

    //make matrix in the appropriate size and fill it with the data.
    double** matrix = new double*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new double[n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = temp[i + j * n];
        }
    }
    cout << "finish converting to matrix and start the Cholesky func " << endl;
    double** L;
    clock_t begin = clock();
    L = Cholesky_Decomposition(matrix);

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "time to run Cholesky function= " << elapsed_secs << endl;
    
    ofstream output("resultMatrix.txt");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            output << L[i][j] << ","; // behaves like cout - cout is also a stream
        }
        output << "\n";
    }
  
    cout << "finish filling input txt file" << endl;

   getchar();
    return 0;
}