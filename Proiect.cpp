#undef UNICODE
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include "resource.h"
#include <iostream>
using namespace std;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

BOOL dlgActive = FALSE; //variabila pentru casetadedialog
HWND hwndMain; //variabila handle a ferestrei principale

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR szCmdLine, int iCmdShow)
{
    static char szAppName[] = "Proiect";
    HWND        hwnd;
    MSG         msg;
    WNDCLASSEX  wndclass;

    wndclass.cbSize = sizeof(wndclass);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;  //optiuni pentru stilul clasei 
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    // incarca pictograma fisierelor de tip aplicatie
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW); // incarca cursorul sageata  
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    // fondul ferstrei de culoare alba     
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;
    wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClassEx(&wndclass);

    hwnd = CreateWindow(szAppName, //numele clasei inregistrat cu RegisterClass
        "Proiect",    // text pentru bara de titlu a ferestrei
        WS_OVERLAPPEDWINDOW,   // stilul ferestrei
        CW_USEDEFAULT,      // pozitia orizontala implicitã
        CW_USEDEFAULT,      // pozitia verticala implicita
        CW_USEDEFAULT,       // latimea implicita
        CW_USEDEFAULT,       // inaltimea implicita
        NULL,               // handle-ul ferestrei parinte
        NULL,               // handle-ul meniului ferestrei
        hInstance,          // proprietara ferestrei 
        NULL);


    SetWindowPos(hwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOACTIVATE);
    // schimba dimensiunea, pozitia si ordinea z a ferestrei copil, a ferestrei pop-up
    ShowWindow(hwnd, SW_HIDE);
    UpdateWindow(hwnd);
    hwndMain = hwnd;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    static HINSTANCE hInstance;
    switch (iMsg)
    {
    case WM_CREATE: // operatiile ce se executa la crearea ferestrei
       // se creaza caseta de dialog
        hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
        if (!dlgActive) {
            DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG),
                hwnd, DlgProc);
            PostMessage(hwnd, WM_CLOSE, 0, 0);
            // insereaza un nou mesaj nou in coada de asteptare
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0); // insereaza un mesaj de incheiere 
        return 0;
    }

    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam) {
    char sursa[100], destinatie[100], locatiesistsursa[100] = "D:\\sisteme de operare\\", locatiesistdest[100] = "D:\\sisteme de operare\\";
    char locatiesursa[100], locatiedest[100],locfissursa[100],locfissursa2[100],locfisursacopy[100],locatiedestcopy[100], numeextfisusrsa[100];
    char copylocsist[100] = "D:\\sisteme de operare\\",locatiedest2[100],numeextdest[100];
    char backslash[100] = "\\",backslash2[100]="\\",fisiergasit2[100],fisiergasit[100],locatiedestcopy2[100];
    char extensie[100] = "\\*",buff[100],buff2[100]="D:\\sisteme de operare\\",buff3[100],buff4[100];
    int iRasp;
    HANDLE hsursa,hfile,hfile2,hfile3;
    WIN32_FIND_DATA FindFileData1,FindFileData2,FindFileData3;
    switch (iMsg) {

    case WM_INITDIALOG:
        // setari initiale	
        return TRUE;

    case WM_CLOSE:
        dlgActive = FALSE;
        EndDialog(hDlg, 0);
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case MUTARE:
            GetDlgItemText(hDlg, NUMEDIRSURSA,sursa, 100);
            strcat(locatiesistsursa,sursa);
            strcpy(locatiesursa, locatiesistsursa);
            GetDlgItemText(hDlg, NUMEDIRDEST, destinatie, 100);
            CreateDirectory(locatiesursa, NULL);
            strcat(locatiesistdest, destinatie);
            strcpy(locatiedest, locatiesistdest);
            strcpy(locatiedest2, locatiedest);
            strcpy(locatiedestcopy, locatiedest);
            CreateDirectory(locatiedest, NULL);
            strcpy(locfissursa,locatiesursa);
            strcpy(locfissursa2, locfissursa);
            strcpy(locfisursacopy, locfissursa);
            hsursa=CreateFile(strcat(locfissursa,"\\fisier.bmp"),(GENERIC_READ | GENERIC_WRITE), (FILE_SHARE_READ | FILE_SHARE_WRITE), NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            strcat(locfissursa2,extensie);
            hfile = FindFirstFile(locfissursa2, &FindFileData1);
            if (hfile != INVALID_HANDLE_VALUE)
            while (FindNextFile(hfile, &FindFileData1)) {
                    SetDlgItemText(hDlg, INTRARISURSA, FindFileData1.cFileName);
                    if (FindFileData1.cFileName[0] != '.' && FindFileData1.cFileName[1] != '.') {
                        strcpy(numeextfisusrsa, FindFileData1.cFileName);
                        strcat(backslash, numeextfisusrsa);
                    }
            }
                CopyFile(locfissursa, strcat(locatiedestcopy,backslash),FALSE);
                FindClose(hfile);
                CloseHandle(hsursa);
                strcat(locatiedest2, extensie);
                hfile2 = FindFirstFile(locatiedest2, &FindFileData2);
                if (hfile2 != INVALID_HANDLE_VALUE)
                while (FindNextFile(hfile2, &FindFileData2)) {
                    SetDlgItemText(hDlg, INTRARIDEST,FindFileData2.cFileName);
                    strcpy(numeextdest,FindFileData2.cFileName);
                    strcat(backslash2, numeextdest);
                }
                FindClose(hfile2);
            return TRUE;

        case ID_CANCEL:
            MessageBox(hDlg, "Abandon!", "Ati selectat Iesire", MB_OK);
            dlgActive = FALSE;
            EndDialog(hDlg, 0);
            return TRUE;

        case STERGERE:
            iRasp = MessageBox(hDlg, "Sunteti sigur ca doriti sa stergeti fisierele copiate?", "Stergere", MB_YESNO);
            if (iRasp == IDYES) {
                GetDlgItemText(hDlg, NUMEDIRDEST, buff, 100);
                strcat(buff2,buff);
                strcpy(buff3, buff2);
                strcat(buff3, "\\");
                strcat(buff2, extensie);
                hfile3 = FindFirstFile(buff2, &FindFileData3);

                if (hfile3 != INVALID_HANDLE_VALUE)

                    while (FindNextFile(hfile3, &FindFileData3)) {
                        strcpy(buff4, FindFileData3.cFileName);
                    }
                FindClose(hfile3);
                strcat(buff3, buff4);
                DeleteFile(buff3);
                SetDlgItemText(hDlg, INTRARIDEST, "");
            }
           
            return TRUE;
        }
        break;
    }
    return FALSE;
}