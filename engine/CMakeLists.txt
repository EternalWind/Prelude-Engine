file(GLOB_RECURSE engine_SOURCES *.cpp *.h)
file(GLOB_RECURSE util_src Util/*)
file(GLOB_RECURSE memory_src Memory/*)
file(GLOB_RECURSE core_src Core/*)

source_group(core FILES ${core_src})
source_group(util FILES ${util_src})
source_group(memory FILES ${memory_src})

include_directories(${PROJECT_SOURCE_DIR}/engine)

add_library(engine ${BUILD_MODE}
	${engine_SOURCES}
)


