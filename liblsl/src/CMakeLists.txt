include_directories (${Boost_INCLUDE_DIRS} "/System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7")

add_library (lsl SHARED
  liblsl_wrap.cxx
  api_config.cpp
  consumer_queue.cpp
  continuous_resolver.cpp
  data_receiver.cpp
  dllmain.cpp
  freefuncs.cpp
  info_receiver.cpp
  inlet_connection.cpp
  lsl_continuous_resolver_c.cpp
  lsl_freefuncs_c.cpp
  lsl_inlet_c.cpp
  lsl_outlet_c.cpp
  lsl_streaminfo_c.cpp
  lsl_xml_element_c.cpp
  resolve_attempt_udp.cpp
  resolver_impl.cpp
  send_buffer.cpp
  stream_info.cpp
  stream_info_impl.cpp
  stream_inlet.cpp
  stream_outlet.cpp
  stream_outlet_impl.cpp
  tcp_server.cpp
  time_receiver.cpp
  udp_server.cpp
  xml_element.cpp
  pugixml/pugixml.cpp
)

if (WIN32)
  set_property (TARGET lsl PROPERTY COMPILE_DEFINITIONS BOOST_ALL_NO_LIB BOOST_THREAD_BUILD_LIB LIBLSL_EXPORTS _SCL_SECURE_NO_WARNINGS _CRT_SECURE_NO_WARNINGS)
  target_link_libraries (lsl ${Boost_LIBRARIES})
elseif (APPLE)
  target_link_libraries (lsl ${Boost_LIBRARIES} pthread)
elseif (UNIX)
  target_link_libraries (lsl ${Boost_LIBRARIES} rt pthread)
else ()
  target_link_libraries (lsl ${Boost_LIBRARIES})
endif ()
