cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 17)

project(RZD_Server_Client LANGUAGES CXX)

add_executable(Server
  RZD_Server_Impl.h
  RZD_Server.cpp
)

add_executable(Client
  Client.cpp
  Client.h
  RZD_Client_Impl.h
  Client.resx
)


set_target_properties(Client PROPERTIES COMMON_LANGUAGE_RUNTIME "")

target_compile_options(Client PRIVATE /fp:precise)

set_property(TARGET Client PROPERTY VS_GLOBAL_ROOTNAMESPACE RZD_Server_Client)

set_property(TARGET Client PROPERTY VS_GLOBAL_KEYWORD "ManagedCProj")

set_property(TARGET Client PROPERTY VS_GLOBAL_CLRSupport "true")

set_property(TARGET Client PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.0")

set_property(TARGET Client PROPERTY VS_DOTNET_REFERENCES "System" "System.Data" "System.Drawing" "System.Windows.Forms" "System.Xml")

string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")




