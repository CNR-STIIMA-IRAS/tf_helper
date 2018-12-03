cmake_minimum_required(VERSION 2.8.3)
project(tf_helper)

add_compile_options(-std=c++11 -funroll-loops  -Ofast)
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  tf
)


catkin_package(
  INCLUDE_DIRS 
  LIBRARIES 
  CATKIN_DEPENDS  geometry_msgs
                  roscpp
                  tf
  DEPENDS 
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

# add_library(${PROJECT_NAME}
#   src/${PROJECT_NAME}/tf_helper.cpp
# )
# add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(${PROJECT_NAME}_node src/tf_helper_node.cpp)
add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
)

add_executable(tf_photo src/tf_photo.cpp)
add_dependencies(tf_photo ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(tf_photo
  ${catkin_LIBRARIES}
)

install(TARGETS ${PROJECT_NAME}_node tf_photo #${PROJECT_NAME} 
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".svn" EXCLUDE
)
