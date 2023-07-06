#
# This file has been primarily designed for the purpose of Slicer extension development.
#
# This file is configured by Slicer and used by UseSlicer.cmake module
# to load Slicer's settings for an external project. External projects
# can use these setting to build new modules against a Slicer build tree.
#
#

#
# When manually building extension on macOS, in addition to the usual configure
# option (CMAKE_BUILD_TYPE, ...), the developer is also expected to
# configure it passing the variables:
#   CMAKE_OSX_ARCHITECTURES
#   CMAKE_OSX_DEPLOYMENT_TARGET
#   CMAKE_OSX_SYSROOT
# The value of these variables should match the one used to
# configure the associated Slicer build tree. These values can be
# retrieved looking at the CMakeCache.txt file located in the Slicer
# build tree.
#
# To simplify the task of manually building out-of-source modules or extensions,
# the developer could include the following statement at the top of both the main
# CMakeLists.txt of the extension and also at the top of each module CMakeLists.txt
# bundled within the extension.
# Doing so will ensure that either the extension or each bundled module could be
# built in a standalone fashion very easily without passing extra option
# at configure time:
#
#  find_package(Slicer COMPONENTS ConfigurePrerequisites REQUIRED)
#
#  project(Foo)
#
#  [...]
#
#  find_package(Slicer REQUIRED)
#  include()
#  [...]


# Extension support can be disabled by either
#  (1) setting Slicer_DONT_USE_EXTENSION to TRUE or
#  (2) calling find_package(Slicer COMPONENTS NoExtensionSupport [...] REQUIRED)


# --------------------------------------------------------------------------
#  COMPONENTS                | CMAKE VARIABLE(S)
# --------------------------------------------------------------------------
#  NoExtensionSupport        | Slicer_USE_NOEXTENSIONSUPPORT
#                            | Slicer_DONT_USE_EXTENSION
# --------------------------------------------------------------------------
#  ConfigurePrerequisites    | Slicer_USE_CONFIGUREPREREQUISITES
# --------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.16.3...3.19.7 FATAL_ERROR)

foreach(component NoExtensionSupport ConfigurePrerequisites)
  string(TOUPPER  _COMPONENT)
  set(Slicer_USE_ 0)
endforeach()

if(Slicer_FIND_COMPONENTS)
  foreach(component )
    string(TOUPPER  _COMPONENT)
    set(Slicer_USE_ 1)
  endforeach()

  set(Slicer_DONT_USE_EXTENSION )
endif()

if(NOT DEFINED Slicer_DONT_USE_EXTENSION)
  set(Slicer_DONT_USE_EXTENSION FALSE)
endif()

if(NOT DEFINED Slicer_USE_CONFIGUREPREREQUISITES)
  set(Slicer_USE_CONFIGUREPREREQUISITES FALSE)
endif()

if(Slicer_SOURCE_DIR)
  return()
endif()

# --------------------------------------------------------------------------
set(Slicer_CMAKE_DIR "")
set(Slicer_EXTENSIONS_CMAKE_DIR "")
set(vtkAddon_CMAKE_DIR "")

# Update CMAKE_MODULE_PATH
set(CMAKE_MODULE_PATH
  
  
  
  ./slicer_mrml_repository/config_qt/Qt5
  )

# --------------------------------------------------------------------------
if(Slicer_USE_CONFIGUREPREREQUISITES)
  if(NOT Slicer_PREREQUISITES_CONFIGURED)
    if(DEFINED CMAKE_PROJECT_NAME)
      message(FATAL_ERROR
        "To be effective, 'find_package(Slicer COMPONENTS ConfigurePrerequisites)' should "
        "be placed before any calls to 'project()' or 'enable_language()'."
        "Before re-configuring, make sure to clean the build directory: /work/build"
        )
    endif()
    # Note: By setting CMAKE_OSX_* variables before any enable_language() or project() calls,
    #       we ensure that the bitness will be properly detected.
    include(SlicerInitializeOSXVariables)
    set(Slicer_PREREQUISITES_CONFIGURED 1 CACHE INTERNAL "True if component 'ConfigurePrerequisites' has already been included")
  endif()
  return()
endif()

# --------------------------------------------------------------------------
# Slicer options
# --------------------------------------------------------------------------
set(Slicer_DEFAULT_BUILD_TYPE "")
set(Slicer_USE_NUMPY "")
set(Slicer_USE_SCIPY "")
set(Slicer_USE_PYTHONQT "")
set(Slicer_USE_QtTesting "")
set(Slicer_USE_SimpleITK "")
set(Slicer_USE_TBB "")
set(Slicer_BUILD_BRAINSTOOLS "")
set(Slicer_BUILD_CLI_SUPPORT "")
set(Slicer_BUILD_DICOM_SUPPORT "")
set(Slicer_BUILD_DIFFUSION_SUPPORT "")
set(Slicer_BUILD_EXTENSIONMANAGER_SUPPORT "")
set(Slicer_BUILD_APPLICATIONUPDATE_SUPPORT "")
set(Slicer_BUILD_PARAMETERSERIALIZER_SUPPORT "")
set(Slicer_BUILD_TESTING "")
set(Slicer_BUILD_WEBENGINE_SUPPORT "")

set(Slicer_REQUIRED_QT_VERSION "")
set(Slicer_REQUIRED_QT_MODULES "")

# Launcher command
set(Slicer_USE_CTKAPPLAUNCHER "")
set(Slicer_LAUNCHER_EXECUTABLE "")
set(Slicer_LAUNCH_COMMAND "")
set(SEM_LAUNCH_COMMAND "")

# VCS commands
set(GIT_EXECUTABLE ""  CACHE FILEPATH "Git command line client")

# Slicer working copy Revision, URL and Root
set(Slicer_REVISION "")
set(Slicer_WC_REVISION "")
set(Slicer_WC_REVISION_HASH "")
set(Slicer_WC_URL "")
set(Slicer_WC_ROOT "")

# Note that the variable "Slicer_REVISION" can be forced to
# a particular value by setting environment variable of the same name.
# This is particularly useful when the revision of Slicer changes because of
# updates to the extension build system and the extensions still need to be
# built against the revision prior to the update.
if(NOT "" STREQUAL "")
  set(Slicer_REVISION "")
  message(STATUS "SlicerConfig: Forcing Slicer_REVISION to ''")
endif()

# Slicer os and architecture
set(Slicer_OS "")
set(Slicer_ARCHITECTURE "")

# Slicer main application
set(Slicer_MAIN_PROJECT "")
set(Slicer_MAIN_PROJECT_APPLICATION_NAME "")

# License and Readme file
set(Slicer_LICENSE_FILE "")
set(Slicer_README_FILE "")

# Path to qrcc.py script used in slicerFunctionAddPythonQtResources  CMake function
set(Slicer_QRCC_SCRIPT "")

# Test templates directory
set(Slicer_CXX_MODULE_TEST_TEMPLATES_DIR "")
set(Slicer_PYTHON_MODULE_TEST_TEMPLATES_DIR "")

# Script for generating <Extension>Config.cmake
set(Slicer_EXTENSION_GENERATE_CONFIG "")

# Path to extension CPack script
set(Slicer_EXTENSION_CPACK "")
set(Slicer_EXTENSION_CPACK_BUNDLE_FIXUP "")
set(Slicer_EXTENSIONS_DIRNAME "")

# Whether Slicer was built with modules and CLI support.
set(Slicer_BUILD_CLI "")
set(Slicer_BUILD_QTLOADABLEMODULES "")
set(Slicer_BUILD_QTSCRIPTEDMODULES "")

# Whether Slicer was built with shared libraries.
set(Slicer_BUILD_SHARED "")
set(Slicer_LIBRARY_PROPERTIES "")

# Export header for BuildModuleLogic and BuildQTModule
set(Slicer_EXPORT_HEADER_TEMPLATE "")
set(Slicer_LOGOS_RESOURCE "")

# Slicer home (top of the tree)
set(Slicer_HOME "")

# Slicer binary directory
set(Slicer_BINARY_DIR "")

# Slicer Core library
set(Slicer_CORE_LIBRARY )

# Slicer GUI library
set(Slicer_GUI_LIBRARY )

# MRML libraries - This variable regroup all related MRML libraries
set(MRML_LIBRARIES )

# Slicer Libs VTK wrapped libraries
set(Slicer_Libs_VTK_WRAPPED_LIBRARIES "")

# Slicer VTK version
set(Slicer_VTK_VERSION_MAJOR "")

# Slicer include directories for module


# Slicer include directories for module logic


# Slicer include directories for module mrml


# Slicer include directories for module Widget


# See vtkAddon/CMake/vtkMacroKitPythonWrap.cmake
set(Slicer_VTK_WRAP_HIERARCHY_DIR "")

# Slicer VTK wrap hierarchy files


# Slicer Libs include file directories.
set(Slicer_Libs_INCLUDE_DIRS "")

# Slicer Base include file directories.
set(Slicer_Base_INCLUDE_DIRS "" "")

# Slicer Module logic include file directories.
set(Slicer_ModuleLogic_INCLUDE_DIRS ""
  CACHE INTERNAL "Slicer Module logic includes" FORCE)

# Slicer Module MRML include file directories.
set(Slicer_ModuleMRML_INCLUDE_DIRS ""
  CACHE INTERNAL "Slicer Module MRML includes" FORCE)

# Slicer Module Widgets include file directories.
set(Slicer_ModuleWidgets_INCLUDE_DIRS ""
  CACHE INTERNAL "Slicer Module widgets includes" FORCE)

set(ITKFactoryRegistration_INCLUDE_DIRS ""
  CACHE INTERNAL "ITKFactoryRegistration includes" FORCE)

set(MRMLCore_INCLUDE_DIRS ""
  CACHE INTERNAL "MRMLCore includes" FORCE)

set(MRMLLogic_INCLUDE_DIRS ""
  CACHE INTERNAL "MRMLLogic includes" FORCE)

set(MRMLCLI_INCLUDE_DIRS ""
  CACHE INTERNAL "MRMLCLI includes" FORCE)

set(qMRMLWidgets_INCLUDE_DIRS ""
  CACHE INTERNAL "qMRMLWidgets includes" FORCE)

set(RemoteIO_INCLUDE_DIRS ""
  CACHE INTERNAL "RemoteIO includes" FORCE)

set(vtkAddon_INCLUDE_DIRS ""
  CACHE INTERNAL "vtkAddon includes" FORCE)

set(vtkITK_INCLUDE_DIRS ""
  CACHE INTERNAL "vtkITK includes" FORCE)

set(vtkSegmentationCore_INCLUDE_DIRS ""
  CACHE INTERNAL "vtkSegmentationCore includes" FORCE)

set(vtkTeem_INCLUDE_DIRS ""
  CACHE INTERNAL "vtkTeem includes" FORCE)

# The location of the UseSlicer.cmake file.
set(Slicer_USE_FILE "")

set(Slicer_BINARY_INNER_SUBDIR "")

# Slicer relative build directories.
set(Slicer_BIN_DIR "")
set(Slicer_LIB_DIR "")
set(Slicer_INCLUDE_DIR "")
set(Slicer_SHARE_DIR "")
set(Slicer_ITKFACTORIES_DIR "")

set(Slicer_CLIMODULES_SUBDIR "")
set(Slicer_CLIMODULES_BIN_DIR "")
set(Slicer_CLIMODULES_LIB_DIR "")
set(Slicer_CLIMODULES_SHARE_DIR "")

set(Slicer_QTLOADABLEMODULES_SUBDIR "")
set(Slicer_QTLOADABLEMODULES_BIN_DIR "")
set(Slicer_QTLOADABLEMODULES_LIB_DIR "")
set(Slicer_QTLOADABLEMODULES_INCLUDE_DIR "")
set(Slicer_QTLOADABLEMODULES_SHARE_DIR "")
set(Slicer_QTLOADABLEMODULES_PYTHON_LIB_DIR "")

if(Slicer_USE_PYTHONQT)
  set(Slicer_QTSCRIPTEDMODULES_SUBDIR "")
  set(Slicer_QTSCRIPTEDMODULES_BIN_DIR "")
  set(Slicer_QTSCRIPTEDMODULES_LIB_DIR "")
  set(Slicer_QTSCRIPTEDMODULES_INCLUDE_DIR "")
  set(Slicer_QTSCRIPTEDMODULES_SHARE_DIR "")
endif()

# ThirdParty: Corresponds to superbuild projects built
# in Slicer extension.
set(Slicer_THIRDPARTY_BIN_DIR "")
set(Slicer_THIRDPARTY_LIB_DIR "")
set(Slicer_THIRDPARTY_SHARE_DIR  "")

# Slicer Python version
set(Slicer_REQUIRED_PYTHON_VERSION "")
set(Slicer_REQUIRED_PYTHON_VERSION_MAJOR "")
set(Slicer_REQUIRED_PYTHON_VERSION_MINOR "")
set(Slicer_REQUIRED_PYTHON_VERSION_PATCH "")
set(Slicer_REQUIRED_PYTHON_VERSION_DOT "")

# Python stdlib and site-package sub-directories
set(PYTHON_STDLIB_SUBDIR "")
set(PYTHON_SITE_PACKAGES_SUBDIR "")

# Slicer install root
set(Slicer_INSTALL_ROOT "")

# Slicer relative install directories.
set(Slicer_INSTALL_BIN_DIR "")
set(Slicer_INSTALL_LIB_DIR "")
set(Slicer_INSTALL_INCLUDE_DIR "")
set(Slicer_INSTALL_SHARE_DIR "")
set(Slicer_INSTALL_ITKFACTORIES_DIR "")

set(Slicer_INSTALL_CLIMODULES_BIN_DIR "")
set(Slicer_INSTALL_CLIMODULES_LIB_DIR "")
set(Slicer_INSTALL_CLIMODULES_SHARE_DIR "")

set(Slicer_INSTALL_QTLOADABLEMODULES_BIN_DIR "")
set(Slicer_INSTALL_QTLOADABLEMODULES_LIB_DIR "")
set(Slicer_INSTALL_QTLOADABLEMODULES_PYTHON_LIB_DIR "")
set(Slicer_INSTALL_QTLOADABLEMODULES_INCLUDE_DIR "")
set(Slicer_INSTALL_QTLOADABLEMODULES_SHARE_DIR "")

if(Slicer_USE_PYTHONQT)
  set(Slicer_INSTALL_QTSCRIPTEDMODULES_BIN_DIR "")
  set(Slicer_INSTALL_QTSCRIPTEDMODULES_LIB_DIR "")
  set(Slicer_INSTALL_QTSCRIPTEDMODULES_INCLUDE_DIR "")
  set(Slicer_INSTALL_QTSCRIPTEDMODULES_SHARE_DIR "")
endif()

set(Slicer_INSTALL_THIRDPARTY_BIN_DIR "")
set(Slicer_INSTALL_THIRDPARTY_LIB_DIR "")
set(Slicer_INSTALL_THIRDPARTY_SHARE_DIR "")

# The Slicer install prefix (*not* defined in the install tree)
set(Slicer_INSTALL_PREFIX  "/emsdk/upstream/emscripten/cache/sysroot")


# --------------------------------------------------------------------------
# Testing
# --------------------------------------------------------------------------
include(CTestUseLaunchers)

# --------------------------------------------------------------------------
# External data
# --------------------------------------------------------------------------
if(NOT DEFINED Slicer_ExternalData_DATA_MANAGEMENT_TARGET)
  set(Slicer_ExternalData_DATA_MANAGEMENT_TARGET "")
endif()
if(NOT DEFINED SEM_DATA_MANAGEMENT_TARGET)
  set(SEM_DATA_MANAGEMENT_TARGET )
endif()
set(Slicer_ExternalData_OBJECT_STORES "")
set(Slicer_ExternalData_URL_TEMPLATES "")

# --------------------------------------------------------------------------
# External projects
# --------------------------------------------------------------------------

# With the help of SuperBuild, Slicer has been configured and built against a collection
# of external projects.
#
# Considering that, by default, Slicer and most of its dependent external projects are
# built as shared library, it's important to make sure that the project including
# SlicerConfig.cmake (this file) is built against the same set of external projects if it applies.
#
# Let's consider the example of a project dependending on both VTK and Slicer. With the help of
# the macro 'slicer_config_set_ep', the build system will check that the path of the already
# defined VTK_DIR matches the VTK_DIR used to build Slicer.
#
# A typical use of this macro is illustrated below:
#
#    slicer_config_set_ep("VTK_DIR", "")
#
#
macro(slicer_config_set_ep var value)
  if(NOT "" STREQUAL "")
    if(DEFINED )
      get_filename_component(var_realpath "" REALPATH)
      get_filename_component(value_realpath  REALPATH)
      if(NOT  STREQUAL )
        message(FATAL_ERROR "Variable  defined prior calling 'find_package(Slicer)' does NOT "
                            "match value used to configure Slicer. It probably means that a different "
                            " has been used to configure this project and Slicer.\n"
                            "=\n"
                            "Slicer_=")
      endif()
    endif()
    set( "" )
  endif()
endmacro()

# SlicerExecutionModel settings
set(SlicerExecutionModel_CLI_LIBRARY_WRAPPER_CXX "")
set(SlicerExecutionModel_EXTRA_INCLUDE_DIRECTORIES "")
set(SlicerExecutionModel_EXTRA_EXECUTABLE_TARGET_LIBRARIES "")

# Slicer external projects variables


# --------------------------------------------------------------------------
# Consistent Compiler Selections
# --------------------------------------------------------------------------
# Compilation Commands
set(Slicer_CMAKE_CXX_COMPILER "")
set(Slicer_CMAKE_C_COMPILER   "")

# With the help of SuperBuild, Slicer has been configured with specific compiler
#
# Considering that, by default, Slicer and most of its dependent external projects are
# built with a particular compiler, it's important to make sure that the project including
# SlicerConfig.cmake (this file) is built against the same compliant compiler
#
# A typical use of this macro is illustrated below:
#    slicer_config_set_compiler_ep("CMAKE_C_COMPILER", "")
#    slicer_config_set_compiler_ep("CMAKE_CXX_COMPILER", "")
#
macro(slicer_config_set_compiler_ep var value)
  if(NOT "" STREQUAL "")
    if(DEFINED )
      get_filename_component(var_realpath "" REALPATH)
      get_filename_component(value_realpath  REALPATH)
      if(NOT MSVC AND NOT  STREQUAL )
        message(FATAL_ERROR "Variable  defined prior calling 'find_package(Slicer)' does NOT "
                            "match value used to configure Slicer. It probably means that a different "
                            " has been used to configure this project and Slicer.\n"
                            "=\n"
                            "Slicer_=")
      endif()
    endif()
    set( "" )
  endif()
endmacro()
slicer_config_set_compiler_ep( CMAKE_C_COMPILER   ""
   CACHE PATH "Path to C compiler used in Slicer build" FORCE )
slicer_config_set_compiler_ep( CMAKE_CXX_COMPILER ""
   CACHE PATH "Path to CXX compiler used in Slicer build" FORCE )
slicer_config_set_compiler_ep( CMAKE_CXX_STANDARD ""
   CACHE PATH "C++ standard used in Slicer build" FORCE )
slicer_config_set_compiler_ep( CMAKE_CXX_STANDARD_REQUIRED ""
   CACHE PATH "Whether the specified C++ standard is a requirement in Slicer build" FORCE )
slicer_config_set_compiler_ep( CMAKE_CXX_EXTENSIONS ""
   CACHE PATH "Whether compiler specific extensions are requested in Slicer build" FORCE )

# On platform (i.e. Windows with Visual Studio) where it is possible to use
# either a 32 or 64 bits generator, it is important to compare bitness of Slicer
# project against project depending on Slicer (i.e. extension) to ensure there
# are no mismatch.
set(Slicer_CMAKE_SIZEOF_VOID_P "4")
set(Slicer_CMAKE_GENERATOR "Ninja")
if(NOT DEFINED Slicer_SKIP_CMAKE_SIZEOF_VOID_P_CHECK)
  set(Slicer_SKIP_CMAKE_SIZEOF_VOID_P_CHECK FALSE)
endif()
if(NOT )
  if(NOT Slicer_CMAKE_SIZEOF_VOID_P EQUAL CMAKE_SIZEOF_VOID_P)
    message(FATAL_ERROR
      "Mismatch between bitness of 'Cone' and 'Slicer' project !\n"
      "\tSlicer_CMAKE_SIZEOF_VOID_P:\n"
      "\tCMAKE_SIZEOF_VOID_P:4\n"
      "Reconfigure 'Cone' project using a compatible Generator.\n"
      "Generator used to configure Slicer was: \n"
      "See https://www.cmake.org/cmake/help/v2.8.11/cmake.html#opt:-Ggenerator-name")
  endif()
endif()

# List all required external project
set(Slicer_EXTERNAL_PROJECTS )
set(Slicer_EXTERNAL_PROJECTS_NO_USEFILE )



# Include external projects
foreach(proj )
  set(_component_args)
  if(DEFINED Slicer__COMPONENTS)
    set(_component_args COMPONENTS )
  endif()
  find_package(  REQUIRED)
  # Add project CMake dir to module path
  if(DEFINED _CMAKE_DIR)
    set(CMAKE_MODULE_PATH
      
      ./slicer_mrml_repository/config_qt/Qt5
      )
  endif()
  # Add project Utilities/CMake dir to module path
  if(DEFINED _CMAKE_UTILITIES_DIR)
    set(CMAKE_MODULE_PATH
      
      ./slicer_mrml_repository/config_qt/Qt5
      )
  endif()
endforeach()

# List all Slicer_USE_SYSTEM_* variables


# This block should be added after VTK and CTK are found.
# It will check if CTK_Qt5_DIR is valid.
include(/SlicerBlockFindQtAndCheckVersion.cmake)

# --------------------------------------------------------------------------
if(EXISTS "" AND NOT TARGET SlicerBaseLogic)
  include("")
endif()
