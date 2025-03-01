# physical-design-homework1-parser

![GitHub repo size](https://img.shields.io/github/repo-size/ysnanako/physical-design-homework1-parser)
![GitHub last commit](https://img.shields.io/github/last-commit/ysnanako/physical-design-homework1-parser)

This project is part of the **National Cheng Kung University (NCKU) - VLSI/CAD Group** course **"Physical Design for Nanometer IC"**, focusing on parsing the **Bookshelf** format `.aux` file and generating `.dat` output files for visualizing chip layouts.

## 📖 Table of Contents
- [Project Overview](#project-overview)
- [Requirements](#requirements)
- [Installation & Execution](#installation--execution)
- [Input Format](#input-format)
- [Output Format](#output-format)
- [Project Structure](#project-structure)
- [Example Execution](#example-execution)
- [Generated Plots](#generated-plots)
- [Contribution Guide](#contribution-guide)
- [Contact Information](#contact-information)

## 📝 Project Overview
The **Bookshelf** format is widely used in **VLSI physical design** for storing **standard cell placement** information. This project is responsible for:
1. Parsing `.aux` files and reading:
   - `.nodes` - Circuit components and their dimensions
   - `.nets` - Netlist information
   - `.pl` - Placement information
   - `.scl` - Row placement information
2. Generating `.dat` files for visualization using **gnuplot**.

## 🛠️ Requirements
This project is developed on **Linux (Ubuntu 20.04+)** and requires:
- `g++ 6.3.0+`
- `make`
- `gnuplot`

## 🚀 Installation & Execution
Follow these steps to install and run the project:

1. **Clone the Repository**
   ```bash
   git clone https://github.com/ysnanako/physical-design-homework1-parser.git
   cd physical-design-homework1-parser
   ```

2. **Compile the Code**
   ```bash
   make
   ```

3. **Run the Program**
   ```bash
   ./HW1_StudentID <circuit.aux>
   ```

4. **Visualize the Output**
   ```bash
   cd plt
   gnuplot <circuit>/<circuit.plt>
   ```

## 📂 Input Format
This project follows the **Bookshelf** format and requires the following files:
- **`.aux`** - Main index file pointing to `.nodes`, `.nets`, `.pl`, `.scl`, etc.
- **`.nodes`** - Describes circuit components and their dimensions.
- **`.nets`** - Defines netlist connectivity.
- **`.pl`** - Specifies the placement coordinates.
- **`.scl`** - Defines row placement structure.

📄 **Example `.aux` File**
```
RowBasedPlacement : circuit.nodes circuit.nets circuit.pl circuit.scl
```

## 📄 Output Format
After execution, the program generates `.dat` files, which can be visualized using `gnuplot`:
- **`_chip.dat`** - Defines chip boundary.
- **`_cell.dat`** - Specifies MODULE locations.
- **`_pad.dat`** - Specifies PAD locations.
- **`_pad_pin.dat`** - Specifies PIN locations on the PADs.
- **`.plt`** - Gnuplot scripts for visualization.

## 🏗️ Project Structure
```
physical-design-homework1-parser/
│── src/              # Source code directory (main.cpp, parser.cpp, datatype.cpp, and headers)
│── obj/              # Compiled object files from the source code (ignored)
│── plt/              # Contains gnuplot scripts for visualization (ignored)
│── dat/              # Stores generated data files such as _chip.dat, _pad.dat, and _pad_pin.dat (ignored)
│── .gitignore        # Specifies files to ignore in version control
│── HW1_StudentID     # Executable file for the parser (ignored)
│── Makefile          # Defines build instructions for compiling the project
│── README.md         # This file

../benchmarks/        # Directory containing Bookshelf benchmark test cases (located outside the repo)

```

## 🔹 **Parsing Flow**
1. **Read the `.aux` file** and parse corresponding `.nodes`, `.nets`, `.pl`, `.scl` files.
2. **Build data structures** (`MODULES`, `NETS`, `PADS`).
3. **Compute circuit information**, including:
   - Number of modules (`MODULES.size()`)
   - Number of pads (`PADS.size()`)
   - Number of nets (`NETS.size()`)
   - Chip dimensions (`chip_W_H`)
4. **Generate `.dat` files** for visualization.
5. **Use `gnuplot` to plot the results**.

## ⚡ **Example Execution**
```bash
./HW1_StudentID ../benchmarks/adaptec1/adaptec1.aux
```
```bash
gnuplot adaptec1/adaptec1.plt
```

## 🖼️ Generated Plots
Below are the generated plots from the `gnuplot` output:

![adaptec1](https://github.com/user-attachments/assets/2d4ffa67-2e21-47f1-b1d6-9a91f103cdc1). 
*adaptec1*
![adaptec2](https://github.com/user-attachments/assets/70cbdc6e-2fb9-401d-8715-5a47294a14c1). 
*adaptec2*
![adaptec3](https://github.com/user-attachments/assets/882e6022-5419-4444-8e7a-76bd0a07cc12). 
*adaptec3*
![adaptec4](https://github.com/user-attachments/assets/4f87c502-b1c2-40bb-a855-493b30a9431e). 
*adaptec4*
![bigblue1](https://github.com/user-attachments/assets/8bc000f5-d5ac-458f-b4ca-7bf72233c14c). 
*bigblue1*
![bigblue2](https://github.com/user-attachments/assets/a90f96b3-fd2d-4bb5-baa3-f6fccbc37bf7). 
*bigblue2*
![bigblue3](https://github.com/user-attachments/assets/ec221b17-7e30-48b6-813d-5c1ef692a834). 
*bigblue3*
![bigblue4](https://github.com/user-attachments/assets/a2d2f925-6ef2-4d41-9d02-b3345ccf0a07). 
*bigblue4*

## 🤝 Contribution Guide
1. Fork this repository.
2. Create a new branch (`git checkout -b feature-xyz`).
3. Commit your changes (`git commit -m 'Add new feature'`).
4. Push to the remote branch (`git push origin feature-xyz`).
5. Submit a Pull Request.

## 📬 Contact Information
- 📧 Email: m16131056@gs.ncku.edu.tw
- 🌎 University: [National Cheng Kung University (NCKU)](https://www.ncku.edu.tw)
- 📖 Course: Physical Design for Nanometer IC, Fall 2024
