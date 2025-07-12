# 🗂️ Multithreaded Filesystem Indexer

A high-performance, multithreaded **filesystem indexer and search tool** written in C++. It recursively scans directories, indexes file metadata, and allows pattern-based searching using glob (`*.cpp`) or regular expressions. Fully containerized using Docker and portable across platforms (Linux, Windows via WSL or Git Bash).

---

## 🚀 Features

- 🔍 **Recursive directory indexing** using [Boost Filesystem](https://www.boost.org/doc/libs/release/libs/filesystem/)
- 🧵 **Multithreaded scanning** using `std::thread` and mutex-based synchronization
- 🧠 Supports both:
  - ✅ **Glob pattern matching** (`*.txt`, `*index*.cpp`, etc.)
  - ✅ **Regex matching** via C++ `<regex>`
- ⚙️ **Modular design**: separated indexing, searching, and CLI
- 📦 **Built with CMake** and linked against Boost libraries
- 🐳 **Dockerized** with one-liner execution via Bash script
- 🖥️ **Cross-platform support** (Windows WSL, Git Bash, Linux)

---

## 📂 Project Structure
- ├── include/            # indexer.hpp (class definition)
- ├── src/                # indexer.cpp, search.cpp, main.cpp
- ├── CMakeLists.txt      # CMake build config
- ├── Dockerfile          # Docker container definition
- ├── run_indexer.sh      # One-command build and run script
- └── README.md           # You're here!

---

## 🛠️ Technologies Used

- Language: **C++11**
- Libraries: **Boost Filesystem**, **Boost System**, **C++ STL (thread, mutex, regex)**
- Build System: **CMake**
- Containerization: **Docker**
- Shell Tools: **Bash**

---

## 📥 How to Clone and Run

### 🔧 Prerequisites

- [Docker](https://www.docker.com/products/docker-desktop)
- Git Bash (Windows) or WSL / Linux terminal

---

### 📦 Clone the Repository

```bash
git clone https://github.com/Likhith-Lochan/file-indexer-cpp.git
cd filesystem-indexer

./run_indexer.sh /data "*.cpp" --regex

