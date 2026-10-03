# Scan-conversion algorithms: plain C++, no Qt
add_library(rasterizer STATIC
   Rasterizer.cpp
   Rasterizer.h
)
target_include_directories(rasterizer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(microscope
   main.cpp
   RenderWidget.cpp
   RenderWidget.h
)
target_link_libraries(microscope PRIVATE viewer rasterizer)

add_executable(rasterizer_test tests/RasterizerTest.cpp)
target_link_libraries(rasterizer_test PRIVATE rasterizer)
add_test(NAME rasterizer_test COMMAND rasterizer_test)
