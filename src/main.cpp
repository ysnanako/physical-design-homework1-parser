#include "datatype.h"
#include "parser.h"
using namespace std;

int main(int argc, char *argv[])
{
    PARSER PARSER_obj;

    PARSER_obj.GetFilename(argc, argv);

    PARSER_obj.ReadAuxFile();
    PARSER_obj.ReadNodeFile();
    PARSER_obj.ReadNetFile();
    PARSER_obj.ReadPlFile();
    PARSER_obj.ReadSclFile();

    PARSER_obj.WriteChipFile();
    PARSER_obj.WriteCellFile();
    PARSER_obj.WritePadFile();
    PARSER_obj.WritePadPinFile();

    PARSER_obj.CalTotal();

    PARSER_obj.WritePltFile();

    // cout information
    cout << "\n";
    cout << "benchmark_dir: " << benchmark_dir << endl;
    cout << "output_dir: " << output_dir << endl;
    cout << "Benchmark: " << benchname << endl;
    cout << "\n";
    cout << "MODULES.size(): " << MODULES.size() << endl;
    cout << "PADS.size(): " << PADS.size() << endl;
    cout << "NETS.size(): " << NETS.size() << endl;
    cout << "\n";
    cout << "chip_lb: " << chip_lb << endl;
    cout << "chip_ur: " << chip_ur << endl;
    cout << "chip_W_H: " << chip_W_H << endl;
    cout << "\n";
    cout << "total_module_area: " << total_module_area << endl;
    cout << "total_pad_area: " << total_pad_area << endl;
    cout << "wHPWL: " << wHPWL << endl;

    return EXIT_SUCCESS; 
}

// ./HW1_M16131056 ../benchmarks/adaptec1/adaptec1.aux


// gnuplot adaptec1/adaptec1.plt