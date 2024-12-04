#pragma once
#include "bookrooms.hpp"
#include "manage.hpp"
#include "rooms.hpp"

void menu();                                                                 // hiển thị menu
void loading(Phong &, Phong[], int &, ThueNhieuPhong &);                     // tải dữ liệu tổng
void nhapDuLieuGiaTien(Phong &);                                             // nhập dữ liệu giá tiền
void nhapDuLieuDanhSachPhong(Phong[], int &);                                // nhập dữ liệu danh sách phòng
void nhapDuLieuDanhSachNguoiThueTrucTiep(ThueNhieuPhong &, Phong[], int &);  // nhập dữ liệu thuê trực tiếp

void menu() {
    int choose, n = 0;
    bool exit = false;
    Phong p;
    Phong *nhieuPhong = new Phong[MAX];
    ThueNhieuPhong thueNhieuPhong;

    loading(p, nhieuPhong, n, thueNhieuPhong);

    do {
        system("cls");
        cout << "\t\t\t*-----------------------------------------*\n";
        cout << "\t\t\t|                                         |\n";
        cout << "\t\t\t|         /  QUẢN LÝ KHÁCH SẠN  /         |\n";
        cout << "\t\t\t|                                         |\n";
        cout << "\t\t\t*-----------------------------------------*\n";
        cout << "\t\t\t|      1.   Thêm phòng                    |\n";
        cout << "\t\t\t|      2.   Xóa phòng                     |\n";
        cout << "\t\t\t|      3.   Xem tình trạng phòng          |\n";
        cout << "\t\t\t|      4.   Thuê phòng                    |\n";
        cout << "\t\t\t|      5.   Thanh toán                    |\n";
        cout << "\t\t\t|      6.   Lịch sử thanh toán            |\n";
        cout << "\t\t\t|      9.   Thiết lập giá tiền            |\n";
        cout << "\t\t\t|      0.   Đăng xuất                     |\n";
        cout << "\t\t\t*-----------------------------------------*\n";
        cout << "\n(?) Chọn chức năng: ";
        cin >> choose;
        switch (choose) {
            case 1: {
                system("cls");
                int soPhong;
                cout << "\nMENU/QUẢN LÝ PHÒNG/THÊM PHÒNG" << "\n";
                if (n != 0)
                    xuatDanhSachCacPhong(nhieuPhong, n);
                themPhong(nhieuPhong, n, soPhong);
                sapXepDanhSachPhong_MergeSort(nhieuPhong, 0, n - 1);
                ThueMotPhong thueMotPhong;
                thueMotPhong.phong = layViTriCuaPhong(nhieuPhong, n, soPhong);
                thueMotPhong.phong->soPhong = soPhong;
                thueMotPhong.phong->gioBD = 0;
                thueMotPhong.phong->phutBD = 0;
                thueMotPhong.phong->giayBD = 0;
                thueMotPhong.phong->ngayBD = 0;
                thueMotPhong.phong->thangBD = 0;
                thueMotPhong.phong->namBD = 0;
                themNodeVaoCuoi(thueNhieuPhong, thueMotPhong);
                sapXepDanhSachNguoiThueTheoSoPhong_QuickSort(thueNhieuPhong);
                ghiDanhSachCacPhong(nhieuPhong, n);
                ghiDanhSachNguoiThueTrucTiep(thueNhieuPhong, n);
                break;
            }
            case 2:
                system("cls");
                int kiemTra;
                cout << "\nMENU/QUẢN LÝ PHÒNG/XÓA PHÒNG" << "\n";
                if (n == 0) {
                    cout << "\n\t(!) Danh sách phòng trống" << "\n";
                    system("pause");
                    break;
                }
                // nếu tất cả phòng đều đang được sử dụng
                if (kiemTraHetPhong(nhieuPhong, n)) {
                    cout << "\n\t(!) Tất cả phòng đang được sử dụng, không thể xóa bây giờ" << "\n";
                    system("pause");
                    break;
                } else {
                    xuatDanhSachCacPhong(nhieuPhong, n);
                    xoaPhong(nhieuPhong, n, kiemTra);
                    sapXepDanhSachPhong_MergeSort(nhieuPhong, 0, n - 1);
                    ghiDanhSachCacPhong(nhieuPhong, n);
                }
                break;
            case 3:
                int subChoose;
                do {
                    system("cls");
                    cout << "\nMENU/QUẢN LÝ PHÒNG/XEM TÌNH TRẠNG PHÒNG" << "\n";
                    cout << "\t\t\t*-----------------------------------------*\n";
                    cout << "\t\t\t|                                         |\n";
                    cout << "\t\t\t|         /  XEM TÌNH TRẠNG PHÒNG  /      |\n";
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
            case 4:
                system("cls");
                cout << "\nMENU/THUÊ PHÒNG" << "\n";
                thuePhong(nhieuPhong, n);
                ghiDanhSachCacPhong(nhieuPhong, n);
                ghiDanhSachNguoiThueTrucTiep(thueNhieuPhong, n);
                break;
            case 5:
                system("cls");
                cout << "\nMENU/THANH TOÁN" << "\n";
                thanhToan(nhieuPhong, n);
                ghiDanhSachCacPhong(nhieuPhong, n);
                ghiDanhSachNguoiThueTrucTiep(thueNhieuPhong, n);
                break;
            case 6: {
                system("cls");
                cout << "\nMENU/LỊCH SỬ THANH TOÁN" << "\n";
                string fileName = "../File/lichsu/lichsuthanhtoan.txt";
                ifstream fileIn(fileName);

                if (fileIn.fail()) {
                    cout << "\n\t(!) Không tìm thấy tập tin" << "\n";
                    system("pause");
                    break;
                } else {
                    cout << "*------------------------*-------------------------*------------*------------*--------------------*" << "\n";
                    cout << setw(32) << left << "| Thời gian bắt đầu"
                         << "|";
                    cout << setw(30) << left << " Thời gian kết thúc"
                         << "|";
                    cout << setw(15) << left << " Số phòng"
                         << "|";
                    cout << setw(15) << left << " Loại phòng"
                         << "|";
                    cout << setw(24) << right << "Số tiền "
                         << "|" << "\n";
                    cout << "*------------------------*-------------------------*------------*------------*--------------------*" << "\n";
                    docLichSu(fileName);
                    cout << "*------------------------*-------------------------*------------*------------*--------------------*" << "\n";
                    system("pause");
                }
                break;
            }
            case 9:
                system("cls");
                cout << "\nMENU/THIẾT LẬP GIÁ TIỀN" << "\n";
                thietLapGiaTien(p);
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

void loading(Phong &p, Phong nhieuPhong[], int &n, ThueNhieuPhong &thueNhieuPhong) {
    system("cls");
    float tienTrinh = 0.0;
    while (tienTrinh <= 1) {
        int doDaiThanh = 100;

        cout << "[";
        int viTri = doDaiThanh * tienTrinh;
        for (int i = 0; i < doDaiThanh; ++i) {
            if (i < viTri)
                cout << on_bright_green << " " << reset;
            else if (i == viTri)
                cout << on_bright_green << " " << reset;
            else
                cout << " ";
        }
        cout << "] " << int(tienTrinh * 100.0) << " %\r";
        cout.flush();
        if (tienTrinh == float(0.2))
            nhapDuLieuGiaTien(p);
        else if (tienTrinh == float(0.4))
            nhapDuLieuDanhSachPhong(nhieuPhong, n);
        else if (tienTrinh == float(0.8))
            nhapDuLieuDanhSachNguoiThueTrucTiep(thueNhieuPhong, nhieuPhong, n);
        else if (tienTrinh == float(1))
            cout << "\n\t(*) Nhập dữ liệu thành công (*)" << "\n";
        tienTrinh += 0.2;
        Sleep(350);
        system("cls");
    }
    cout << endl;
}

void nhapDuLieuGiaTien(Phong &p) {
    docGiaTien(p);
    if (p.giaTienThuong == 0 || p.giaTienCaoCap == 0) {
        cout << "\n\t(!) Hệ thống đang chưa được thiết lập giá tiền. Hãy thiết lập ngay bây giờ" << "\n";
        system("pause");
        thietLapGiaTien(p);
    } else
        cout << "\n\t(*) Đang nhập dữ liệu giá tiền (*)" << "\n";
}

void nhapDuLieuDanhSachPhong(Phong nhieuPhong[], int &n) {
    cout << "\n\t(*) Đang nhập dữ liệu danh sách phòng (*)" << "\n";
    docDanhSachCacPhong(nhieuPhong, n);
}

void nhapDuLieuDanhSachNguoiThueTrucTiep(ThueNhieuPhong &thueNhieuPhong, Phong nhieuPhong[], int &n) {
    taoListThueMotPhong(thueNhieuPhong);
    cout << "\n\t(*) Đang nhập dữ liệu danh sách người thuê (*)" << "\n";
    docDanhSachNguoiThueTrucTiep(thueNhieuPhong, nhieuPhong, n);
}