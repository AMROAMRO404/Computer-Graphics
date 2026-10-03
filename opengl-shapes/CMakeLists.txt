find_package(OpenGL REQUIRED)

add_executable(shapes
   main.cpp
   RenderWidget.cpp
   RenderWidget.h
)
target_link_libraries(shapes PRIVATE viewer OpenGL::GL)

# QOpenGLWidget lives in its own module since Qt 6
if (QT_VERSION_MAJOR GREATER_EQUAL 6)
   find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)
   target_link_libraries(shapes PRIVATE Qt6::OpenGLWidgets)
endif()

if (APPLE)
   # this program uses the classic fixed-function API on purpose
   target_compile_definitions(shapes PRIVATE GL_SILENCE_DEPRECATION)
endif()
