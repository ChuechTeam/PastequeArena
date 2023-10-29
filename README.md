# Pasteque ARENA

Fighting + match 3 = ???

## Building

### Prerequisites

- CMake 3.21+
- C/C++ compiler
  - Linux: GCC or Clang
  - Windows: Microsoft Visual Studio 2022
- Git & Git LFS

**Required components for Android building**
- Android SDK with target API 33
- Android NDK r25+
- Android Studio 2022.2.1+
- Ninja build system (it must be in the PATH)   
  **Note:** On Windows you can use `winget` to install Ninja directly.

### Instructions (Desktop build)
1. Clone the repository somewhere, and change your working directory:
    ```sh
    git clone https://github.com/ChuechTeam/PastequeArena.git
    cd PastequeArena
    ```
2. Create a build directory and cd into it:
    ```sh
    mkdir build
    cd build
    ```
3. Prepare the build folder:
    ```sh
    cmake ..
    ```
4. Build the project (you can replace 8 by the number of cores you want to use):
    ```sh
   cmake --build . --target PastequeArena -j 8
    ```
5. Run the game! `PastequeArena` on Linux; `PastequeArena.exe` on Windows.

### Instructions (Android build)
Assuming you already have cloned the repository, the easiest way to get the
Android build running is to use Android Studio, which will run the Gradle
build script to automatically compile the CMake project. 

1. Make sure that the `ANDROID_SDK_ROOT` environment variable is set to the
Android SDK folder.
2. Open Android Studio, select `Open an existing project`
and choose the `Android` folder.
3. Run the app on your device or emulator!