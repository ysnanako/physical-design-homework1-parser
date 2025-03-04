# physical-design-homework1-parser

![GitHub repo size](https://img.shields.io/github/repo-size/ysnanako/physical-design-homework1-parser)
![GitHub last commit](https://img.shields.io/github/last-commit/ysnanako/physical-design-homework1-parser)

This project is part of the **National Cheng Kung University (NCKU) - VLSI/CAD Group** course **"Physical Design for Nanometer IC"**, focusing on parsing the **Bookshelf** format `.aux` file and generating `.dat` output files for visualizing chip layouts.

## 📖 Table of Contents
- [Project Overview](#project-overview)
- [Input Format](#input-format)
- [Output Format](#output-format)
- [Project Structure](#project-structure)
- [Parsing Flow](#parsing-flow)
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
2. Generating output files:
   - `.dat` - Data files storing parsed chip layout information.
   - `.plt` - Gnuplot scripts for visualization.

## 📄 Input Format
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

## 🧰 Project Structure
```
📂 physical-design-homework1-parser/
│── 📂 src/ # (main.cpp, parser.cpp, datatype.cpp, and headers)
│── 📂 obj/ # (ignored)
│── 📂 plt/ # (ignored in Git, automatically generated)
│── 📂 dat/ # (ignored in Git due to large size, automatically generated)
│── 🖥️ HW1_StudentID # (ignored)
│── 🔧 Makefile
│── 📜 README.md # This file
│── 📜 .gitignore

../📂 benchmarks/ # (located outside the repo)

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

**adaptec1**  
![adaptec1](https://github.com/user-attachments/assets/09f5d401-fee3-46cd-b48d-7a336de86010)  
**adaptec2**  
![adaptec2](https://github.com/user-attachments/assets/c7ab4d4e-588e-4f27-bd2c-6dc2024882bf)  
**adaptec3**  
![adaptec3](https://github.com/user-attachments/assets/66b46e68-b2ce-486e-bbd8-322ecbf2d06f)  
**adaptec4**  
![adaptec4](https://github.com/user-attachments/assets/7477fb03-103c-4bcb-8945-2e77b7482bff)  
**bigblue1**  
![bigblue1](https://github.com/user-attachments/assets/91bbacfe-57e5-4794-ad7d-bb3354fb5266)  
**bigblue2**  
![bigblue2](https://github.com/user-attachments/assets/dff18cc7-2947-4346-80b5-c173842fe564)  
**bigblue3**  
![bigblue3](https://github.com/user-attachments/assets/c47068a3-3525-450c-8767-cd28a4a3579d)  
**bigblue4**   
![bigblue4](https://github.com/user-attachments/assets/bdddc174-ce87-406d-879b-e6d3ffda5956)  

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
