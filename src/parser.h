#ifndef _PARSER_H_
#define _PARSER_H_

#include "datatype.h"
using namespace std;

class PARSER
{
public:
    string node_filename, net_filename, wts_filename, pl_filename, scl_filename;
    void GetFilename(const int& argc, char *argv[]);
    void ReadAuxFile();
    void ReadNodeFile();
    void ReadNetFile();
    void ReadWtsFile();
    void ReadPlFile();
    void ReadSclFile();
    void WriteChipFile();
    void WriteCellFile();
    void WritePadFile();
    void WritePadPinFile();
    void CalTotal();
    void WritePltFile();
private:
    ifstream fin;
    ofstream fout;
    // node
    void CreatModule(string);
    void CreatPad(string);
    // net
    void CreatNet(string);
    void CreatPin(string);
    // pl
    void SetNodePos(string);
    // scl
    double GetNum(string);
};

#endif


