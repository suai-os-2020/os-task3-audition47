#include <windows.h>
#include <iostream>
#include "lab3.h"

using namespace std;

#define THREAD_COUNT 9
#define SEMAPHORE_COUNT 3

DWORD ThreadID;
HANDLE hThread[THREAD_COUNT];
HANDLE hSemaphore[SEMAPHORE_COUNT];
HANDLE hMutex;

DWORD WINAPI thread_a(LPVOID);
DWORD WINAPI thread_b_sem(LPVOID);
DWORD WINAPI thread_c_sem(LPVOID);
DWORD WINAPI thread_e_sem(LPVOID);
DWORD WINAPI thread_d(LPVOID);
DWORD WINAPI thread_e(LPVOID);
DWORD WINAPI thread_f(LPVOID);
DWORD WINAPI thread_g(LPVOID);
DWORD WINAPI thread_h(LPVOID);
DWORD WINAPI thread_i(LPVOID);

unsigned int lab3_thread_graph_id()
{
    return 8;
}

const char* lab3_unsynchronized_threads()
{
    return "deg";
}

const char* lab3_sequential_threads()
{
    return "bce";
}

DWORD WINAPI thread_a(LPVOID lpParam)
{
	for (int i = 0; i < 3; i++) {
        	WaitForSingleObject(hMutex, INFINITE);
        	cout << "a" << flush;
        	computation();
        	ReleaseMutex(hMutex);
    	}

    	hThread[1] = CreateThread(NULL, 0, thread_b_sem, NULL, 0, &ThreadID);
    	if (hThread[1] == NULL) {
    		return GetLastError();
    	}

    	hThread[2] = CreateThread(NULL, 0, thread_c_sem, NULL, 0, &ThreadID);
    	if (hThread[2] == NULL) {
        	return GetLastError();
    	}

    	hThread[3] = CreateThread(NULL, 0, thread_e_sem, NULL, 0, &ThreadID);
    	if (hThread[3] == NULL) {
        	return GetLastError();
    	}

    	WaitForSingleObject(hThread[1], INFINITE);
    	WaitForSingleObject(hThread[2], INFINITE);
    	WaitForSingleObject(hThread[3], INFINITE);

    	CloseHandle(hThread[1]);
    	CloseHandle(hThread[2]);
   	CloseHandle(hThread[3]);

	return 0;
}

DWORD WINAPI thread_b_sem(LPVOID lpParam)
{
        for (int i = 0; i < 3; i++) {
                WaitForSingleObject(hSemaphore[0], INFINITE);
                WaitForSingleObject(hMutex, INFINITE);
                cout << "b" << flush;
                computation();
                ReleaseMutex(hMutex);
                ReleaseSemaphore(hSemaphore[1], 1, NULL);
        }
        return 0;
}

DWORD WINAPI thread_c_sem(LPVOID lpParam)
{
        for (int i = 0; i < 3; i++) {
                WaitForSingleObject(hSemaphore[1], INFINITE);
                WaitForSingleObject(hMutex, INFINITE);
                cout << "c" << flush;
                computation();
                ReleaseMutex(hMutex);
                ReleaseSemaphore(hSemaphore[2], 1, NULL);
        }
        return 0;
}

DWORD WINAPI thread_e_sem(LPVOID lpParam)
{
        for (int i = 0; i < 3; i++) {
                WaitForSingleObject(hSemaphore[2], INFINITE);
                WaitForSingleObject(hMutex, INFINITE);
                cout << "e" << flush;
                computation();
                ReleaseMutex(hMutex);
                ReleaseSemaphore(hSemaphore[0], 1, NULL);
        }

    	hThread[3] = CreateThread(NULL, 0, thread_e, NULL, 0, &ThreadID);
    	if (hThread[3] == NULL) {
        	return GetLastError();
    	}

    	hThread[4] = CreateThread(NULL, 0, thread_d, NULL, 0, &ThreadID);
    	if (hThread[4] == NULL) {
        	return GetLastError();
    	}

    	hThread[5] = CreateThread(NULL, 0, thread_g, NULL, 0, &ThreadID);
    	if (hThread[5] == NULL) {
        	return GetLastError();
    	}

    	WaitForSingleObject(hThread[3], INFINITE);
    	WaitForSingleObject(hThread[4], INFINITE);
    	WaitForSingleObject(hThread[5], INFINITE);

    	CloseHandle(hThread[3]);
    	CloseHandle(hThread[4]);
    	CloseHandle(hThread[5]);

	return 0;
}

DWORD WINAPI thread_e(LPVOID lpParam)
{
        for (int i = 0; i < 3; i++) {
                WaitForSingleObject(hMutex, INFINITE);
                cout << "e" << flush;
                computation();
                ReleaseMutex(hMutex);
        }
         return 0;
}

DWORD WINAPI thread_g(LPVOID lpParam)
{
        for (int i = 0; i < 3; i++) {
                WaitForSingleObject(hMutex, INFINITE);
                cout << "g" << flush;
                computation();
                ReleaseMutex(hMutex);
        }
        return 0;
}

DWORD WINAPI thread_d(LPVOID lpParam)
{
        for (int i = 0; i < 3; i++) {
                WaitForSingleObject(hMutex, INFINITE);
                cout << "d" << flush;
                computation();
                ReleaseMutex(hMutex);
        }
        hThread[5] = CreateThread(NULL, 0, thread_g, NULL, 0, &ThreadID);
        if (hThread[5] == NULL) {
                return GetLastError();
        }

        hThread[6] = CreateThread(NULL, 0, thread_h, NULL, 0, &ThreadID);
        if (hThread[6] == NULL) {
                return GetLastError();
        }

        hThread[7] = CreateThread(NULL, 0, thread_f, NULL, 0, &ThreadID);
        if (hThread[7] == NULL) {
                return GetLastError();
        }

        WaitForSingleObject(hThread[5], INFINITE);
        WaitForSingleObject(hThread[6], INFINITE);
        WaitForSingleObject(hThread[7], INFINITE);

        CloseHandle(hThread[5]);
        CloseHandle(hThread[6]);
        CloseHandle(hThread[7]);

        return 0;
}


DWORD WINAPI thread_f(LPVOID lpParam)
{
        for (int i = 0; i < 3; i++) {
                WaitForSingleObject(hMutex, INFINITE);
                cout << "f" << flush;
                computation();
                ReleaseMutex(hMutex);
        }
        return 0;
}

DWORD WINAPI thread_h(LPVOID lpParam)
{
        for (int i = 0; i < 3; i++) {
                WaitForSingleObject(hMutex, INFINITE);
                cout << "h" << flush;
                computation();
                ReleaseMutex(hMutex);
        }

    	return 0;
}

DWORD WINAPI thread_i(LPVOID lpParam)
{
        for (int i = 0; i < 3; i++) {
                WaitForSingleObject(hMutex, INFINITE);
                cout << "i" << flush;
                computation();
                ReleaseMutex(hMutex);
        }

	
        hThread[5] = CreateThread(NULL, 0, thread_g, NULL, 0, &ThreadID);
        if (hThread[5] == NULL) {
                return GetLastError();
        }

        hThread[6] = CreateThread(NULL, 0, thread_h, NULL, 0, &ThreadID);
        if (hThread[6] == NULL) {
                return GetLastError();
        }

        hThread[8] = CreateThread(NULL, 0, thread_i, NULL, 0, &ThreadID);
        if (hThread[8] == NULL) {
                return GetLastError();
        }

        WaitForSingleObject(hThread[5], INFINITE);
        WaitForSingleObject(hThread[6], INFINITE);
        WaitForSingleObject(hThread[8], INFINITE);

        CloseHandle(hThread[5]);
        CloseHandle(hThread[6]);
        CloseHandle(hThread[8]);

return 0;
}

int lab3_init()
{
    	hMutex = CreateMutex(NULL, 0, NULL);
    	if (hMutex == NULL) {
        	cout << "CreateMutex error: " << GetLastError();
        	return 1;
    	}

    	for (int i = 0; i < SEMAPHORE_COUNT; i++) {
        	hSemaphore[i] = CreateSemaphore(NULL, i == 0 ? 1 : 0, 1, NULL);
        	if (hSemaphore[i] == NULL) {
            		cout << "CreateSemaphore error: " << GetLastError();
            		return 1;
        	}
    	}

    	hThread[0] = CreateThread(NULL, 0, thread_a, NULL, 0, &ThreadID);
    	if (hThread[0] == NULL) {
        	return GetLastError();
    	}

    	WaitForSingleObject(hThread[0], INFINITE);

    	CloseHandle(hThread[0]);

    	CloseHandle(hMutex);

    	for (int i = 0; i < SEMAPHORE_COUNT; i++) {
        	CloseHandle(hSemaphore[i]);
    	}

    	return 0;
}
