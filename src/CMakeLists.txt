file(GLOB hdrs "*.h")
file(GLOB srcs "main.cpp" "jsoncpp.cpp")

add_executable(cubemap ${hdrs} ${srcs})
target_link_libraries(cubemap ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
install(TARGETS cubemap DESTINATION .)