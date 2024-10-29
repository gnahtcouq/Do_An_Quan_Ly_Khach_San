#pragma once
#include "utils.hpp"

struct Phong {
    string maPhong;                          // mã phòng
    int soPhong;                             // số phòng
    bool loaiPhong;                          // loại phòng: thường hoặc cao cấp
    bool tinhTrang = 0;                      // tình trạng phòng - 0:trống   1:đầy
    int gioBD = 0, phutBD = 0, giayBD = 0;   // thời gian bắt đầu (giờ:phút:giây)
    int ngayBD = 0, thangBD = 0, namBD = 0;  // thời gian bắt đầu (ngày/tháng/năm)
    int gioKT = 0, phutKT = 0, giayKT = 0;   // thời gian kết thúc (giờ:phút:giây)
    int ngayKT = 0, thangKT = 0, namKT = 0;  // thời gian kết thúc (ngày/tháng/năm)
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
    Phong mt;
    int soPhongTam;
    mt.maPhong = taoMaPhong(nhieuPhong, n);
    string fileName = "../File/phong/danhsachphong.txt";

    ifstream fileIn(fileName);
    bool fileExists = !fileIn.fail();
    fileIn.close();

    if (fileExists && n > 0) {
        do {
            cout << "\n(?) Nhập số phòng (nhập -1 để hủy): ";
            cin >> mt.soPhong;
            if (mt.soPhong == -1) {
                cout << "\n\t(!) Hủy thêm phòng" << "\n";
                system("pause");
                return;  // Exit the function if the user cancels
            }
            soPhongTam = n + 1;
            if (kiemTraTrungSoPhong(nhieuPhong, n, mt.soPhong) != -1) {
                cout << "\n\t(!) Số phòng đã tồn tại. Xin hãy nhập lại" << "\n";
            } else if (mt.soPhong > soPhongTam) {
                cout << "\n\t(!) Số phòng chỉ được lớn hơn số phòng lớn nhất hiện tại 1 đơn vị. Xin hãy nhập lại" << "\n";
            }
        } while (kiemTraTrungSoPhong(nhieuPhong, n, mt.soPhong) != -1 || mt.soPhong > soPhongTam);
    } else {
        do {
            cout << "\n(?) Nhập số phòng (nhập -1 để hủy): ";
            cin >> mt.soPhong;
            if (mt.soPhong == -1) {
                cout << "\n\t(!) Hủy thêm phòng" << "\n";
                system("pause");
                return;  // Exit the function if the user cancels
            }
            if (mt.soPhong != 1) {
                cout << "\n\t(!) Số phòng khởi đầu mặc định sẽ là 1. Xin hãy nhập lại" << "\n";
            }
        } while (mt.soPhong != 1);
    }

    soPhong = mt.soPhong;
    do {
        cout << "\n(?) Nhập kiểu phòng (0: Thường - 1: Cao cấp, nhập -1 để hủy): ";
        cin >> mt.loaiPhong;
        if (mt.loaiPhong == -1) {
            cout << "\n\t(!) Hủy thêm phòng" << "\n";
            system("pause");
            return;  // Exit the function if the user cancels
        }
        if (mt.loaiPhong < 0 || mt.loaiPhong > 1) {
            cout << "\n\t(!) Kiểu phòng không hợp lệ. Xin hãy nhập lại" << "\n";
        }
    } while (mt.loaiPhong < 0 || mt.loaiPhong > 1);

    for (int i = n - 1; i >= 0; i--)
        nhieuPhong[i + 1] = nhieuPhong[i];
    nhieuPhong[0] = mt;
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
    if (phong.tinhTrang == 1)  // tinhTrang == 1 -> Máy đã có người sử dụng
        tinhTrangPhong = "Đầy";
    else  // tinhTrang == 0 -> Máy trống
        tinhTrangPhong = "Trống";
    if (phong.loaiPhong == 1)  // loaiPhong == 1 -> Máy cao cấp
        loaiKieuPhong = "Cao cấp";
    else  // loaiPhong == 0 -> Máy thường
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

    if (phong.tinhTrang == 1)  // tinhTrang == 1 -> Máy đã có người sử dụng
        tinhTrangPhong = "Đầy";
    else  // tinhTrang == 0 -> Máy trống
        tinhTrangPhong = "Trống";
    if (phong.loaiPhong == 1)  // loaiPhong == 1 -> Máy cao cấp
        loaiKieuPhong = "Cao cấp";
    else  // loaiPhong == 0 -> Máy thường
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