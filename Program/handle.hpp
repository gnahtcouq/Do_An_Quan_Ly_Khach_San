#pragma once
#include <assert.h>
#include <conio.h>  // getch()
#include <string.h>
#include <windows.h>

#include <fstream>
#include <iomanip>  // setw()
#include <iostream>
#include <limits>
#include <random>  // srand()
#include <string>

using namespace std;

#define MAX 200

const HWND consoleWindow = GetConsoleWindow();

void layThoiGianHeThong(int &, int &, int &, int &, int &, int &);  // lấy thời gian hệ thống
void xoaKhoangTrangThua(string &);                                  // xóa khoảng trắng thừa ở giữa
void vietHoaKiTuDauMoiTu(string &);                                 // viết hoa kí tự đầu

void layThoiGianHeThong(int &gio, int &phut, int &giay, int &ngay, int &thang, int &nam) {
    time_t baygio = time(0);
    tm *ltm = localtime(&baygio);
    gio = ltm->tm_hour;
    phut = ltm->tm_min;
    giay = ltm->tm_sec;
    ngay = ltm->tm_mday;
    thang = 1 + ltm->tm_mon;
    nam = 1900 + ltm->tm_year;
}

void xoaKhoangTrangThua(string &str) {
    for (int i = 0; i < str.length(); i++) {
        // nếu kí tự là khoảng trắng ==> xóa đi 1 kí tự
        if (str[i] == ' ') {
            str.erase(str.begin() + i);
            i--;
        }
    }
}

void vietHoaKiTuDauMoiTu(string &str) {
    // Bước 1: chuyển chuỗi str về chuỗi in thường
    strlwr((char *)str.c_str());  // hàm chuyển chuỗi str về chuỗi in thường
    // Bước 2: viết hoa kí tự đầu của mỗi từ
    if (str[0] != ' ') {
        if (str[0] >= 97 && str[0] <= 122) {
            str[0] -= 32;
        }
    }
    // kí tự tại vị trí i là khoảng trắng, i + i khác khoảng trắng thì kí tự tại vị trí i + 1 chính là kí tự đầu tiên của mỗi từ
    for (int i = 0; i < str.length() - 1; i++) {
        if (str[i] == ' ' && str[i + 1] != ' ') {
            // A: 65
            // B: 66
            // Z: 90
            // a: 97
            // b: 98
            // c: 99
            // z: 122
            if (str[i + 1] >= 97 && str[i + 1] <= 122) {
                // - 32 là chuyển kí tự in thường về in hoa
                str[i + 1] -= 32;  // <=> str[i + 1] = str[i + 1] - 32;
            }
        }
    }
}
