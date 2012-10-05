file(GLOB_RECURSE engine_SOURCES *.cpp *.h)
file(GLOB_RECURSE util_src Util/*)
file(GLOB_RECURSE memory_src Memory/*)
file(GLOB_RECURSE core_src Core/*)
file(GLOB_RECURSE event_src Event/*)
file(GLOB_RECURSE io_src IO/*)

if(BUILD_STATIC)
    set(BUILD_MODE STATIC)
else()
    set(BUILD_MODE SHARED)
endif()

source_group(Core FILES ${core_src})
source_group(Util FILES ${util_src})
source_group(Memory FILES ${memory_src})
source_group(Event FILES ${event_src})
source_group(IO FILES ${io_src})

include_directories(${PROJECT_SOURCE_DIR}/engine)

add_library(Prelude ${BUILD_MODE}
	${engine_SOURCES}
)

install(TARGETS Prelude
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
