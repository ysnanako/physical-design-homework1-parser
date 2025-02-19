#include "parser.h"
using namespace std;

#define N 0
#define S 1
#define W 2
#define E 3
#define F 4

void PARSER::GetFilename(const int& argc, char *argv[])
{
    if(argc == 2)
        benchmark = argv[1];
    else
    {
        cerr << "Usage: ./exe <circuit.aux>. \n";
        exit(EXIT_FAILURE);
    }
    for(size_t cnt = 0, i = 0; cnt < 3; ++i)
    {
        benchmark_dir += argv[1][i];
        if(cnt == 2 && argv[1][i] != '/')
            benchname += argv[1][i];
        if(argv[1][i] == '/')
            cnt++;
    }
    output_dir = "dat/" + benchname + "/";
}
void PARSER::ReadAuxFile()
{
    fin.open(benchmark);
    if(!fin)
    {
        cerr << "Error: Input .aux file failed. \n";
        exit(EXIT_FAILURE);
    }
    string temp;
    fin >> temp >> temp >> node_filename >> net_filename >> wts_filename >> pl_filename >> scl_filename;
    fin.close();
    node_filename = benchmark_dir + node_filename;
    net_filename = benchmark_dir + net_filename;
    wts_filename = benchmark_dir + wts_filename;
    pl_filename = benchmark_dir + pl_filename;
    scl_filename = benchmark_dir + scl_filename;
    fin.close();
    cout << "Read aux file done. \n";
}
void PARSER::ReadNodeFile()
{
    fin.open(node_filename);
    if(!fin)
    {
        cerr << "Error: Input .nodes file failed. \n";
        exit(EXIT_FAILURE);
    }
    string line;
    getline(fin, line);
    getline(fin, line);
    getline(fin, line);
    getline(fin, line);
    getline(fin, line);
    getline(fin, line);
    while(getline(fin, line))
    {
        if(line.size() < 1)
            continue;
        else if(line.back() != 'l' && line.back() != 'I')
            CreatModule(line);
        else if(line.back() == 'l' || line.back() == 'I')
            CreatPad(line);
    }
    fin.close();
    cout << "Read node file done. \n";
}
void PARSER::CreatModule(string line)
{
    stringstream ss(line);
    MODULE *new_ptr = new MODULE;
    ss >> new_ptr->name;
    new_ptr->id = stoul(new_ptr->name.substr(1));
    double w, h;
    ss >> w >> h;
    new_ptr->W_H = FPOS(w, h);
    MODULES.push_back(new_ptr);
    module_map[new_ptr->name] = new_ptr;
}
void PARSER::CreatPad(string line)
{
    stringstream ss(line);
    PAD *new_ptr = new PAD;
    ss >> new_ptr->name;
    new_ptr->id = stoul(new_ptr->name.substr(1));
    double w, h;
    ss >> w >> h;
    new_ptr->W_H = FPOS(w, h);
    if(line.back() == 'I')
        new_ptr->is_cover = true;
    PADS.push_back(new_ptr);
    pad_map[new_ptr->name] = new_ptr;
}
void PARSER::ReadNetFile()
{
    fin.open(net_filename);
    if(!fin)
    {
        cerr << "Error: Input .nets file failed. \n";
        exit(EXIT_FAILURE);
    }
    string line;
    getline(fin, line);
    getline(fin, line);
    getline(fin, line);
    getline(fin, line);
    getline(fin, line);
    getline(fin, line);
    getline(fin, line);
    while(getline(fin, line))
    {
        if(line.size() < 1)
            continue;
        else if(line.substr(0, 1) == "N")
            CreatNet(line);
        else if(line.substr(0, 1) == "\t")
            CreatPin(line);
    }
    default_Pin_W_H.Set(3);
    fin.close();
    cout << "Read net file done. \n";
}
void PARSER::CreatNet(string line)
{
    stringstream ss(line);
    string s;
    NET *new_ptr = new NET;
    ss >> s >> s >> s >> new_ptr->name;
    new_ptr->id = stoul(new_ptr->name.substr(1));
    NETS.push_back(new_ptr);
}
void PARSER::CreatPin(string line)
{
    stringstream ss(line);
    string s;
    ss >> s;
    // module
    auto module_it = module_map.find(s);
    if(module_it != module_map.end())
    {
        MODULE *module_ptr = module_it->second;
        // pin
        double x, y;
        ss >> s >> s >> x >> y;
        PIN *new_ptr = new PIN;
        new_ptr->module = module_ptr;
        new_ptr->offset = FPOS(x, y);
        // node
        module_ptr->nets.push_back(NETS.back());
        module_ptr->pins.push_back(new_ptr);
        // net
        NETS.back()->pins.push_back(new_ptr);
        return;
    }
    // pad
    auto pad_it = pad_map.find(s);
    if(pad_it != pad_map.end())
    {
        PAD *pad_ptr = pad_it->second;
        // pin
        double x, y;
        ss >> s >> s >> x >> y;
        PIN *new_ptr = new PIN;
        new_ptr->pad = pad_ptr;
        new_ptr->offset = FPOS(x, y);
        // node
        pad_ptr->pins.push_back(new_ptr);
        // net
        NETS.back()->pins.push_back(new_ptr);
        return;
    }
}
void PARSER::ReadWtsFile()
{
    
}
void PARSER::ReadPlFile()
{
    fin.open(pl_filename);
    if(!fin)
    {
        cerr << "Error: Input .pl file failed. \n";
        exit(EXIT_FAILURE);
    }
    string line;
    getline(fin, line);
    getline(fin, line);
    getline(fin, line);
    getline(fin, line);
    while(getline(fin, line))
    {
        if(line.size() < 1)
            continue;
        SetNodePos(line);
    }
    fin.close();
    cout << "Read pl file done. \n";
}
void PARSER::SetNodePos(string line)
{
    stringstream ss(line);
    string s;
    ss >> s;
    // module
    auto module_it = module_map.find(s);
    if(module_it != module_map.end()) 
    {
        MODULE *module_ptr = module_it->second;
        double x, y;
        ss >> x >> y >> s >> s;
        module_ptr->lb = FPOS(x, y);
        module_ptr->ur.update_ur(module_ptr->lb, module_ptr->W_H);
        module_ptr->center.Center(module_ptr->lb, module_ptr->W_H);
        switch (s.back())
        {
        case 'N':
            module_ptr->orientation = N;
            break;
        case 'W':
            module_ptr->orientation = S;
            break;
        case 'S':
            module_ptr->orientation = W;
            break;
        case 'E':
            module_ptr->orientation = E;
            break;
        default:
            break;
        }
        if(s.front() == 'F')
            module_ptr->orientation += F;
        return;
    }
    // pad
    auto pad_it = pad_map.find(s);
    if(pad_it != pad_map.end()) 
    {
        PAD *pad_ptr = pad_it->second;
        double x, y;
        ss >> x >> y;
        pad_ptr->lb = FPOS(x, y);
        pad_ptr->ur.update_ur(pad_ptr->lb, pad_ptr->W_H);
        pad_ptr->center.Center(pad_ptr->lb, pad_ptr->W_H);
        switch (s.back())
        {
        case 'N':
            pad_ptr->orientation = N;
            break;
        case 'W':
            pad_ptr->orientation = S;
            break;
        case 'S':
            pad_ptr->orientation = W;
            break;
        case 'E':
            pad_ptr->orientation = E;
            break;
        default:
            break;
        }
        if(s.front() == 'F')
            pad_ptr->orientation += F;
        return;
    }
}
void PARSER::ReadSclFile()
{
    fin.open(scl_filename);
    if(!fin)
    {
        cerr << "Error: Input .scl file failed. \n";
        exit(EXIT_FAILURE);
    }
    string line;
    getline(fin, line);
    getline(fin, line);
    getline(fin, line);
    getline(fin, line);
    double num_rows = 0, num_sites = 0, height = 0, site_width = 0;
    chip_lb.Set(numeric_limits<double>::max(), 0);
    while(getline(fin, line))
    {
        if(line.size() < 1)
            continue;
        else if(line.substr(0, 7) == "NumRows" && !num_rows)
            num_rows = GetNum(line);
        else if(line.substr(0, 7) == "  Coord" && !chip_lb.y)
            chip_lb.y = GetNum(line);
        else if(line.substr(0, 8) == "  Height" && !height)
            height = GetNum(line);
        else if(line.substr(0, 11) == "  Sitewidth" && !site_width)
            site_width = GetNum(line);
        else if(line.substr(0, 14) == "  SubrowOrigin")
        {
            if(GetNum(line) < chip_lb.x)
                chip_lb.x = GetNum(line);
            if(num_sites < GetNum(line.substr(25)))
                num_sites = GetNum(line.substr(25));
        }
    }
    chip_ur.x = chip_lb.x + num_sites * site_width;
    chip_ur.y = chip_lb.y + num_rows * height;
    chip_W_H.update_W_H(chip_lb, chip_ur);
    chip_area = chip_W_H.GetProduct();
    fin.close();
    cout << "Read scl file done. \n";
}
double PARSER::GetNum(string line)
{
    stringstream ss(line);
    string s;
    ss >> s >> s >> s;
    return stod(s);
}
void PARSER::WriteChipFile()
{
    fout.open(output_dir + benchname + "_chip.dat");
    if(!fout)
    {
        cerr << "Error: Output _chip.dat file failed. \n";
        exit(EXIT_FAILURE);
    }
    fout << "\n# core region\n";
    fout << chip_lb.x << ", " << chip_lb.y << "\n";
    fout << chip_ur.x << ", " << chip_lb.y << "\n";
    fout << chip_ur.x << ", " << chip_ur.y << "\n";
    fout << chip_lb.x << ", " << chip_ur.y << "\n";
    fout << chip_lb.x << ", " << chip_lb.y << "\n\n";
    fout << "\n# die area\n";
    fout << chip_lb.x << ", " << chip_lb.y << "\n";
    fout << chip_ur.x << ", " << chip_lb.y << "\n";
    fout << chip_ur.x << ", " << chip_ur.y << "\n";
    fout << chip_lb.x << ", " << chip_ur.y << "\n";
    fout << chip_lb.x << ", " << chip_lb.y << "\n\n";
    fout.close();
    cout << "Write chip file done. \n";
}
void PARSER::WriteCellFile()
{
    fout.open(output_dir + benchname + "_cell.dat");
    if(!fout)
    {
        cerr << "Error: Output _cell.dat file failed. \n";
        exit(EXIT_FAILURE);
    }
    fout << "\n# FENCE DEFAULT\n";
    fout << "0, 0\n\n";
    for(auto const &module : MODULES)
    {
        // relative to chip_lb
        module->lb = module->lb - chip_lb; 
        module->ur.update_ur(module->lb, module->W_H);
        // write cell file
        fout << "# " << module->name << "\n";
        fout << module->lb.x << ", " << module->lb.y << "\n";
        fout << module->ur.x << ", " << module->lb.y << "\n";
        fout << module->ur.x << ", " << module->ur.y << "\n";
        fout << module->lb.x << ", " << module->ur.y << "\n";
        fout << module->lb.x << ", " << module->lb.y << "\n\n";
        // relative to (0, 0)
        module->lb = module->lb + chip_lb; 
        module->ur.update_ur(module->lb, module->W_H);
    }
    fout.close();
    cout << "Write cell file done. \n";
}
void PARSER::WritePadFile()
{
    fout.open(output_dir + benchname + "_pad.dat");
    if(!fout)
    {
        cerr << "Error: Output _pad.dat file failed. \n";
        exit(EXIT_FAILURE);
    }
    fout << "\n# PADS\n";
    fout << "0, 0\n\n";
    for(auto const &pad : PADS)
    {
        // relative to chip_lb
        pad->lb = pad->lb - chip_lb;
        pad->ur.update_ur(pad->lb, pad->W_H);
        // write pad file
        fout << "# " << pad->name << "\n";
        fout << pad->lb.x << ", " << pad->lb.y << "\n";
        fout << pad->ur.x << ", " << pad->lb.y << "\n";
        fout << pad->ur.x << ", " << pad->ur.y << "\n";
        fout << pad->lb.x << ", " << pad->ur.y << "\n";
        fout << pad->lb.x << ", " << pad->lb.y << "\n\n";
        // arrow /
        fout << pad->lb.x + pad->W_H.x * 0.65 << ", " << pad->lb.y + pad->W_H.y * 0.85 << "\n";
        fout << pad->lb.x + pad->W_H.x * 0.75 << ", " << pad->ur.y << "\n\n";
        // arrow |
        fout << pad->lb.x + pad->W_H.x * 0.75 << ", " << pad->lb.y + pad->W_H.y * 0.6 << "\n";
        fout << pad->lb.x + pad->W_H.x * 0.75 << ", " << pad->ur.y << "\n\n";
        // arrow
        fout << pad->lb.x + pad->W_H.x * 0.75 << ", " << pad->ur.y << "\n";
        fout << pad->lb.x + pad->W_H.x * 0.85 << ", " << pad->lb.y + pad->W_H.y * 0.85 << "\n\n";
        // relative to (0, 0)
        pad->lb = pad->lb + chip_lb;
        pad->ur.update_ur(pad->lb, pad->W_H);
    }
    fout.close();
    cout << "Write pad file done. \n";
}
void PARSER::WritePadPinFile()
{
    fout.open(output_dir + benchname + "_pad_pin.dat");
    if(!fout)
    {
        cerr << "Error: Output _pad_pin.dat file failed. \n";
        exit(EXIT_FAILURE);
    }
    fout << "\n# PAD_PIN\n";\
    fout << "0, 0\n\n";
    for(auto const &net : NETS)
    {
        fout << "# " << net->name << "\n";
        for(auto const &pin : net->pins)
        {
            if(pin->pad)
            {
                // relative to chip_lb
                FPOS pos = pin->pad->center + pin->offset - chip_lb;
                fout << pos.x << ", " << pos.y << "\n";
                fout << pos.x + default_Pin_W_H.x << ", " << pos.y << "\n";
                fout << pos.x + default_Pin_W_H.x << ", " << pos.y + default_Pin_W_H.y << "\n";
                fout << pos.x << ", " << pos.y + default_Pin_W_H.y << "\n";
                fout << pos.x << ", " << pos.y << "\n\n";
            }
        }
    }
    fout.close();
    cout << "Write pad pin file done. \n";
}
void PARSER::CalTotal()
{
    for(auto const &module : MODULES)
        total_module_area += module->W_H.GetProduct();
    for(auto const &pad : PADS)
        total_pad_area += pad->W_H.GetProduct();
    for(auto const &net : NETS)
    {
        FPOS min_pos, max_pos;
        min_pos.Set(numeric_limits<double>::max());
        max_pos.Set(numeric_limits<double>::min());
        for(auto const &pin : net->pins)
        {
            FPOS pos;
            if(pin->module)
                pos = pin->module->center + pin->offset;
            if(pin->pad)
                pos = pin->pad->center + pin->offset;
            min_pos.Min(pos);
            max_pos.Max(pos);
        }
        wHPWL += (max_pos.x - min_pos.x) + (max_pos.y - min_pos.y);
    }
}
void PARSER::WritePltFile()
{
    fout.open("plt/" + benchname + "/" + benchname + ".plt");
    if(!fout)
    {
        cerr << "Error: Output .plt file failed. \n";
        exit(EXIT_FAILURE);
    }
    fout << "set nokey\n";
    fout << "set term pngcairo font 'qt'\n";
    fout << "set output '" << benchname + "/" + benchname  << ".png'\n\n";

    fout << "set size ratio -1\n";
    fout << "set xrange [0:]\n";
    fout << "set yrange [0:]\n";
    fout << "plot[:][:] ";
    fout << "'../" << output_dir + benchname << "_chip.dat' w l lc -1, ";
    fout << "'../" << output_dir + benchname << "_cell.dat' w l lc 6, ";
    fout << "'../" << output_dir + benchname << "_pad.dat' w l lc 4, ";
    fout << "'../" << output_dir + benchname << "_pad_pin.dat' w l lc -1\n\n\n";
    
    fout << "set title '" << benchname << ", MODULE= " << MODULES.size() << ", NET= " << NETS.size() << ", HPWL= " << wHPWL << ", ' font 'Times, 22'\n\n";

    fout << "set term qt\n";
    fout << "set key\n\n";

    fout << "set size ratio -1\n";
    fout << "plot[:][:] ";
    fout << "'../" << output_dir + benchname << "_chip.dat' w l lc -1, ";
    fout << "'../" << output_dir + benchname << "_cell.dat' w l lc 6, ";
    fout << "'../" << output_dir + benchname << "_pad.dat' w l lc 4, ";
    fout << "'../" << output_dir + benchname << "_pad_pin.dat' w l lc -1\n\n\n";

    fout << "pause -1 'Press any key'\n";

    fout.close();
    cout << "Write plt file done. \n";
}