// Copyright 2017-2020, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

using UnrealBuildTool;
using System;
using System.IO;

public class MongoC : ModuleRules
{
	// Path to the plugins binary folder
	private string BinariesPath
	{
		get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "..", "..", "Binaries")); }
	}

	// Append platform folder (e.g. /Win64) to binary path
	private string BinariesPlatformPath
	{
		get { return Path.Combine(BinariesPath, Target.Platform.ToString()); }
	}

	// Helper function to copy libraries from third party folder to the plugins binary folder
	private void CopyToBinariesFolder(string SourceFilePath, ReadOnlyTargetRules Target)
	{
		// Get filename from path
		string Filename = Path.GetFileName(SourceFilePath);

		if (!Directory.Exists(BinariesPlatformPath))
		{
			Directory.CreateDirectory(BinariesPlatformPath);
			System.Console.WriteLine("[UMongoC] Creating directory {0}", BinariesPlatformPath);
		}

		if (!File.Exists(Path.Combine(BinariesPlatformPath, Filename)))
		{
			File.Copy(SourceFilePath, Path.Combine(BinariesPlatformPath, Filename), true);
			System.Console.WriteLine("[UMongoC] Copying {0} to {1}", SourceFilePath, BinariesPlatformPath);
		}
	}

	public MongoC(ReadOnlyTargetRules Target) : base(Target)
	{
		// We are just setting up paths for pre-compiled binaries.
		Type = ModuleType.External;

		//bEnableUndefinedIdentifierWarnings = false;
		//bEnableExceptions = true;
		//bUseRTTI = true;


		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// .h
			string HeadersDir = Path.Combine(ModuleDirectory, "mongo-c-driver", "include");
			PublicIncludePaths.Add(Path.Combine(HeadersDir, "libbson-1.0"));
			PublicIncludePaths.Add(Path.Combine(HeadersDir, "libmongoc-1.0"));

			// .lib
			string LibsDir = Path.Combine(ModuleDirectory, "mongo-c-driver", "lib");
			PublicAdditionalLibraries.Add(Path.Combine(LibsDir, "bson-1.0.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(LibsDir, "mongoc-1.0.lib"));

			// .dll
			string BinDir = Path.Combine(ModuleDirectory, "mongo-c-driver", "bin");
			//RuntimeDependencies.Add(Path.Combine(BinDir, "libbson-1.0.dll"));
			//RuntimeDependencies.Add(Path.Combine(BinDir, "libmongoc-1.0.dll"));

			// Copy dll's to plugin /Binaries
			CopyToBinariesFolder(Path.Combine(BinDir, "libbson-1.0.dll"), Target);
			CopyToBinariesFolder(Path.Combine(BinDir, "libmongoc-1.0.dll"), Target);
		}
		else if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			Console.WriteLine("Using Linux Mongo/BSON library files");
			// .h
			string HeadersDir = Path.Combine(ModuleDirectory, "mongo-c-driver-linux", "include");
			PublicIncludePaths.Add(Path.Combine(HeadersDir, "libbson-1.0"));
			PublicIncludePaths.Add(Path.Combine(HeadersDir, "libmongoc-1.0"));

			// .lib
			string LibsDir = Path.Combine(ModuleDirectory, "mongo-c-driver-linux", "lib");
			PublicAdditionalLibraries.Add(Path.Combine(LibsDir,"libbson-static-1.0.a"));
			PublicAdditionalLibraries.Add(Path.Combine(LibsDir,"libmongoc-static-1.0.a"));
		}
	}
}
