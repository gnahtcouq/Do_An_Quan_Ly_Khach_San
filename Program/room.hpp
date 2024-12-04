#pragma once
#include "handle.hpp"

struct Phong {
    string maPhong;                                               // mã phòng
    int soPhong;                                                  // số phòng
    int loaiPhong;                                                // loại phòng: thường hoặc cao cấp
    bool tinhTrang = 0;                                           // tình trạng phòng - 0:trống   1:đầy
    int gioBD = 0, phutBD = 0, giayBD = 0;                        // thời gian bắt đầu (giờ:phút:giây)
    int ngayBD = 0, thangBD = 0, namBD = 0;                       // thời gian bắt đầu (ngày/tháng/năm)
    int gioKT = 0, phutKT = 0, giayKT = 0;                        // thời gian kết thúc (giờ:phút:giây)
    int ngayKT = 0, thangKT = 0, namKT = 0;                       // thời gian kết thúc (ngày/tháng/năm)
    long long giaTien = 0, giaTienThuong = 0, giaTienCaoCap = 0;  // giá tiền
};

string taoMaPhong(Phong[], int);                 // tạo mã phòng ngẫu nhiên
int kiemTraTrungMaPhong(Phong[], int, string);   // kiểm tra mã phòng đã tồn tại
int kiemTraTrungSoPhong(Phong[], int, int);      // kiểm tra số phòng đã tồn tại
void themPhong(Phong[], int &, int &);           // thêm một phòng
void xoaPhong(Phong[], int &, int &);            // xóa một phòng
void inMotPhongTheoChieuNgang(Phong);            // in một phòng theo chiều ngang
void inMotPhongTheoChieuNgangCoThoiGian(Phong);  // im một phòng theo chiều ngang có thời gian thuê
void docMotPhong(ifstream &, Phong &);           // đọc thông tin một phòng từ file
void ghiMotPhong(ofstream &, Phong);             // ghi thông tin một phòng ra file
void docGiaTien(Phong &);                        // đọc giá tiền từ file
void ghiGiaTien(Phong);                          // ghi giá tiền từ file
void thietLapGiaTien(Phong &);                   // thiết lập giá tiền

string taoMaPhong(Phong nhieuPhong[], int n) {
    string ma = "STU000";
    do {
        for (int i = 3; i < ma.length(); i++)
            ma[i] = rand() % (57 - 48 + 1) + 48;
    } while (kiemTraTrungMaPhong(nhieuPhong, n, ma) >= 0);
    return ma;
}

int kiemTraTrungMaPhong(Phong nhieuPhong[], int n, string str) {
    for (int i = 0; i < n; i++)
        if (nhieuPhong[i].maPhong == str)
            return i;
    return -1;
}

int kiemTraTrungSoPhong(Phong nhieuPhong[], int n, int soPhong) {
    for (int i = 0; i < n; i++)
        if (nhieuPhong[i].soPhong == soPhong)
            return i;
    return -1;
}

void themPhong(Phong nhieuPhong[], int &n, int &soPhong) {
    Phong p;
    p.maPhong = taoMaPhong(nhieuPhong, n);

    do {
        cout << "\n(?) Nhập số phòng: ";
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (!(cin >> p.soPhong)) {
            cout << "\n\t(!) Vui lòng nhập số nguyên\n";
            continue;
        }
        if (p.soPhong <= 0 || p.soPhong >= MAX) {
            cout << "\n\t(!) Số phòng không hợp lệ [1-" << MAX << "]. Xin hãy nhập lại" << "\n";
        } else if (kiemTraTrungSoPhong(nhieuPhong, n, p.soPhong) != -1) {
            cout << "\n\t(!) Số phòng đã tồn tại. Xin hãy nhập lại" << "\n";
        }
    } while (cin.fail() || p.soPhong <= 0 || p.soPhong >= MAX || kiemTraTrungSoPhong(nhieuPhong, n, p.soPhong) != -1);

    soPhong = p.soPhong;
    cin.ignore();

    do {
        cout << "\n(?) Nhập loại phòng (0: Thường - 1: Cao cấp): ";
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (!(cin >> p.loaiPhong)) {
            cout << "\n\t(!) Vui lòng nhập số nguyên\n";
            continue;
        }
        if (p.loaiPhong < 0 || p.loaiPhong > 1) {
            cout << "\n\t(!) Loại phòng không hợp lệ. Xin hãy nhập lại" << "\n";
        }
    } while (cin.fail() || p.loaiPhong < 0 || p.loaiPhong > 1);

    for (int i = n - 1; i >= 0; i--)
        nhieuPhong[i + 1] = nhieuPhong[i];
    nhieuPhong[0] = p;
    n++;
    cout << "\n\t(!) Thêm phòng thành công" << "\n";
    system("pause");
}

void xoaPhong(Phong nhieuPhong[], int &n, int &kiemTra) {
    string str;
    cout << "\n(?) Nhập mã phòng cần xóa: ";
    cin >> str;
    int vitri = kiemTraTrungMaPhong(nhieuPhong, n, str);
    // Dời
    if (vitri < 0) {
        cout << "\n\t(!) Mã phòng không tồn tại. Xin hãy nhập lại" << "\n";
        kiemTra = 0;
        system("pause");
    } else {
        for (int i = vitri; i < n - 1; i++) {
            nhieuPhong[i].maPhong = nhieuPhong[i + 1].maPhong;
            nhieuPhong[i].soPhong = nhieuPhong[i + 1].soPhong;
            nhieuPhong[i].loaiPhong = nhieuPhong[i + 1].loaiPhong;
            nhieuPhong[i].tinhTrang = nhieuPhong[i + 1].tinhTrang;
        }
        // Giảm số lượng
        Phong tam = nhieuPhong[n - 1];
        n--;
        cout << "\n\t(!) Xóa phòng thành công" << "\n";
        kiemTra = 1;
        system("pause");
    }
}

void inMotPhongTheoChieuNgang(Phong phong) {
    string loaiKieuPhong, tinhTrangPhong;
    if (phong.tinhTrang == 1)  // tinhTrang == 1 -> phòng đã có người sử dụng
        tinhTrangPhong = "Đầy";
    else  // tinhTrang == 0 -> phòng trống
        tinhTrangPhong = "Trống";
    if (phong.loaiPhong == 1)  // loaiPhong == 1 -> phòng cao cấp
        loaiKieuPhong = "Cao cấp";
    else  // loaiPhong == 0 -> phòng thường
        loaiKieuPhong = "Thường";
    cout << setw(13) << left << "| " + phong.maPhong << "|";
    cout << setw(13) << left << " " + to_string(phong.soPhong) << "|";
    if (loaiKieuPhong == "Thường")
        cout << setw(23) << left << " " + loaiKieuPhong << "|";
    else
        cout << setw(22) << left << " " + loaiKieuPhong << "|";
    if (tinhTrangPhong == "Đầy")
        cout << setw(23) << left << " " + tinhTrangPhong << "|" << "\n";
    else
        cout << setw(22) << left << " " + tinhTrangPhong << "|" << "\n";
}

void inMotPhongTheoChieuNgangCoThoiGian(Phong phong) {
    string loaiKieuPhong, tinhTrangPhong;
    // Chuyển định dạng giờ, phút, giây, ngày, tháng, năm sang kiểu chuỗi
    string GIOBD = to_string(phong.gioBD);
    string PHUTBD = to_string(phong.phutBD);
    string GIAYBD = to_string(phong.giayBD);
    string NGAYBD = to_string(phong.ngayBD);
    string THANGBD = to_string(phong.thangBD);
    string NAMBD = to_string(phong.namBD);
    // Nếu (ngày, phút, giây, ngày, tháng, năm) < 10 -> Thêm '0' vào đằng trước
    if (GIOBD.length() == 1)
        GIOBD = "0" + GIOBD;
    if (PHUTBD.length() == 1)
        PHUTBD = "0" + PHUTBD;
    if (GIAYBD.length() == 1)
        GIAYBD = "0" + GIAYBD;
    if (NGAYBD.length() == 1)
        NGAYBD = "0" + NGAYBD;
    if (THANGBD.length() == 1)
        THANGBD = "0" + THANGBD;
    if (NAMBD.length() == 1)
        NAMBD = "0" + NAMBD;

    string thoiGian = GIOBD + ":" + PHUTBD + ":" + GIAYBD + " - " + NGAYBD + "/" + THANGBD + "/" + NAMBD;

    if (phong.tinhTrang == 1)  // tinhTrang == 1 -> phòng đã có người sử dụng
        tinhTrangPhong = "Đầy";
    else  // tinhTrang == 0 -> phòng trống
        tinhTrangPhong = "Trống";
    if (phong.loaiPhong == 1)  // loaiPhong == 1 -> phòng cao cấp
        loaiKieuPhong = "Cao cấp";
    else  // loaiPhong == 0 -> phòng thường
        loaiKieuPhong = "Thường";

    cout << setw(10) << left << "| " + phong.maPhong << "|";
    cout << setw(10) << left << " " + to_string(phong.soPhong) << "|";
    if (loaiKieuPhong == "Thường")
        cout << setw(23) << left << " " + loaiKieuPhong << "|";
    else
        cout << setw(22) << left << " " + loaiKieuPhong << "|";
    if (tinhTrangPhong == "Đầy")
        cout << setw(23) << left << " " + tinhTrangPhong << "|";
    else
        cout << setw(22) << left << " " + tinhTrangPhong << "|";

    if (phong.tinhTrang != 0) {
        if (phong.ngayBD != 0 && phong.thangBD != 0 && phong.namBD != 0)
            cout << setw(23) << left << " " + thoiGian << "|";
        else
            cout << setw(23) << left << " ";
        cout << "\n";
    } else
        cout << setw(23) << left << " "
             << "|" << "\n";
}

void docMotPhong(ifstream &fileIn, Phong &phong) {
    getline(fileIn, phong.maPhong, ' ');
    fileIn >> phong.soPhong;
    fileIn >> phong.loaiPhong;
    fileIn >> phong.tinhTrang;
    fileIn.ignore();
}

void ghiMotPhong(ofstream &fileOut, Phong phong) {
    fileOut << phong.maPhong << ' ';
    fileOut << phong.soPhong << ' ';
    fileOut << phong.loaiPhong << ' ';
    fileOut << phong.tinhTrang;
}
void docGiaTien(Phong &phong) {
    string fileName = "../File/phong/giatien.txt";
    ifstream fileIn(fileName);
    if (fileIn.fail()) {
        cout << "\n\t(!) Không tìm thấy tập tin `giatien.txt`, tạo tập tin mới" << "\n";
        ofstream fileOut(fileName);
        fileOut.close();
    } else {
        while (!fileIn.eof()) {
            fileIn >> phong.giaTienThuong;
            fileIn >> phong.giaTienCaoCap;
        }
    }
    fileIn.close();
}
void ghiGiaTien(Phong phong) {
    string fileName = "../File/phong/giatien.txt";
    ofstream fileOut(fileName);
    if (fileOut.fail()) {
        cout << "\n\t(!) Không tìm thấy tập tin `giatien.txt`" << "\n";
        system("pause");
    } else {
        fflush(stdin);
        fileOut << phong.giaTienThuong << ' ';
        fileOut << phong.giaTienCaoCap;
    }
    fileOut.close();
}

void thietLapGiaTien(Phong &phong) {
    cout << "\n*----------- GIÁ TIỀN HIỆN TẠI -----------*\n";
    cout << setw(20) << left << "| Phòng thường:";
    cout << setw(25) << right << to_string(phong.giaTienThuong) + " VND"
         << " |" << "\n";
    cout << setw(20) << left << "| Phòng cao cấp:";
    cout << setw(24) << right << to_string(phong.giaTienCaoCap) + " VND"
         << " |";
    cout << "\n*-----------------------------------------*";
    cout << "\n(?) Nhập giá tiền phòng thường / 1 giờ: ";
    cin >> phong.giaTienThuong;
    cout << "\n(?) Nhập giá tiền phòng cao cấp / 1 giờ: ";
    cin >> phong.giaTienCaoCap;
    cout << "\n\t(!) Thiết lập giá tiền thành công\n";
    system("pause");
    ghiGiaTien(phong);
}