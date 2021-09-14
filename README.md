# Stellarlink

## Description

**StellarLink** is a 2D mini game / **Fall Physic Simulator** written in **Qt/QML**, **C++** and **JavaScript**.

In the game, you have to cover the ***most distance*** as possible, with the ***most speed*** as possible and reaching the ***most heigth*** as possible, while keeping the ***health bar above 0***. To do so, you will have to avoid hitting stiff egde by using the control button `←`, `↑` and `→` . 

## Screenshots

## Play

### Dependencies

The only one dependency is [**Qt Creator**](https://www.qt.io/download). The Game was tested using [**Qt 5.15.2**](https://www.qt.io/blog/qt-5.15.2-released). The needed Modules are:
- **Core**
- **Quick**
- **Qml**
- **Gui**
- **QuickControls2**

**Note:** All those modules are **included** in the installation of Qt

### Building

- To build the app, jsut open ``.\CMakeLists.txt`` with **Qt Creator**, and select a Kit from **QT5**
- After that, just run the project.

**Note:** If there are compile errors, you will need to change your **CMake Tool** in your kit. To do, open the the [**manege kits window**](https://doc.qt.io/qtcreator/creator-configuring-projects.html), click on ``add`` and add a new kit with the same specifications as the kit choosen before. Then **change the ``CMake Tool`` to ``CMake (Qt)``**

### Run

After running the project, the game should open soon. You can then play the game and have fun

## Bugs and Issues

If you encounter anything odd with the game, or problem while building/running the project feel free to report an [**issue**](https://github.com/JosephBisso/Stellarlink/issues).

# Other Game Project

- [**Card Game**](https://github.com/JosephBisso/Cardgame)
