# CMakeList.txt : CMake project for ArtificialLife, include source and define
# project specific logic here.

# Set the path to the SFML package, which was manually installed.
set(SFML_PATH "C:/Users/JoHn/libs/SFML-3.0.0")

# Add SFML include and lib directories
include_directories(${SFML_PATH}/include)
link_directories(${SFML_PATH}/lib)

# Add source to this project's executable.
add_executable (ArtificialLife "ArtificialLife.cpp" "ArtificialLife.h" "Creature.cpp" "Creature.h"  "World.cpp" "World.h" "util.cpp" "util.h" "Slider.h"  "Slider.cpp" "Prey.cpp" "Prey.h" "Predator.h" "Predator.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ArtificialLife PROPERTY CXX_STANDARD 20)
endif()

# Tell CMake what SFML libraries we will use
target_link_libraries(ArtificialLife sfml-graphics sfml-window sfml-system)

# Copy SFML DLL files to the build file destination
add_custom_command(TARGET ArtificialLife POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${SFML_PATH}/bin"  # Location of the SFML DLLs
	"$<TARGET_FILE_DIR:ArtificialLife>"  # Output location.
)

# TODO: Add tests and install targets if needed.

# Suppress warnings
add_compile_options(/wd4275)
