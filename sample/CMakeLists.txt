file(GLOB_RECURSE sample_SOURCE *.cpp *.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/engine)

add_executable(Sample 
	${sample_SOURCE}
)

target_link_libraries(Sample Prelude)