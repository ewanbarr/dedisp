# The definitions in this file should be changed to match your system

CUDA_PATH ?= /usr/local/cuda

CUDA_DIR   ?= $(CUDA_PATH)
THRUST_DIR ?= $(CUDA_DIR)/include
INSTALL_DIR ?= /usr/local

# LIB_ARCH   = lib
LIB_ARCH   = lib64

GCC        = gcc
GXX        = g++
AR         = ar
NVCC       = $(CUDA_DIR)/bin/nvcc -Xptxas -abi=no
DOXYGEN    = doxygen
RM         = rm
ECHO       = echo
MKFLAGS    = 

DEDISP_DEBUG = 0

#.SILENT :
