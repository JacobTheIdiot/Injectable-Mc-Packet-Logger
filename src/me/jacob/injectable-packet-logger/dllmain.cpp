// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <iostream>
#include "jni/jni.h"
#include "features/logger.h"
FILE* pfile = nullptr;

JavaVM* jvm = nullptr;
JNIEnv* env = nullptr;

void init(HMODULE hModule) {

	AllocConsole();
	freopen_s(&pfile, "CONOUT$", "w", stdout);
	std::cout << "packet logger injected!" << std::endl;

    jsize vmCount;
	if (JNI_GetCreatedJavaVMs(&jvm, 1, &vmCount) != JNI_OK || vmCount == 0) {
		std::cerr << "failed to get java vm" << std::endl;
		return;
	}
	jint res = jvm->AttachCurrentThread((void**)&env, nullptr);
	if (res != JNI_OK) {
		std::cerr << "failed to attach to java vm" << std::endl;
		return;
	}

	if (env == nullptr) {
		std::cerr << "failed to get jni env" << std::endl;
		return;
	}

	std::cout << "successfully attached to Java vm!" << std::endl;

	log_packets(env, jvm);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)init, hModule, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

