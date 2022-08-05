set(math_INCLUDE_DIR)
list(APPEND math_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")
#list(APPEND math_INCLUDE_DIR "${OpenCV_INCLUDE_DIRS}")

set(math_INCLUDE_DIRS ${math_INCLUDE_DIR} CACHE PATH "math include directories")