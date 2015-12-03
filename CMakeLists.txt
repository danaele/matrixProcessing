cmake_minimum_required(VERSION 2.8)
 
PROJECT(matrixProcessing)

# Find SlicerExecutionModel
find_package(SlicerExecutionModel REQUIRED)
include(${SlicerExecutionModel_USE_FILE})

set(matrixProcessing_SOURCE matrixProcessing.cxx)

set(matrixProcessing_HEADER matrixProcessing.h)

SEMMacroBuildCLI(
  NAME matrixProcessing
  EXECUTABLE_ONLY
  ADDITIONAL_SRCS ${matrixProcessing_SOURCE}
  )
