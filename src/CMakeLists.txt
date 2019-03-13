cmake_minimum_required(VERSION 2.8) 

PROJECT(ResourcePackage)
 
INCLUDE_DIRECTORIES(../include) 
INCLUDE_DIRECTORIES(../../platform/include/)

AUX_SOURCE_DIRECTORY(. ResourcePackage)

ADD_LIBRARY (ResourcePackage SHARED ${ResourcePackage})
