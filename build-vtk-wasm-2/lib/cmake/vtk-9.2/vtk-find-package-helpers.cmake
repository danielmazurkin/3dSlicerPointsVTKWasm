if (NOT DEFINED "SDL2_DIR" OR NOT SDL2_DIR)
  set("SDL2_DIR" "/emsdk/upstream/emscripten/cache/sysroot/lib/cmake/SDL2" CACHE PATH "Third-party helper setting from ${CMAKE_FIND_PACKAGE_NAME}")
endif ()
