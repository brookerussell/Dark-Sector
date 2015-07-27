cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(read)

#set(useROOT true)

#-------------------- CMAKE USER-SPECIFIC INFO ------------------------

#Root
include_directories(/home/mina/BasicSoftware/ROOT/v5_34_24/include /home/mina/BasicSoftware/ROOT/v5_34_24)

set(ROOT_LIBRARIES -L/home/mina/BasicSoftware/ROOT/v5_34_24/lib -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic)

#CRY
include_directories(/home/mina/BasicSoftware/cry/cry_v1.7/src)

set(CRY_LIBRARIES -L/home/mina/BasicSoftware/cry/cry_v1.7/lib -lCRY)

#Mina's LArLite Info
set(LARLITE_DIR /home/mina/BasicSoftware/LArLite)
include_directories(${LARLITE_DIR}/UserDev/Mina/DStudy)
set(LARLITE_LIB -L${LARLITE_DIR}/lib -lMina_DStudy)


#----------------------------------------------------------------------
#all vis and ui drivers on
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

# GEANT4 core
find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

# User code
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(read read.cc ${sources} ${headers})

target_link_libraries(read ${LARLITE_LIB} ${Geant4_LIBRARIES} ${CRY_LIBRARIES} ${ROOT_LIBRARIES})
