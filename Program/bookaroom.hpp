#pragma once
#include "bookaroom.hpp"
#include "rooms.hpp"

struct ThueMotPhong {
    Phong *phong = NULL;  // trỏ đến phòng
};

void chonPhong(ThueMotPhong &, Phong[], int);                            // chọn phòng
void chonPhongCanThanhToan(Phong[], int);                                // chọn phòng cần thanh toán
void docMotNguoiThueTrucTiep(ifstream &, ThueMotPhong &, Phong[], int);  // đọc một người thuê trực tiếp từ file
void ghiMotNguoiThueTrucTiep(ofstream &, ThueMotPhong);                  // ghi một người thuê trực tiếp ra file

void chonPhong(ThueMotPhong &thueMotPhong, Phong nhieuPhong[], int n) {
    int soPhong;
    do {
        system("cls");
        cout << "\nMENU/THUÊ PHÒNG" << "\n";
        xuatDanhSachCacPhongTrong(nhieuPhong, n);
        cout << "\n(?) Nhập số phòng: ";
        cin >> soPhong;
        if (!kiemTraSoPhong(nhieuPhong, n, soPhong)) {
            cout << "\n\t(!) Số phòng không hợp lệ. Xin hãy nhập lại" << "\n";
            system("pause");
        } else
            thueMotPhong.phong = layViTriCuaPhong(nhieuPhong, n, soPhong);  // hàm này trong file rooms.hpp
    } while (!kiemTraSoPhong(nhieuPhong, n, soPhong));
}

void chonPhongCanThanhToan(ThueMotPhong &thueMotPhong, Phong phong[], int n) {
    int soPhong;
    do {
        system("cls");
        cout << "\nMENU/THANH TOÁN" << "\n";
        xuatDanhSachCacPhongDay(phong, n);
        cout << "\n(?) Nhập số phòng: ";
        cin >> soPhong;
        if (!kiemTraSoPhongCanThanhToan(phong, n, soPhong)) {
            cout << "\n\t(!) Số phòng không hợp lệ. Xin hãy nhập lại" << "\n";
            system("pause");
        } else
            thueMotPhong.phong = layViTriCuaPhong(phong, n, soPhong);  // hàm này trong file rooms.hpp
    } while (!kiemTraSoPhongCanThanhToan(phong, n, soPhong));
}

void docMotNguoiThueTrucTiep(ifstream &fileIn, ThueMotPhong &thueMotPhong, Phong nhieuPhong[], int n) {
    int soPhong = 0;  // lưu tạm số phòng lúc đọc từ file
    fileIn >> soPhong;
    thueMotPhong.phong = layViTriCuaPhong(nhieuPhong, n, soPhong);  // lấy số phòng lưu tạm để trả về phòng của số phòng đó
    fileIn >> thueMotPhong.phong->gioBD;
    fileIn >> thueMotPhong.phong->phutBD;
    fileIn >> thueMotPhong.phong->giayBD;
    fileIn >> thueMotPhong.phong->ngayBD;
    fileIn >> thueMotPhong.phong->thangBD;
    fileIn >> thueMotPhong.phong->namBD;
    fileIn.ignore();
    if (thueMotPhong.phong->gioBD == 0 &&
        thueMotPhong.phong->phutBD == 0 &&
        thueMotPhong.phong->giayBD == 0 &&
        thueMotPhong.phong->ngayBD == 0 &&
        thueMotPhong.phong->thangBD == 0 &&
        thueMotPhong.phong->namBD == 0)
        thueMotPhong.phong->tinhTrang = 0;  // cập nhật lại tình trạng phòng -> 0 (phòng trống)
    else
        thueMotPhong.phong->tinhTrang = 1;  // cập nhật lại tình trạng phòng -> 1 (phòng đã có người sử dụng)
}

void ghiMotNguoiThueTrucTiep(ofstream &fileOut, ThueMotPhong thueMotPhong) {
    fileOut << thueMotPhong.phong->soPhong << ' ';
    fileOut << thueMotPhong.phong->gioBD << ' ';
    fileOut << thueMotPhong.phong->phutBD << ' ';
    fileOut << thueMotPhong.phong->giayBD << ' ';
    fileOut << thueMotPhong.phong->ngayBD << ' ';
    fileOut << thueMotPhong.phong->thangBD << ' ';
    fileOut << thueMotPhong.phong->namBD;
}