# Qt6 Event Manager

A desktop event management application built using **C++ and Qt6**, implementing an MVC-inspired architecture, file persistence, validation logic, and data visualization through custom widgets.

---

## 🚀 Features

- Add / remove / manage events
- File-based persistence (CSV & TXT)
- Export events to:
  - CSV format
  - HTML format
- Custom chart visualization
- Input validation with custom exceptions
- Layered architecture (UI, Controller, Repository)
- Qt Widgets GUI
- Separation of concerns (clean structure)

---

## 🏗️ Architecture

The project follows a layered architecture similar to MVC:

### Presentation Layer (GUI)
- `mainwindow.*`
- `EventListView.*`
- `chartwidget.*`
- `mainwindow.ui`

Handles:
- User interaction
- Data visualization
- UI updates

### Business Logic Layer
- `controller.*`
- `eventValidator.h`

Handles:
- Application logic
- Validation rules
- Communication between GUI and repository

### Data Layer
- `repo.*`
- `event.*`
- `WriteToFile.*`
- `CSVWriteToFile.h`
- `HTMLWriteToFile.h`
- `repoException.h`

Handles:
- Event storage
- File reading/writing
- Custom exceptions

---

## 📊 Technologies Used

- **C++**
- **Qt 6 (Qt Widgets)**
- **Qt Charts**
- **OOP principles**
- **MVC-inspired architecture**
- **File I/O**
- **Exception handling**

---

## 💾 Data Persistence

The application uses:

- `events.csv` → main event storage
- `user_events.txt` → user-specific events
- HTML export functionality
- CSV export functionality

---

## 🧠 Concepts Implemented

- Object-Oriented Programming (OOP)
- Encapsulation
- Separation of concerns
- Exception handling
- Validation logic
- Repository pattern (file-based)
- Dynamic UI updates
- Data visualization

---

## 🖥️ How to Build & Run

### Requirements
- Qt 6.x
- Qt Creator (recommended) or CMake/IDE configured for Qt
- A compatible C++ compiler (MSVC / MinGW / Clang)

### Steps

1. Clone the repository:
```bash
git clone https://github.com/<your-username>/<repo-name>.git
cd <repo-name>
