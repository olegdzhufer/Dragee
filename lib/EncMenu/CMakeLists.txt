# EncMenu Navigation System Library
# https://github.com/VladVanyuk/MakeMenuLib
# MIT License

cmake_minimum_required(VERSION 3.5)

idf_component_register(SRCS "EncMenu_priv.cpp." "EncMenu.cpp" 
                       INCLUDE_DIRS "."
                       REQUIRES arduino)

project(EncMenu)