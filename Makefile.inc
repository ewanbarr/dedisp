# The definitions in this file should be changed to match your system

# CUDA paths
CUDA_PATH ?= /usr/local/cuda
CUDA_DIR   ?= $(CUDA_PATH)
THRUST_DIR ?= $(CUDA_DIR)/include
INSTALL_DIR ?= /usr/local

# Architecture and compiler settings
LIB_ARCH   = lib64
GCC        = gcc
GXX        = g++
AR         = ar
NVCC       = $(CUDA_DIR)/bin/nvcc
DOXYGEN    = doxygen
RM         = rm
ECHO       = echo
MKFLAGS    =

DEDISP_DEBUG = 0

# Detect CUDA version
CUDA_VERSION ?= $(shell $(NVCC) --version | grep -oP 'release \K[0-9]+\.[0-9]+' | head -1)

# Set GPU architecture flags dynamically based on CUDA version
GPU_ARCH_FLAG =

ifeq ($(CUDA_VERSION),)
    $(warning "CUDA version not detected, using default compute capabilities")
    GPU_ARCH_FLAG = -gencode arch=compute_60,code=sm_60 -gencode arch=compute_61,code=sm_61 -gencode arch=compute_75,code=sm_75
else
    CUDA_MAJOR := $(shell echo $(CUDA_VERSION) | cut -d'.' -f1)
    CUDA_MINOR := $(shell echo $(CUDA_VERSION) | cut -d'.' -f2)

    ifneq ($(shell expr $(CUDA_MAJOR) \>= 10), 0)
        GPU_ARCH_FLAG += -gencode arch=compute_60,code=sm_60 -gencode arch=compute_61,code=sm_61 -gencode arch=compute_70,code=sm_70
    endif
    ifneq ($(shell expr $(CUDA_MAJOR) \>= 11), 0)
        GPU_ARCH_FLAG += -gencode arch=compute_75,code=sm_75
    endif
    ifneq ($(shell expr $(CUDA_MAJOR) \>= 11 \& $(CUDA_MINOR) \>= 2), 0)
        GPU_ARCH_FLAG += -gencode arch=compute_80,code=sm_80
    endif
    ifneq ($(shell expr $(CUDA_MAJOR) \>= 11 \& $(CUDA_MINOR) \>= 8), 0)
        GPU_ARCH_FLAG += -gencode arch=compute_86,code=sm_86
    endif
    ifneq ($(shell expr $(CUDA_MAJOR) \>= 12), 0)
        GPU_ARCH_FLAG += -gencode arch=compute_89,code=sm_89
    endif
    ifneq ($(shell expr $(CUDA_MAJOR) \>= 12 \& $(CUDA_MINOR) \>= 2), 0)
        GPU_ARCH_FLAG += -gencode arch=compute_90,code=sm_90
    endif
endif


