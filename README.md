# Hospital Management System

This project is a simple **Hospital Management System** implemented in the C programming language. It is designed to help manage hospital operations, including maintaining records of patients and doctors, scheduling appointments, and managing hospital resources.

## Features

- Add, update, delete, and search for patient records.
- Maintain doctor information and availability.
- Schedule and manage appointments.
- File-based data storage for persistence.

## Folder Structure

```
hospital-management-system/
│
├── src/
│   ├── code.c          # Main source code file
│   ├── patients.txt    # File to store patient records
│   └── doctors.txt     # File to store doctor information
│
├── README.md           # Project documentation
├── .gitignore          # Git ignore file
```

## How to Compile and Run

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/hospital-management-system.git
   cd hospital-management-system
   ```

2. Compile the program using `gcc`:
   ```bash
   gcc -o hospital src/main.c src/patient.c src/doctor.c
   ```

3. Run the executable:
   ```bash
   ./hospital
   ```

## Requirements

- GCC Compiler
- A terminal or command prompt

## Example Usage

- Start the program and choose options from the menu to:
  - Add new patients.
  - View patient or doctor records.
  - Schedule appointments.

## Contributing

Contributions are welcome! Feel free to submit a pull request or open an issue if you have suggestions or improvements.

## Author

Harshwardhan Nitin Chinchkhedkar

---

Thank you for checking out this project! If you have any questions, feel free to reach out.
