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
DWORD WINAPI thread_d(LPVOID);
DWORD WINAPI thread_e(LPVOID);
DWORD WINAPI thread_f(LPVOID);
DWORD WINAPI thread_b_sem(LPVOID);
DWORD WINAPI thread_c_sem(LPVOID);
DWORD WINAPI thread_e_sem(LPVOID);
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
    // ---- step 1 ----
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "a" << flush;
        computation();
        ReleaseMutex(hMutex);
    }

    // ---- step 2 ----

    // start B
    hThread[1] = CreateThread(NULL, 0, thread_b_sem, NULL, 0, &ThreadID);
    if (hThread[1] == NULL) {
        return GetLastError();
    }

    // start C
    hThread[2] = CreateThread(NULL, 0, thread_c_sem, NULL, 0, &ThreadID);
    if (hThread[2] == NULL) {
        return GetLastError();
    }

    // start E
    hThread[3] = CreateThread(NULL, 0, thread_e_sem, NULL, 0, &ThreadID);
    if (hThread[3] == NULL) {
        return GetLastError();
    }

    // wait B
    WaitForSingleObject(hThread[1], INFINITE);
    // wait C
    WaitForSingleObject(hThread[2], INFINITE);
    // wait E
    WaitForSingleObject(hThread[3], INFINITE);
    
    // close B
    CloseHandle(hThread[1]);
    // close C
    CloseHandle(hThread[2]);
    // close E
    CloseHandle(hThread[3]);
    
    // ---- step 3 ----

    // start E
    hThread[3] = CreateThread(NULL, 0, thread_e, NULL, 0, &ThreadID);
    if (hThread[3] == NULL) {
        return GetLastError();
    }

    // start D
    hThread[4] = CreateThread(NULL, 0, thread_d, NULL, 0, &ThreadID);
    if (hThread[4] == NULL) {
        return GetLastError();
    }

    // start G
    hThread[5] = CreateThread(NULL, 0, thread_g, NULL, 0, &ThreadID);
    if (hThread[5] == NULL) {
        return GetLastError();
    }
    // wait E
    WaitForSingleObject(hThread[3], INFINITE);
    // wait D
    WaitForSingleObject(hThread[4], INFINITE);
    // wait G
    WaitForSingleObject(hThread[5], INFINITE);

    // close E
    CloseHandle(hThread[3]);
    // close D
    CloseHandle(hThread[4]);
    // close G
    CloseHandle(hThread[5]);
 
    // ---- step 4 ----

    // start G sem
    hThread[5] = CreateThread(NULL, 0, thread_g, NULL, 0, &ThreadID);
    if (hThread[5] == NULL) {
        return GetLastError();
    }

    // start H sem
    hThread[6] = CreateThread(NULL, 0, thread_h, NULL, 0, &ThreadID);
    if (hThread[6] == NULL) {
        return GetLastError();
    }

    // start F sem
    hThread[7] = CreateThread(NULL, 0, thread_f, NULL, 0, &ThreadID);
    if (hThread[7] == NULL) {
        return GetLastError();
    }

    // wait G sem
    WaitForSingleObject(hThread[5], INFINITE);
    // wait H sem
    WaitForSingleObject(hThread[6], INFINITE);
    // wait F sem
    WaitForSingleObject(hThread[7], INFINITE);
    

    // close G sem
    CloseHandle(hThread[5]);
    // close H sem
    CloseHandle(hThread[6]);
    // close F sem
    CloseHandle(hThread[7]);
    
    // ---- step 5 ----

    // start G
    hThread[5] = CreateThread(NULL, 0, thread_g, NULL, 0, &ThreadID);
    if (hThread[5] == NULL) {
        return GetLastError();
    }

    // start H
    hThread[6] = CreateThread(NULL, 0, thread_h, NULL, 0, &ThreadID);
    if (hThread[6] == NULL) {
        return GetLastError();
    }

    // start I
    hThread[8] = CreateThread(NULL, 0, thread_i, NULL, 0, &ThreadID);
    if (hThread[8] == NULL) {
        return GetLastError();
    }

    // wait G
    WaitForSingleObject(hThread[5], INFINITE);
    // wait H
    WaitForSingleObject(hThread[6], INFINITE);
    // wait I
    WaitForSingleObject(hThread[8], INFINITE);
    
    // close G
    CloseHandle(hThread[5]);
    // close H
    CloseHandle(hThread[6]);
    // close I
    CloseHandle(hThread[8]);
    
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

    return 0;
}



DWORD WINAPI thread_k(LPVOID lpParam)
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "k" << flush;
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

DWORD WINAPI thread_i(LPVOID lpParam)
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "i" << flush;
        computation();
        ReleaseMutex(hMutex);
    }

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

    // start A
    hThread[0] = CreateThread(NULL, 0, thread_a, NULL, 0, &ThreadID);
    if (hThread[0] == NULL) {
        return GetLastError();
    }
    // wait A
    WaitForSingleObject(hThread[0], INFINITE);
    // close A
    CloseHandle(hThread[0]);

    CloseHandle(hMutex);

    for (int i = 0; i < SEMAPHORE_COUNT; i++) {
        CloseHandle(hSemaphore[i]);
    }

    return 0;
}
