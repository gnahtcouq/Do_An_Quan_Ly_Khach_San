#pragma once
#include "rooms.hpp"

void menu();  // hiển thị menu

void menu() {
    int choose, n;
    bool exit = false;
    Phong *nhieuPhong = new Phong[MAX];
    docDanhSachCacPhong(nhieuPhong, n);
    do {
        system("cls");
        cout << "\t\t\t*-----------------------------------------*\n";
        cout << "\t\t\t|                                         |\n";
        cout << "\t\t\t|         ~  QUẢN LÝ KHÁCH SẠN  ~         |\n";
        cout << "\t\t\t|                                         |\n";
        cout << "\t\t\t*-----------------------------------------*\n";
        cout << "\t\t\t|      1.   Thêm phòng                    |\n";
        cout << "\t\t\t|      2.   Xem tình trạng phòng          |\n";
        cout << "\t\t\t|      0.   Đăng xuất                     |\n";
        cout << "\t\t\t*-----------------------------------------*\n";
        cout << "\n(?) Chọn chức năng: ";
        cin >> choose;
        switch (choose) {
            case 1:
                system("cls");
                int soPhong;
                cout << "\nMENU/QUẢN LÝ PHÒNG/THÊM PHÒNG" << "\n";
                if (n != 0)
                    xuatDanhSachCacPhong(nhieuPhong, n);
                themPhong(nhieuPhong, n, soPhong);
                sapXepDanhSachPhong_MergeSort(nhieuPhong, 0, n - 1);
                ghiDanhSachCacPhong(nhieuPhong, n);
                break;
            case 2:
                int subChoose;
                do {
                    system("cls");
                    cout << "\nMENU/QUẢN LÝ PHÒNG/XEM TÌNH TRẠNG PHÒNG" << "\n";
                    cout << "\t\t\t*-----------------------------------------*\n";
                    cout << "\t\t\t|                                         |\n";
                    cout << "\t\t\t|         ~  XEM TÌNH TRẠNG PHÒNG  ~      |\n";
                    cout << "\t\t\t|                                         |\n";
                    cout << "\t\t\t*-----------------------------------------*\n";
                    cout << "\t\t\t|      1.   Tất cả phòng                  |\n";
                    cout << "\t\t\t|      2.   Phòng đang được sử dụng       |\n";
                    cout << "\t\t\t|      3.   Phòng trống                   |\n";
                    cout << "\t\t\t|      0.   Quay lại                      |\n";
                    cout << "\t\t\t*-----------------------------------------*\n";
                    cout << "\n(?) Chọn chức năng: ";
                    cin >> subChoose;
                    switch (subChoose) {
                        case 1:
                            system("cls");
                            cout << "\nMENU/QUẢN LÝ PHÒNG/XEM TÌNH TRẠNG PHÒNG/TẤT CẢ PHÒNG" << "\n";
                            xuatDanhSachCacPhong(nhieuPhong, n);
                            system("pause");
                            break;
                        case 2:
                            system("cls");
                            cout << "\nMENU/QUẢN LÝ PHÒNG/XEM TÌNH TRẠNG PHÒNG/PHÒNG ĐANG ĐƯỢC SỬ DỤNG" << "\n";
                            xuatDanhSachCacPhongDay(nhieuPhong, n);
                            system("pause");
                            break;
                        case 3:
                            system("cls");
                            cout << "\nMENU/QUẢN LÝ PHÒNG/XEM TÌNH TRẠNG PHÒNG/PHÒNG TRỐNG" << "\n";
                            xuatDanhSachCacPhongTrong(nhieuPhong, n);
                            system("pause");
                            break;
                        case 0:
                            break;
                        default:
                            cout << "\n\t(!) Lựa chọn không hợp lệ. Xin hãy nhập lại" << "\n";
                            system("pause");
                            break;
                    }
                } while (subChoose != 0);
                break;
            case 0:
                exit = true;
                break;
            default:
                cout << "\n\t(!) Lựa chọn không hợp lệ. Xin hãy nhập lại" << "\n";
                system("pause");
                break;
        }
    } while (!exit);
    delete[] nhieuPhong;
}