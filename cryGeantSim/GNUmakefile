####################################################
# GEANT4 GDML
#
# File:      GNUMakefile
#
#
# Date:      11/9/2012
####################################################

name := read
G4TARGET := $(name)
G4EXLIB := true

EXTRALIBS += -L$(CRYHOME)/lib -lCRY
EXTRALIBS += $(shell root-config --glibs)
CPPFLAGS  += -I$(CRYHOME)/src
CPPFLAGS += -I$(shell root-config --incdir)

#....make sure geant uses static (not shared) libraries
export G4LIB_BUILD_STATIC=1
export G4LIB_BUILD_SHARED=

.PHONY: all
all: check lib bin

### G4ANALYSIS_USE := true

include $(G4INSTALL)/config/binmake.gmk

#
#....Check that GEANT and CRY are properly installed
#
check:
ifndef G4INSTALL
	@echo G4INSTALL not defined, please setup GEANT4 environment.; false
endif
ifndef CRYHOME
	@echo CRYHOME not defined, please setup CRY using: source ../setup; false
endif
