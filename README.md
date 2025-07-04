MyOpenCVProject

 A simple OpenCV project demonstrating C++ and OpenCV functions.

 ## Prerequisites
 - **OpenCV**: Version 4.11.0 (pre-built Windows version recommended).
 - **CMake**: Version 3.10 or higher.
 - **Visual Studio**: 2022 (or compatible version) with C++ support.
 - **Compiler**: MSVC (or MinGW for alternative setups).

 ## Setup
 1. **Install OpenCV**:
    - Download and install OpenCV 4.11.0 for Windows from [OpenCV releases](https://opencv.org/releases/).
    - Set the environment variable `PATH` to include `C:/opencv/build/x64/vc16/bin` (adjust for your installation path).

 2. **Clone the repository**:
    ```bash
    git clone https://github.com/your-username/MyOpenCVProject.git
    cd MyOpenCVProject
    ```

 3. **Prepare test image**:
    - Place a test image named `test.jpg` in the project root directory.

 4. **Build the project**:
    ```bash
    mkdir build
    cd build
    cmake .. -G "Visual Studio 17 2022" -A x64 -DOpenCV_DIR=C:/opencv/build
    ```
    - Open `MyOpenCVProject.sln` in Visual Studio.
    - Build the solution (`F7`) in `Release` or `Debug` mode.

 5. **Run the project**:
    - In Visual Studio, set `MyOpenCVProject` as the startup project.
    - Set the working directory to the project root (containing `test.jpg`).
    - Run (`F5` or `Ctrl+F5`).

 ## Project Structure
 - `traincxx.cpp/h`: Implements a simple C++ function (e.g., sum).
 - `trainopen.cpp/h`: Implements an OpenCV function (e.g., grayscale conversion).
 - `main.cpp`: Tests both functions and displays results.

 ## Notes
 - Ensure `00005.png` is in the project root or adjust the path in your customized path.
 - If running outside Visual Studio, copy `opencv_world4110.dll` to the executable directory or add it to `PATH`.
