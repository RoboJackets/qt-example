
# Qt Example Project

This is a quick walkthrough/tutorial on how to setup a simple Qt application.  The main window will have a text field, a button, and a list widget.  You type something in the field, then click the button to add that text to the list.

This project is setup as a git repo such that each step along the way that requires file changes is done for you ahead of time as a git commit.  It's best to follow through the directions on your own, but if you get stuck, you can see how how to do it by looking at these git commits.

To see how to do step six, you can do a git diff from step five to step six.

```shell
git diff step5..step6
```

The relevant commits have all been [tagged](http://git-scm.com/book/en/v2/Git-Basics-Tagging).  Type `git tag` to see a list.


## 1: project directory

Make a new folder for your app (can be named qt-example or whatever you want).

`mkdir qt-example`

Now that you've made your folder, move into it.

`cd qt-example`


## 2: initialize git repo

Git is a way of life.  Once you're comfortable with using it, it will become a key part of most every software project you work on.  To begin, git has to be initialized, which creates a `.git` directory in your folder.  Type `ls -a` to list all files (the -a flag tells ls to even show hidden files/folders).

`git init`


## 3: create main.cpp

Every C/C++ program is required to have a function called "main".  This function is what gets called when your program is run and when the main() function returns, your program is done running.  Below is a quick hello world main.cpp.  Start out by creating a similar file in your project folder.

```c++
//  main.cpp

//  the iostream header contains cout among other things
#include <iostream>

//  this declaration lets us leave of the "std::" when using things in the standard libraries
//  without it, we'd have to type "std::cout", not we can just type "cout"
using namespace std;


int main(int argc, char **argv) {
    cout << "Hello World" << endl;

    //  return 0 to indicate success
    return 0;
}
```


## 4: compile and run program

Our program doesn't do much yet (it just prints hello world), but let's verify that it works by compiling and running it.  First we'll invoke the c++ compiler (g++ or clang++, your choice) and tell it to compile `main.cpp` into an executable.  Next, we'll run our program and see it's output.

```shell
$ g++ main.cpp -o example # use the -o flag to tell the compiler what to name the output program
$ ./example
> Hello World
```


## 5: make it a Qt app

Qt is a popular GUI framework (among other things) for C++.  It provides things like windows, buttons, and text fields.  We'll start out by instantiating a QApplication object, which is the Qt class for managing an app.

In your main.cpp, you'll want to make an instance of QApplication.  Then at the end of your main() function, you'll return `app.exec()`.  The exec() method runs a loop that continues until the program is told to quit (maybe you clicked the "x" button in the corner of the main window).

```
QApplication app(argc, argv);

...

return app.exec();
```

In order to use the QApplication class, you'll have to include the appropriate header file, which declares the class and the methods available for you to call.  This include will go near the top of your main.cpp file.

```c++
#include <QtWidgets>
```


## 6: Add a window

Next, we'll add a window to our app that will display when the program is run.  Qt has a `QMainWindow` class for this purpose.  We'll make our own subclass of it so we can customize the functionality.  Let's call it `MainWindow`.

```c++
//  MainWindow.hpp

//  put "#pragma once" at the top of header files to protect against being included multiple times
#pragma once

#include <QtWidgets>


class MainWindow : public QMainWindow {
public:
    //  override the constructor
    MainWindow(QWidget * parent = 0, Qt::WindowFlags flags = 0);
};
```


```c++
//  MainWindow.cpp
#include "MainWindow.hpp"

//  note that we call the superclass constructor here and pass on the arguments
MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {

}
```

Now let's instantiate and display our MainWindow from the main() function so it actually shows up.

Place this code after the QApplication initialization in main.cpp.  Also, don't forget to include the MainWindow header file!

```c++
MainWindow win;
win.show()
```


## 7: build and run the project again

When we first built and run our program, we invoked the compiler directly.  We could do that again, but there are a couple differences.  We now have multiple source files, so we'd have to pass all those to the compiler.  More challenging though, we now have to tell the compiler where the Qt header files are and how to link against the Qt dynamic library.  Rather than do this manually, let's use CMake to handle this for us.

CMake works by looking at a `CMakeLists.txt` file in your folder for instructions on how to build the project.  Luckily for us, there are some built-in directions for working with Qt, which will make this easier.  Here's an example CMakeLists.txt file you can use:

```cmake
# the min version of CMake this file is compatible with
# a required part of every CMake file
cmake_minimum_required(VERSION 2.8)

project("Qt Example Project")

# find the location of Qt header files and libraries
find_package(Qt5Widgets REQUIRED)

# later on, we'll use Qt Creator to build out our UI
# Qt Creator creates .ui files which will be preprocessed for us (that's what qt5_wrap_ui does)
# After preprocessing, a .h and .cpp file are produced for each .ui file
# we add the binary output directory as an include directory so that we can include the .h file later on
file(GLOB example_UIS *.ui)
qt5_wrap_ui(example_UIS ${example_UIS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# tell CMake to compile every .cpp file in this directory and add it to an executable named `example`
file(GLOB example_SRC *.cpp)
add_executable(example ${example_SRC} ${example_UIS})

# this tells CMake where the header files and dynamic libraries are that we need
qt5_use_modules(example Widgets Core)
```


## 8: build project with CMake and run

CMake reads the CMakeLists.txt file and creates makefiles from it.  This means that after we run CMake, we need to run `make` to actually build our project.  We'll do this from a separate directory so the binaries don't clutter up our source directory.

```shell
mkdir build
cd build
cmake ..
make
```

You should now have an executable named `example` in the `build` folder.  Run it and your window should display.


## 9: add makefile to invoke CMake

This step is optional, but makes it easier to work with your project.  The way of running CMake described above is a little long to have to type each time.  We can replace all of those commands with just `make` by writing a makefile.  Save the below as `makefile` in your project.

```
# running `make` with no arguments builds the target named "all"
all:
    mkdir -p build
    cd build; cmake .. && make

# running `make clean` will remove all compiled stuff
clean:
    rm -rf build
```


## 10: add build directory to .gitignore

By default, git will track any file in your directory that you tell it to.  There are certain files that we never want to track though, such as compiled binaries.  We can tell git to never consider tracking these by adding them to the .gitignore file in the project directory.

```
# .gitignore
build/
```


## 11: git commit

Now that we've got a basic app running and displaying a window, let's make a git commit so we can always get back here if we need to.  It also helps show the progression of software development to create commits along the way.

```shell
git add --all
git commit -m "setup basic project to display a Qt window"
```


## 12: create MainWindow.ui

Using Qt Creator, make a window gui and save it as MainWindow.ui.  Add a PushButton, a text field, and a ListWidget.  When processed by Qt (when we invoke `cmake`), this will create a `ui_MainWindow.h` file in the build directory that contains the code to make a real window look just as it did in the creator.  Once we run `make` again, take a second to open it up and look at it.  The code that this generated is in the setupUi() method of Ui_MainWindow.

To add this to our MainWindow class, you'll first add an instance variable for the ui, then call setupUi in our constructor.

```c++
//  in the MainWindow declaration in MainWindow.hpp
Ui_MainWindow _ui;
```

```c++
//  in the constructor for MainWindow in MainWindow.cpp
_ui.setupUi(this);
```


## 13: add logic for the button press

We'll add a method `buttonClicked()` to our MainWindow class.  Declare it in the header, then implement it in the .cpp file like so:

```c++
//  MainWindow.cpp

void MainWindow::buttonClicked() {
    QString text = _ui.textField->text();
    _ui.listWidget->addItem(text);
}
```

To make this method get called when the button is clicked, we need to add what Qt calls a "connection", which is part of its signals and slots system.  A button emits a "clicked" signal when it's clicked.  Our buttonClicked() method on MainWindow will be a "slot".  To tie the two together, we'll add a connection in the MainWindow constructor.

```
//  MainWindow.cpp constructor

QObject::connect(_ui.button, &QPushButton::clicked, this, &MainWindow::buttonClicked);
```

The app should be functional now, so run `make` again and run your app!
