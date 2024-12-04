#pragma once
#include "handle.hpp"
#include "room.hpp"
#include "staff.hpp"

struct Admin {
    string taiKhoanAdmin = "admin",
           matKhauAdmin = "admin";

    bool laAdmin(string taiKhoan, string matKhau) {
        if (taiKhoan == taiKhoanAdmin && matKhau == matKhauAdmin)
            return true;
        return false;
    }
    string getTaiKhoanAdmin() { return taiKhoanAdmin; }
    string getMatKhauAdmin() { return matKhauAdmin; }
};

int kiemTraTaiKhoan(DanhSachNhanVien, string, string);  // kiểm tra tài khoản
int xacThucDangNhap(DanhSachNhanVien, string, string);  // xác thực đăng nhập
void dangNhap(DanhSachNhanVien, int &, string &);       // đăng nhập
void docLichSu(string &);                               // đọc file lịch sử
bool kiemTraNgayHopLe(int, int, int);                   // kiểm tra ngày nhập vào hợp lệ

int kiemTraTaiKhoan(DanhSachNhanVien dsnv, string taiKhoan, string matKhau) {
    if (dsnv) {
        if (dsnv->nv.taiKhoan == taiKhoan && dsnv->nv.matKhau == matKhau)
            return 1;
        return kiemTraTaiKhoan(dsnv->left, taiKhoan, matKhau) + kiemTraTaiKhoan(dsnv->right, taiKhoan, matKhau);
    }
    return 0;
}

int xacThucDangNhap(DanhSachNhanVien dsnv, string taiKhoan, string matKhau) {
    Admin dangNhap;
    if (dangNhap.laAdmin(taiKhoan, matKhau))
        return 1;
    else {
        if (kiemTraTaiKhoan(dsnv, taiKhoan, matKhau) == 1)
            return 2;
    }
    return 0;
}

void dangNhap(DanhSachNhanVien dsnv, int &phanQuyen, string &ten) {
    string taiKhoan, matKhau;
    do {
        char c;
        int viTri = 0;
        char *str = new char[30];
        assert(str != NULL);
        system("cls");
        cout << "\t\t\t\t\t*-----------------------------------*\n";
        cout << "\t\t\t\t\t|" << "       QUẢN LÝ STU HOTEL     " << "|\n";
        cout << "\t\t\t\t\t|" << "             ĐĂNG NHẬP       " << "|\n";
        cout << "\t\t\t\t\t*-----------------------------------*\n";
        cout << "\n\t\t\t\t\t(?) Nhập tài khoản: \t";
        cin >> taiKhoan;
        cin.ignore();
        cout << "\n\t\t\t\t\t(?) Nhập mật khẩu:  \t";
        system("pause");
        str[viTri] = '\0';
        matKhau = str;
        ten = taiKhoan;
        phanQuyen = xacThucDangNhap(dsnv, taiKhoan, matKhau);
        if (phanQuyen == 0) {
            cout << "\n\n\t\t\t\t\t(!) Tài khoản/Mật khẩu không chính xác. Xin hãy nhập lại" << "\n";
            int key = 0;
            system("pause");
        }
    } while (phanQuyen == 0);
    cout << "\n\n\t\t\t\t\t(!) Đăng nhập thành công" << "\n";
    system("pause");

    // Ghi lịch sử đăng nhập
    int gio, phut, giay, ngay, thang, nam;
    layThoiGianHeThong(gio, phut, giay, ngay, thang, nam);

    string GIO = to_string(gio);
    string PHUT = to_string(phut);
    string GIAY = to_string(giay);
    string NGAY = to_string(ngay);
    string THANG = to_string(thang);
    string NAM = to_string(nam);

    if (GIO.length() == 1) GIO = "0" + GIO;
    if (PHUT.length() == 1) PHUT = "0" + PHUT;
    if (GIAY.length() == 1) GIAY = "0" + GIAY;
    if (NGAY.length() == 1) NGAY = "0" + NGAY;
    if (THANG.length() == 1) THANG = "0" + THANG;
    if (NAM.length() == 1) NAM = "0" + NAM;

    string thoiGianDangNhap = GIO + ":" + PHUT + ":" + GIAY + " - " + NGAY + "/" + THANG + "/" + NAM;
    string fileName = "../File/lichsu/lichsudangnhap.txt";
    ofstream fileOut(fileName, ios::app);
    if (fileOut.fail()) {
        cout << "\n\t(!) Không tìm thấy tập tin" << "\n";
        system("pause");
    } else {
        fileOut << setw(25) << left << "| " + thoiGianDangNhap << "|";
        fileOut << setw(30) << left << " " + ten << "|";
        fileOut << setw(16) << left << " Đăng nhập" << "|\n";
    }
    fileOut.close();
}

void docLichSu(string &fileName) {
    ifstream fileIn(fileName);
    string line;
    vector<string> list;
    while (getline(fileIn, line)) {
        list.push_back(line);
    }
    fileIn.close();
    for (int i = 0; i < list.size(); i++)
        cout << list[i] << "\n";
}

bool kiemTraNgayHopLe(int ngay, int thang, int nam) {
    time_t baygio = time(0);
    tm *ltm = localtime(&baygio);
    int namHienTai = 1900 + ltm->tm_year;
    if (nam <= 1900 || thang <= 0 || thang > 12 || ngay <= 0 || ngay > 31 || nam >= namHienTai + 1)
        return 0;
    if (thang == 1 || thang == 3 || thang == 5 || thang == 7 || thang == 8 || thang == 10 || thang == 12)
        if (ngay <= 31)
            return 1;
    if (thang == 4 || thang == 6 || thang == 9 || thang == 11)
        if (ngay <= 30)
            return 1;
    if ((nam % 4 == 0 && nam % 100 != 0) || nam % 400 == 0) {
        if (ngay <= 29)
            return 1;
    } else {
        if (ngay <= 28)
            return 1;
    }
    return 0;
}