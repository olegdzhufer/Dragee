# Virtual base class for LiquidCrystal and LiquidCrystal_I2C libraries
# https://github.com/VladVanyuk/LiquidCrystal
# MIT License

cmake_minimum_required(VERSION 3.5)

idf_component_register(SRCS "CharOperation.cpp" "Menulib.cpp" "Menu.cpp" "initBlock.cpp"
                       INCLUDE_DIRS ".", "./coreMenu"
                       REQUIRES arduino)

project(LiquidCrystal_Base)