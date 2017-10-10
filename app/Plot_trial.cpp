// Example for C++ Interface to Gnuplot

// requirements:
// * gnuplot has to be installed (http://www.gnuplot.info/download.html)
// * for Windows: set Path-Variable for Gnuplot path (e.g. C:/program files/gnuplot/bin)
//             or set Gnuplot path with: Gnuplot::set_GNUPlotPath(const std::string &path);


#include <iostream>
#include <fstream>
#include "gnuplot_i.hpp"//Gnuplot class handles POSIX-Pipe-communikation with Gnuplot

#define SLEEP_LGTH 2  // sleep time in seconds
#define NPOINTS    50 // length of array

void wait_for_key(); // Programm halts until keypress

int main()
{
    //
    // Using the GnuplotException class
    //
    try
    {
        Gnuplot g1("lines");

        //
        // Slopes
        //

        g1.set_grid();
        const int x[4]={2,4,3};
        const int y[4]={4,5,3};
        std::ofstream outfile;
        outfile.open("Co_ordinates.txt", std::ios::out | std::ios::trunc );
            outfile.precision(6);
            for(int i=0;i<4; i++){
                outfile<<std::fixed<<x[i]<<"   "<<std::fixed<<y[i];
                outfile<<std::endl;
            }
        outfile.close();
        g1.set_grid();
        g1.plotfile_xy("Co_ordinates.txt",1,2,"Grid");
        wait_for_key();

    }
    catch (GnuplotException& ge)
    {
       std::cout << ge.what() <<std::endl;
    }
    return 0;
}



void wait_for_key ()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)  // every keypress registered, also arrow keys
    cout << endl << "Press any key to continue..." << endl;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    _getch();
#elif defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
    std::cout << std::endl << "Press ENTER to continue..." << std::endl;

    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
#endif
}
