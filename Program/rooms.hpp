#pragma once
#include "room.hpp"

void docDanhSachCacPhong(Phong[], int &);                    // đọc danh sách các phòng
void ghiDanhSachCacPhong(Phong[], int &);                    // ghi danh sách các phòng
Phong *layViTriCuaPhong(Phong[], int, int);                  // lấy vị trí của phòng
void xuatDanhSachCacPhong(Phong[], int);                     // xuất danh sách các phòng (trống và đã được sử dụng)
void xuatDanhSachCacPhongCoThoiGian(Phong[], int);           // xuất danh sách các phòng có thời gian (trống và đã được sử dụng)
void xuatDanhSachCacPhongDay(Phong[], int);                  // xuất danh sách các phòng đã được sử dụng
void xuatDanhSachCacPhongTrong(Phong[], int);                // xuất danh sách các phòng trống
void sapXepDanhSachPhong(Phong[], int &);                    // sắp xếp danh sách phòng tăng dần theo số phòng
void sapXepDanhSachPhong_MergeSort(Phong[], int, int, int);  // thuật toán sắp xếp mergeSort
void mergeSort(Phong[], int, int);                           // thuật toán sắp xếp mergeSort
bool kiemTraHetPhong(Phong[], int);                          // kiểm tra hết phòng
bool kiemTraTrangThai(Phong[], int);                         // kiểm tra trạng thái
bool kiemTraSoPhong(Phong[], int, int);                      // kiểm tra phòng còn trống hay đã được sử dụng
bool kiemTraSoPhongCanThanhToan(Phong[], int, int);          // kiểm tra số phòng cần thanh toán

void docDanhSachCacPhong(Phong nhieuPhong[], int &n) {
    string fileName = "../File/phong/danhsachphong.txt";
    ifstream fileIn(fileName);
    if (fileIn.fail()) {
        cout << "\n\t(!) Không tìm thấy tập tin, tạo tập tin mới" << "\n";
        ofstream fileOut(fileName);
        fileOut.close();
        n = 0;
    } else {
        fileIn >> n;
        fileIn.ignore();
        for (int i = 0; i < n; i++) {
            docMotPhong(fileIn, nhieuPhong[i]);
        }
        fileIn.close();
    }
}

void ghiDanhSachCacPhong(Phong nhieuPhong[], int &n) {
    string fileName = "../File/phong/danhsachphong.txt";
    ofstream fileOut(fileName);
    if (fileOut.fail()) {
        cout << "\n\t(!) Không tìm thấy tập tin" << "\n";
        system("pause");

    } else {
        fileOut << n << endl;
        for (int i = 0; i < n; i++) {
            ghiMotPhong(fileOut, nhieuPhong[i]);
            if (i != n - 1)
                fileOut << endl;
        }
    }
    fileOut.close();
}

Phong *layViTriCuaPhong(Phong nhieuPhong[], int n, int soPhong) {
    for (int i = 0; i < n; i++)
        if (nhieuPhong[i].soPhong == soPhong)
            return &nhieuPhong[i];
    return NULL;
}

void xuatDanhSachCacPhong(Phong nhieuPhong[], int n) {
    if (n != 0) {
        // nếu không có phòng
        if (kiemTraHetPhong(nhieuPhong, n))
            cout << "\n\t(!) Chưa có phòng" << "\n";
        else {
            cout << "*------------*-------------*--------------------*--------------------*" << "\n";
            cout << setw(15) << left << "| Mã phòng"
                 << "|";
            cout << setw(16) << left << " Số phòng"
                 << "|";
            cout << setw(23) << left << " Kiểu phòng"
                 << "|";
            cout << setw(23) << left << " Tình trạng"
                 << "|" << "\n";
            cout << "*------------*-------------*--------------------*--------------------*\n";
            for (int i = 0; i < n; i++)
                inMotPhongTheoChieuNgang(nhieuPhong[i]);
            cout << "*------------*-------------*--------------------*--------------------*" << "\n";
        }
    } else
        cout << "\n\t(!) Danh sách phòng trống" << "\n";
}

void xuatDanhSachCacPhongCoThoiGian(Phong nhieuPhong[], int n) {
    if (n != 0) {
        cout << "*---------*----------*--------------------*--------------------*-----------------------*" << "\n";
        cout << setw(12) << left << "| Mã phòng"
             << "|";
        cout << setw(13) << left << " Số phòng"
             << "|";
        cout << setw(23) << left << " Kiểu phòng"
             << "|";
        cout << setw(23) << left << " Tình trạng"
             << "|";
        cout << setw(30) << left << " Thời gian bắt đầu"
             << "|" << "\n";
        cout << "*---------*----------*--------------------*--------------------*-----------------------*\n";
        for (int i = 0; i < n; i++)
            inMotPhongTheoChieuNgangCoThoiGian(nhieuPhong[i]);
        cout << "*---------*----------*--------------------*--------------------*-----------------------*" << "\n";
    } else
        cout << "\n\t(!) Danh sách phòng trống" << "\n";
}

void xuatDanhSachCacPhongDay(Phong nhieuPhong[], int n) {
    if (n != 0) {
        // nếu không có phòng nào được bật
        if (!kiemTraTrangThai(nhieuPhong, n))
            cout << "\n\t(!) Không có phòng đang được sử dụng" << "\n";
        else {
            cout << "*---------*----------*--------------------*--------------------*-----------------------*" << "\n";
            cout << setw(12) << left << "| Mã phòng"
                 << "|";
            cout << setw(13) << left << " Số phòng"
                 << "|";
            cout << setw(23) << left << " Kiểu phòng"
                 << "|";
            cout << setw(23) << left << " Tình trạng"
                 << "|";
            cout << setw(30) << left << " Thời gian bắt đầu"
                 << "|" << "\n";
            cout << "*---------*----------*--------------------*--------------------*-----------------------*" << "\n";
            for (int i = 0; i < n; i++)
                if (nhieuPhong[i].tinhTrang == 1)
                    inMotPhongTheoChieuNgangCoThoiGian(nhieuPhong[i]);
            cout << "*---------*----------*--------------------*--------------------*-----------------------*" << "\n";
        }
    } else
        cout << "\n\t(!) Danh sách phòng trống" << "\n";
}

void xuatDanhSachCacPhongTrong(Phong nhieuPhong[], int n) {
    if (n != 0) {
        // nếu hết phòng
        if (kiemTraHetPhong(nhieuPhong, n))
            cout << "\n\t(!) Hết phòng" << "\n";
        else {
            cout << "*------------*-------------*--------------------*--------------------*" << "\n";
            cout << setw(15) << left << "| Mã phòng"
                 << "|";
            cout << setw(16) << left << " Số phòng"
                 << "|";
            cout << setw(23) << left << " Kiểu phòng"
                 << "|";
            cout << setw(23) << left << " Tình trạng"
                 << "|" << "\n";
            cout << "*------------*-------------*--------------------*--------------------*" << "\n";
            for (int i = 0; i < n; i++)
                if (nhieuPhong[i].tinhTrang == 0)
                    inMotPhongTheoChieuNgang(nhieuPhong[i]);
            cout << "*------------*-------------*--------------------*--------------------*" << "" << "\n";
        }
    } else
        cout << "\n\t(!) Danh sách phòng trống" << "\n";
}

void sapXepDanhSachPhong(Phong nhieuPhong[], int &n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (nhieuPhong[i].soPhong > nhieuPhong[j].soPhong) {
                Phong tam = nhieuPhong[i];
                nhieuPhong[i] = nhieuPhong[j];
                nhieuPhong[j] = tam;
            }
}

// Thuật toán MergeSort
void merge(Phong nhieuPhong[], int l, int m, int r) {
    vector<Phong> x(nhieuPhong + l, nhieuPhong + m + 1);
    vector<Phong> y(nhieuPhong + m + 1, nhieuPhong + r + 1);
    int i = 0, j = 0;
    while (i < x.size() && j < y.size()) {
        if (x[i].soPhong <= y[j].soPhong) {
            nhieuPhong[l] = x[i];
            ++l;
            ++i;
        } else {
            nhieuPhong[l] = y[j];
            ++l;
            ++j;
        }
    }
    while (i < x.size()) {
        nhieuPhong[l] = x[i];
        ++l;
        ++i;
    }
    while (j < y.size()) {
        nhieuPhong[l] = y[j];
        ++l;
        ++j;
    }
}

void sapXepDanhSachPhong_MergeSort(Phong nhieuPhong[], int l, int r) {
    if (l >= r)
        return;
    int m = (l + r) / 2;
    sapXepDanhSachPhong_MergeSort(nhieuPhong, l, m);
    sapXepDanhSachPhong_MergeSort(nhieuPhong, m + 1, r);
    merge(nhieuPhong, l, m, r);
}

bool kiemTraHetPhong(Phong nhieuPhong[], int n) {
    for (int i = 0; i < n; i++)
        if (nhieuPhong[i].tinhTrang == 0)  // còn phòng trống -> thì trả về false
            return false;
    return true;
}

bool kiemTraTrangThai(Phong nhieuPhong[], int n) {
    bool kiemTra = false;
    for (int i = 0; i < n; i++) {
        if (nhieuPhong[i].tinhTrang == 1) {
            kiemTra = true;
            break;
        }
    }
    return kiemTra;
}

bool kiemTraSoPhong(Phong nhieuPhong[], int n, int soPhong) {
    for (int i = 0; i < n; i++)
        if (nhieuPhong[i].soPhong == soPhong && nhieuPhong[i].tinhTrang == 0)
            return true;
    return false;
}

bool kiemTraSoPhongCanThanhToan(Phong nhieuPhong[], int n, int soPhong) {
    for (int i = 0; i < n; i++)
        if (nhieuPhong[i].soPhong == soPhong && nhieuPhong[i].tinhTrang == 1)
            return true;
    return false;
}