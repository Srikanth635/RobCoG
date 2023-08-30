# UProtobuf
* Unreal Engine Third Party Plugin of the google protobuf libraries
* current protobuf version `3.12.3`

## Usage
#### Include the plugin in the project
* Add the plugin to your project (e.g `MyProject/Plugins/UProtobuf`)
* Add the module dependency to your module (Project, Plugin);
In the `MyModule.Build.cs` file:
```
        PublicDependencyModuleNames.AddRange(  
		new string[]  
		{  
		...  
		"UProtobuf",
		...  
		}  
		);  
```
#### Compile the *.proto file
* The protobuf compiler protoc.exe is under the folder `UProtobuf/Source/ThirdParty/tools`
* Use protoc.exe to compile the .proto file to generate .pb.cc and .pb.h files. (eg `.\protoc.exe --cpp_out=. .\<My Proto>.proto`) 

#### Build protobuf library from source code in Window
* Protobuf installation tutorial links
`https://github.com/protocolbuffers/protobuf/blob/master/src/README.md`
`https://github.com/protocolbuffers/protobuf/blob/master/cmake/README.md`
* Unreal Engine requires the Runtime Library property of protobuf library is 'MD_DynamicRelease'. To change the Runtime Library property, change the file `protobuf-3.12.3\cmake\CMakeLists.txt`, before compiling. To change the property from 'MT' to 'MD', simply just comment these three lines.

```
  if (MSVC AND protobuf_MSVC_STATIC_RUNTIME)
    foreach(flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
#      if(${flag_var} MATCHES "/MD")
#        string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
#      endif(${flag_var} MATCHES "/MD")
    endforeach(flag_var)
  endif (MSVC AND protobuf_MSVC_STATIC_RUNTIME)
```