# Parking Management System in C

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Area](https://img.shields.io/badge/Area-Data_Structures-red.svg)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A comprehensive command-line interface (CLI) application developed in C to manage a parking lot system. This project demonstrates the use of modular programming, dynamic memory allocation, linked lists, and file persistence.



## ℹ️ About
This project was developed as a Computer Science assignment. It simulates a real-world parking scenario where an administrator can manage users (drivers), register their vehicles, choose billing plans (Daily, Monthly, Annual), and control vehicle entry/exit. All data is saved locally to ensure persistence between sessions.



## ✨ Features
* **User Management:** Register, select, search, and delete users (drivers).
* **Vehicle Management:** Add, remove, and list vehicles associated with a specific user.
* **Parking Operations:**
    * Check-in vehicles (Entry).
    * Check-out vehicles (Exit) with automatic status updates.
    * List all currently parked vehicles.
* **Billing System:**
    * Support for different vehicle types: **Car (Large/Small)** and **Motorcycle**.
    * Support for different plans: **Daily**, **Monthly**, and **Annual**.
    * Real-time balance checks and payment processing.
    * Financial report (Cash flow).
* **Data Persistence:** Automatic saving and loading of data using text files (`dados_usuarios.txt`).



## 📂 Project Structure
The project follows a modular structure to separate logic from definitions:


```

c-parking-management-system-cli/
├── include/        # Header files (.h) - Prototypes and Structs
│   ├── pagamento.h
│   ├── usuario.h
│   └── veiculo.h
├── src/            # Source files (.c) - Implementation
│   ├── main.c
│   ├── pagamento.c
│   ├── usuario.c
│   └── veiculo.c
├── .gitignore      # Git ignore file
├── LICENSE         # License file
└── README.md       # Project documentation

```



## 🧠 Concepts Applied
* **Structs & Typedefs:** To model Users and Vehicles.
* **Pointers:** Extensive use of pointers for memory manipulation.
* **Dynamic Memory Allocation:** Using `malloc`, `realloc`, and `free`.
* **Data Structures:** Singly Linked Lists to manage users and their vehicles dynamically.
* **File I/O:** Reading and parsing text files to save/load state.
* **Modularization:** Separation of concerns using header files and source files.
* **Input Validation:** Robust handling of user inputs (strings, integers) to prevent buffer overflows.



## 🚀 Getting Started


### Prerequisites
You need a C compiler installed on your machine.
* **Windows:** MinGW or GCC via WSL.
* **Linux/macOS:** GCC.


### Compilation
Since this project uses a modular structure, you need to tell the compiler where to find the header files (`-I include`) and compile all source files together.

Open your terminal in the project root folder and run:
```bash
gcc src/main.c src/usuario.c src/veiculo.c src/pagamento.c -I include -o estacionamento
```

### Running the App
**On Linux/macOS:**
```bash
./estacionamento
```

**On Windows:**
```cmd
estacionamento.exe
```

## 🛠 Usage

1. **Register a User:** Start by creating a user profile with a Name and CPF.
2. **Select User:** Log in as that user to manage vehicles.
3. **Add Vehicle:** Register a car or motorcycle and choose a billing plan.
4. **Add Balance:** Add credits to the user's account to pay for parking.
5. **Park:** Use the "Estacionar Veiculo" option to check in.
6. **Exit:** Use "Retirar Veiculo" to leave.


---

## ⚠️ Language Note

Please note that the code comments are currently in **Portuguese**, as this project was originally developed for a university assignment.

## ✒️ Author

Developed by **Vitor Hugo Rodovalho**.

---

## 📜 License

MIT License.

