#include <iostream>
#include "spmat.h"
using namespace std;

int main()
{
    cout << "\n\n==================== m1 Tests =======================" << endl;
    SparseMatrix m1(4);
    SparseMatrix::Coord pts1[] =   
        { {0,2}, {0,3}, {1,1}, {1,2}, {2,0},
          {3,2}, {3,3}
        };
    double vals3[] = {2.6, 0.1, 2.3, 3.5, 5.1, 8.7, 4.3};
    for(size_t i = 0; i < sizeof(pts1)/sizeof(SparseMatrix::Coord); i++)
    {
        m1.set(pts1[i], vals3[i]);
    }
    cout << "Original" << endl;
    m1.print(std::cout);

    m1.set({0,0},1.8);
    cout << "Setting point 0,0 to 1.8" << endl;
    m1.print(std::cout);

    m1.set({1,2},0);
    cout << "Setting point 1,2 to 0" << endl;
    m1.print(std::cout);

    m1.copyDim({3,SparseMatrix::npos}, {SparseMatrix::npos,2});
    cout << "Copied row 3 to col 2" << endl;
    m1.print(std::cout);


    cout << "\n\n==================== M2 Tests =======================" << endl;

    SparseMatrix m2(1);
    cout << "Original" << endl;
    m2.print(std::cout);

    m2.set({0,0}, 1.2);

    cout << "Non-zero" << endl;
    m2.print(std::cout);

    cout << "Sum of row 0: " << m2.sumDim({0,SparseMatrix::npos}) << endl;
    cout << "Sum of col 0: " << m2.sumDim({SparseMatrix::npos,0}) << endl;

    m2.copyDim({0,SparseMatrix::npos}, {0, SparseMatrix::npos});
    cout << "Copied row 0 to row 0" << endl;
    m2.print(std::cout);

    m2.set({0,0},0);
    cout << "Delete a point by setting to 0" << endl;
    m2.print(std::cout);

    cout << "\n\n==================== m1 Tests =======================" << endl;
    SparseMatrix m3(10);
    SparseMatrix::Coord pts3[] =   
        { {0,1}, {7,5}, {0,5}, {0,3}, {0,8},
          {0,0}, {3,5}, {8,5}, {2,5}
        };
    for(size_t i = 0; i < sizeof(pts3)/sizeof(SparseMatrix::Coord); i++)
    {
        m3.set(pts3[i], pts3[i][0] + pts3[i][1]*.1);
    }
    cout << "Original" << endl;
    m3.print(std::cout);

    m3.set(pts3[8],0);
    cout << "Delete a point by setting to 0" << endl;
    m3.print(std::cout);

    cout << "Sum of row 0: " << m3.sumDim({0,SparseMatrix::npos}) << endl;
    cout << "Sum of col 5: " << m3.sumDim({SparseMatrix::npos,5}) << endl;

    m3.copyDim({0,SparseMatrix::npos}, {0,SparseMatrix::npos});
    cout << "Copied row 0 to row 0" << endl;
    m3.print(std::cout);

    m3.copyDim({0,SparseMatrix::npos}, {1,SparseMatrix::npos});
    cout << "Copied row 0 to row 1" << endl;
    m3.print(std::cout);

    m3.copyDim({SparseMatrix::npos,5}, {SparseMatrix::npos,6});
    cout << "Copied col 5 to 6" << endl;
    m3.print(std::cout);

    m3.copyDim({0,SparseMatrix::npos}, {SparseMatrix::npos,1});
    cout << "Copied row 0 to col 1" << endl;
    m3.print(std::cout);

    m3.copyDim({SparseMatrix::npos,8}, {3,SparseMatrix::npos});
    cout << "Copied col 8 to row 3" << endl;
    m3.print(std::cout);

    cout << "Getting location 9,9: (should be 0) " << m3.get({9,9}) << endl;
    cout << "Now getting location 10,10: (should throw) " << endl;
    try {
        m3.get({10,10});
        cout << "Should not print this -- should have thrown exception" << endl;
    }
    catch(std::invalid_argument&) {
        cout << "Correctly threw exception." << endl;
    }

    SparseMatrix m4(10);
    for(size_t i = 0; i < sizeof(pts3)/sizeof(SparseMatrix::Coord); i++)
    {
        m4.set(pts3[i], pts3[i][0] + pts3[i][1]*.1);
    }

    
    cout << "Original" << endl;
    m4.print(std::cout);

    m4.copyDim({2, SparseMatrix::npos}, {2, SparseMatrix::npos});
    cout << "Copied row 2 to row 2" << endl;
    m4.print(std::cout);

    m4.set({3,5}, 0);
    cout << "Delete a point by setting to 0" << endl;
    m4.print(std::cout);

    m4.copyDim({SparseMatrix::npos, 5}, {SparseMatrix::npos, 2});
    cout << "Copied col 5 to col 2" << endl;
    m4.print(std::cout);

    m4.copyDim({SparseMatrix::npos, 2}, {2, SparseMatrix::npos});
    cout << "Copied col 2 to row 2" << endl;
    m4.print(std::cout);

    m4.copyDim({SparseMatrix::npos, 8}, {2, SparseMatrix::npos});
    cout << "Copied col 8 to row 2" << endl;
    m4.print(std::cout);

    m4.copyDim({0, SparseMatrix::npos}, {SparseMatrix::npos, 0});
    cout << "Copied row 0 to col 0" << endl;
    m4.print(std::cout);

    m4.copyDim({0, SparseMatrix::npos}, {SparseMatrix::npos, 1});
    cout << "Copied row 0 to col 0" << endl;
    m4.print(std::cout);

    m4.copyDim({SparseMatrix::npos, 2}, {5, SparseMatrix::npos});
    cout << "Copied col 2 to row 5" << endl;
    m4.print(std::cout);

    m4.set({0,0}, 9);
    cout << "Setting 0,0 to 9" << endl;
    m4.print(std::cout);

    m4.set({4,0}, 9);
    cout << "Setting 4,0 to 9" << endl;
    m4.print(std::cout);

    m4.set({6,0}, 9);
    cout << "Setting 6,0 to 9" << endl;
    m4.print(std::cout);

    m4.set({7,0}, 9);
    cout << "Setting 7,0 to 9" << endl;
    m4.print(std::cout);

    m4.set({9,0}, 9);
    cout << "Setting 9,0 to 9" << endl;
    m4.print(std::cout);

    m4.copyDim({7, SparseMatrix::npos}, {SparseMatrix::npos, 5});
    cout << "Copied row 7 to col 5" << endl;
    m4.print(std::cout);

    m4.copyDim({SparseMatrix::npos, 0}, {1, SparseMatrix::npos});
    cout << "Copied col 0 to row 1" << endl;
    m4.print(std::cout);

    m4.copyDim({0, SparseMatrix::npos}, {SparseMatrix::npos, 1});
    cout << "Copied row 0 to col 1" << endl;
    m4.print(std::cout);

    m4.copyDim({SparseMatrix::npos, 2}, {3, SparseMatrix::npos});
    cout << "Copied col 2 to row 3" << endl;
    m4.print(std::cout);

    m4.copyDim({SparseMatrix::npos, 2}, {7, SparseMatrix::npos});
    cout << "Copied col 2 to row 7" << endl;
    m4.print(std::cout);

    m4.copyDim({SparseMatrix::npos, 7}, {1, SparseMatrix::npos});
    cout << "Copied col 7 to row 1" << endl;
    m4.print(std::cout);

    m4.copyDim({SparseMatrix::npos, 5}, {5, SparseMatrix::npos});
    cout << "Copied col 5 to row 5" << endl;
    m4.print(std::cout);

    m4.copyDim({SparseMatrix::npos, 3}, {1, SparseMatrix::npos});
    cout << "Copied col 3 to row 1" << endl;
    m4.print(std::cout);

    m4.copyDim({SparseMatrix::npos, 3}, {5, SparseMatrix::npos});
    cout << "Copied col 3 to row 5" << endl;
    m4.print(std::cout);

    m4.copyDim({SparseMatrix::npos, 0}, {8, SparseMatrix::npos});
    cout << "Copied col 0 to row 8" << endl;
    m4.print(std::cout);

    m4.copyDim({SparseMatrix::npos, 2}, {4, SparseMatrix::npos});
    cout << "Copied col 2 to row 4" << endl;
    m4.print(std::cout);
    

    try {
        m4.copyDim({SparseMatrix::npos, 5}, {6, 5});
        cout << "Should not print this -- should have thrown exception" << endl;
    }
    catch(std::invalid_argument&) {
        cout << "Correctly threw exception." << endl;
    }



    

    return 0;
}