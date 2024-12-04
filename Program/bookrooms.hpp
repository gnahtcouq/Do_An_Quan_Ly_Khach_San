#pragma once
#include "bookaroom.hpp"
#include "bookrooms.hpp"

struct Node {
    ThueMotPhong data;
    Node *pNext;
};

struct ThueNhieuPhong {
    Node *pHead;
    Node *pTail;
};

void taoListThueMotPhong(ThueNhieuPhong &);                           // tạo List
void themNodeVaoDau(ThueNhieuPhong &, ThueMotPhong);                  // thêm Node vào đầu
void themNodeVaoCuoi(ThueNhieuPhong &, ThueMotPhong);                 // thêm Node vào cuối
void xoaNodeDauTien(ThueNhieuPhong &);                                // xóa Node đầu tiên
void xoaNodeCuoiCung(ThueNhieuPhong &);                               // xóa Node cuối cùng
void giaiPhongDanhSachNguoiThueTrucTiep(ThueNhieuPhong &);            // giải phóng danh sách người thuê trực tiếp
void thuePhong(Phong[], int);                                         // mở phòng trực tiếp
void thanhToan(Phong[], int);                                         // thanh toán
Node *taoNodeThueMotPhong(ThueMotPhong);                              // tạo Node
void sapXepDanhSachNguoiThueTheoSoPhong_QuickSort(ThueNhieuPhong &);  // sắp xếp danh sách người thuê theo số phòng
void docDanhSachNguoiThueTrucTiep(ThueNhieuPhong &, Phong[], int &);  // đọc danh sách người thuê trực tiếp từ file
void ghiDanhSachNguoiThueTrucTiep(ThueNhieuPhong, int);               // ghi danh sách người thuê trực tiếp ra file
int tinhSoNgayGiuaHaiMocThoiGian(int, int, int, int, int, int);       // tính số ngày sử dụng

void taoListThueMotPhong(ThueNhieuPhong &thueNhieuPhong) {
    thueNhieuPhong.pHead = NULL;
    thueNhieuPhong.pTail = NULL;
}

Node *taoNodeThueMotPhong(ThueMotPhong thueMotPhong) {
    Node *p = new Node;
    if (p == NULL) {
        cout << "\n\t(!) Không đủ bộ nhớ" << "\n";
        return NULL;
    } else {
        p->data = thueMotPhong;
        p->pNext = NULL;
    }
    return p;
}

void themNodeVaoDau(ThueNhieuPhong &thueNhieuPhong, ThueMotPhong thueMotPhong) {
    Node *p = taoNodeThueMotPhong(thueMotPhong);
    if (thueNhieuPhong.pHead == NULL)
        thueNhieuPhong.pHead = thueNhieuPhong.pTail = p;
    else {
        p->pNext = thueNhieuPhong.pHead;
        thueNhieuPhong.pHead = p;
    }
}

void themNodeVaoCuoi(ThueNhieuPhong &thueNhieuPhong, ThueMotPhong thueMotPhong) {
    Node *p = taoNodeThueMotPhong(thueMotPhong);
    if (thueNhieuPhong.pHead == NULL)
        thueNhieuPhong.pHead = thueNhieuPhong.pTail = p;
    else {
        thueNhieuPhong.pTail->pNext = p;
        thueNhieuPhong.pTail = p;
    }
}

void xoaNodeDauTien(ThueNhieuPhong &thueNhieuPhong) {
    if (thueNhieuPhong.pHead == NULL)  // không có phần tử nào
        return;
    else {
        Node *p = thueNhieuPhong.pHead;
        thueNhieuPhong.pHead = p->pNext;
        delete p;
    }
}

void xoaNodeCuoiCung(ThueNhieuPhong &thueNhieuPhong) {
    if (thueNhieuPhong.pHead == NULL)
        return;
    // nếu phần tử nằm đầu cũng là phần tử nằm cuối
    else if (thueNhieuPhong.pHead == thueNhieuPhong.pTail)
        xoaNodeDauTien(thueNhieuPhong);
    else {
        for (Node *t = thueNhieuPhong.pHead; t != NULL; t = t->pNext) {
            if (t->pNext == thueNhieuPhong.pTail) {
                delete thueNhieuPhong.pTail;
                t->pNext = NULL;
                thueNhieuPhong.pTail = t;
                return;
            }
        }
    }
}

void giaiPhongDanhSachNguoiThueTrucTiep(ThueNhieuPhong &thueNhieuPhong) {
    Node *t = NULL;
    while (thueNhieuPhong.pHead != NULL) {
        t = thueNhieuPhong.pHead;
        thueNhieuPhong.pHead = thueNhieuPhong.pHead->pNext;
        delete t;
    }
}

void sapXepDanhSachNguoiThueTheoSoPhong_QuickSort(ThueNhieuPhong &thueNhieuPhong) {
    ThueNhieuPhong t1, t2;
    Node *tag, *p;
    if (thueNhieuPhong.pHead == thueNhieuPhong.pTail)
        return;
    taoListThueMotPhong(t1);
    taoListThueMotPhong(t2);
    tag = thueNhieuPhong.pHead;
    thueNhieuPhong.pHead = thueNhieuPhong.pHead->pNext;
    tag->pNext = NULL;
    while (thueNhieuPhong.pHead != NULL) {
        p = thueNhieuPhong.pHead;
        thueNhieuPhong.pHead = thueNhieuPhong.pHead->pNext;
        p->pNext = NULL;
        if (p->data.phong <= tag->data.phong)
            themNodeVaoDau(t1, p->data);
        else
            themNodeVaoDau(t2, p->data);
    }
    sapXepDanhSachNguoiThueTheoSoPhong_QuickSort(t1);
    sapXepDanhSachNguoiThueTheoSoPhong_QuickSort(t2);
    if (t1.pHead != NULL) {
        thueNhieuPhong.pHead = t1.pHead;
        t1.pTail->pNext = tag;
    } else
        thueNhieuPhong.pHead = tag;
    tag->pNext = t2.pHead;
    if (t2.pHead != NULL)
        thueNhieuPhong.pTail = t2.pTail;
    else
        thueNhieuPhong.pTail = tag;
}

void thuePhong(Phong nhieuPhong[], int n) {
    if (n != 0) {
        if (kiemTraHetPhong(nhieuPhong, n)) {  // nếu hết phòng
            cout << "\n\t(!) Hết phòng" << "\n";
            system("pause");
        } else {
            int gioBD = 0, phutBD = 0, giayBD = 0, ngayBD = 0, thangBD = 0, namBD = 0;
            ThueMotPhong r;
            chonPhong(r, nhieuPhong, n);
            r.phong->tinhTrang = 1;  // cập nhật lại tình trạng phòng -> 1 (phòng đã có người sử dụng)
            layThoiGianHeThong(gioBD, phutBD, giayBD, ngayBD, thangBD, namBD);
            r.phong->gioBD = gioBD;
            r.phong->phutBD = phutBD;
            r.phong->giayBD = giayBD;
            r.phong->ngayBD = ngayBD;
            r.phong->thangBD = thangBD;
            r.phong->namBD = namBD;
            cout << "\n\t(!) Thuê phòng thành công" << "\n";
            system("pause");
        }
    } else {
        cout << "\n\t(!) Danh sách phòng trống" << "\n";
        system("pause");
    }
}

void docDanhSachNguoiThueTrucTiep(ThueNhieuPhong &thueNhieuPhong, Phong nhieuPhong[], int &n) {
    string fileName = "../File/phong/danhsachthue.txt";
    ifstream fileIn(fileName);
    if (fileIn.fail()) {
        cout << "\n\t(!) Không tìm thấy tập tin `danhsachthue.txt`, tạo tập tin mới" << "\n";
        ofstream fileOut(fileName);
        fileOut << '0';
        fileOut.close();
        system("pause");
    } else {
        ThueMotPhong r;
        fileIn >> n;
        fileIn.ignore();
        for (int i = 0; i < n; i++) {
            docMotNguoiThueTrucTiep(fileIn, r, nhieuPhong, n);
            themNodeVaoCuoi(thueNhieuPhong, r);
        }
    }
    fileIn.close();
}

void ghiDanhSachNguoiThueTrucTiep(ThueNhieuPhong thueNhieuPhong, int n) {
    string fileName = "../File/phong/danhsachthue.txt";
    ofstream fileOut(fileName);
    if (fileOut.fail()) {
        cout << "\n\t(!) Không tìm thấy tập tin `danhsachthue.txt`" << "\n";
        system("pause");
    } else {
        fileOut << n << endl;
        for (Node *t = thueNhieuPhong.pHead; t != NULL; t = t->pNext) {
            ghiMotNguoiThueTrucTiep(fileOut, t->data);
            if (t->pNext != NULL)
                fileOut << endl;
        }
    }
    fileOut.close();
}

void thanhToan(Phong nhieuPhong[], int n) {
    if (n != 0) {
        bool kiemTra = kiemTraTrangThai(nhieuPhong, n);
        if (kiemTra == true) {
            Phong p;
            ThueMotPhong r;
            int gioSD = 0, phutSD = 0, giaySD = 0;
            int gioKT = 0, phutKT = 0, giayKT = 0, ngayKT = 0, thangKT = 0, namKT = 0;
            int soNgay = 0, thoiGian1 = 0, thoiGian2 = 0, tongThoiGian = 0;
            long long thoiGianBatDau = 0, thoiGianKetThuc = 0;
            double soTienMotGiay = 0;
            //
            //
            chonPhongCanThanhToan(r, nhieuPhong, n);  // hàm này trong file bookaroom.hpp
            r.phong->tinhTrang = 0;                   // cập nhật lại tình trạng phòng -> 0 (phòng trống)
            //
            //
            // Lấy thời gian kết thúc
            layThoiGianHeThong(gioKT, phutKT, giayKT, ngayKT, thangKT, namKT);
            r.phong->gioKT = gioKT;
            r.phong->phutKT = phutKT;
            r.phong->giayKT = giayKT;
            r.phong->ngayKT = ngayKT;
            r.phong->thangKT = thangKT;
            r.phong->namKT = namKT;
            //
            //
            // Tính khoảng thời gian giữa 2 mốc thời gian
            if (r.phong->namBD == r.phong->namKT) {
                if (r.phong->thangBD == r.phong->thangKT) {
                    if (r.phong->ngayBD == r.phong->ngayKT)
                        thoiGianBatDau = 3600 * r.phong->gioBD + 60 * r.phong->phutBD + r.phong->giayBD;
                    else
                        thoiGianBatDau = 86400 - (3600 * r.phong->gioBD + 60 * r.phong->phutBD + r.phong->giayBD);
                    if (r.phong->ngayBD < r.phong->ngayKT)
                        thoiGianKetThuc = 3600 * r.phong->gioKT + 60 * r.phong->phutKT + r.phong->giayKT;
                    else {
                        thoiGianKetThuc = thoiGianBatDau - (3600 * r.phong->gioKT + 60 * r.phong->phutKT + r.phong->giayKT);
                        if (thoiGianKetThuc < 0)
                            thoiGianKetThuc = -thoiGianKetThuc;
                    }
                } else {
                    thoiGianBatDau = 86400 - (3600 * r.phong->gioBD + 60 * r.phong->phutBD + r.phong->giayBD);
                    thoiGianKetThuc = 3600 * r.phong->gioKT + 60 * r.phong->phutKT + r.phong->giayKT;
                }
            } else {
                thoiGianBatDau = 86400 - (3600 * r.phong->gioBD + 60 * r.phong->phutBD + r.phong->giayBD);
                thoiGianKetThuc = 3600 * r.phong->gioKT + 60 * r.phong->phutKT + r.phong->giayKT;
            }
            //
            //
            // Tính tổng thời gian đã sử dụng
            soNgay = tinhSoNgayGiuaHaiMocThoiGian(r.phong->ngayBD, r.phong->thangBD, r.phong->namBD, r.phong->ngayKT, r.phong->thangKT, r.phong->namKT);
            thoiGian1 = thoiGianBatDau + (86400 * (soNgay - 1));  // tổng thời gian của ngày bắt đầu + với thời gian của những ngày sử dụng tròn 24 tiếng
            thoiGian2 = thoiGianKetThuc;                          // tổng thời gian của ngày kết thúc
            tongThoiGian = thoiGian1 + thoiGian2;                 // tổng thời gian đã sử dụng
            //
            //
            // Quy đổi tổng thời gian ra giờ, phút, giây
            if (r.phong->namBD == r.phong->namKT)
                if (r.phong->thangBD == r.phong->thangKT)
                    if (r.phong->ngayBD == r.phong->ngayKT)
                        tongThoiGian = thoiGianKetThuc;
            gioSD = tongThoiGian / 3600;
            phutSD = (tongThoiGian % 3600) / 60;
            giaySD = (tongThoiGian % 3600) % 60;
            //
            //
            // Chuyển định dạng giờ, phút, giây, ngày, tháng, năm sang kiểu chuỗi
            string GIOSD = to_string(gioSD);
            string PHUTSD = to_string(phutSD);
            string GIAYSD = to_string(giaySD);
            string GIOBD = to_string(r.phong->gioBD);
            string PHUTBD = to_string(r.phong->phutBD);
            string GIAYBD = to_string(r.phong->giayBD);
            string NGAYBD = to_string(r.phong->ngayBD);
            string THANGBD = to_string(r.phong->thangBD);
            string NAMBD = to_string(r.phong->namBD);
            string GIOKT = to_string(gioKT);
            string PHUTKT = to_string(phutKT);
            string GIAYKT = to_string(giayKT);
            string NGAYKT = to_string(ngayKT);
            string THANGKT = to_string(thangKT);
            string NAMKT = to_string(namKT);
            //
            //
            // Nếu (ngày, phút, giây, ngày, tháng, năm) < 10 -> Thêm '0' vào đằng trước
            if (GIOSD.length() == 1) GIOSD = "0" + GIOSD;
            if (PHUTSD.length() == 1) PHUTSD = "0" + PHUTSD;
            if (GIAYSD.length() == 1) GIAYSD = "0" + GIAYSD;
            if (GIOBD.length() == 1) GIOBD = "0" + GIOBD;
            if (PHUTBD.length() == 1) PHUTBD = "0" + PHUTBD;
            if (GIAYBD.length() == 1) GIAYBD = "0" + GIAYBD;
            if (NGAYBD.length() == 1) NGAYBD = "0" + NGAYBD;
            if (THANGBD.length() == 1) THANGBD = "0" + THANGBD;
            if (NAMBD.length() == 1) NAMBD = "0" + NAMBD;
            if (GIOKT.length() == 1) GIOKT = "0" + GIOKT;
            if (PHUTKT.length() == 1) PHUTKT = "0" + PHUTKT;
            if (GIAYKT.length() == 1) GIAYKT = "0" + GIAYKT;
            if (NGAYKT.length() == 1) NGAYKT = "0" + NGAYKT;
            if (THANGKT.length() == 1) THANGKT = "0" + THANGKT;
            if (NAMKT.length() == 1) NAMKT = "0" + NAMKT;
            //
            //
            string thoiGianSuDung = GIOSD + ":" + PHUTSD + ":" + GIAYSD;
            string thoiGianLucDau = GIOBD + ":" + PHUTBD + ":" + GIAYBD + " - " + NGAYBD + "/" + THANGBD + "/" + NAMBD;
            string thoiGianThanhToan = GIOKT + ":" + PHUTKT + ":" + GIAYKT + " - " + NGAYKT + "/" + THANGKT + "/" + NAMKT;
            //
            //
            docGiaTien(p);
            r.phong->giaTienThuong = p.giaTienThuong;
            r.phong->giaTienCaoCap = p.giaTienCaoCap;
            if (r.phong->loaiPhong == 0)
                soTienMotGiay = r.phong->giaTienThuong / 3600;
            else
                soTienMotGiay = r.phong->giaTienCaoCap / 3600;
            r.phong->giaTien = tongThoiGian * soTienMotGiay;
            string giaTien = to_string(r.phong->giaTien) + " VND";
            //
            //
            string loaiKieuPhong;
            if (r.phong->loaiPhong == 1)  // kieuMay == 1 -> phòng cao cấp
                loaiKieuPhong = "Cao cấp";
            else  // kieuMay == 0 -> phòng thường
                loaiKieuPhong = "Thường";
            //
            //
            // Xuất thông tin thanh toán
            system("cls");
            cout << "\nMENU/THANH TOÁN" << "\n";
            cout << "\n*----------------- THÔNG TIN THANH TOÁN ----------------*\n";
            cout << setw(30) << left << "| Số phòng: ";
            cout << setw(28) << right << r.phong->soPhong << " |\n";
            cout << setw(30) << left << "| Loại phòng: ";
            if (loaiKieuPhong == "Thường")
                cout << setw(31) << right << loaiKieuPhong << " |\n";
            else
                cout << setw(30) << right << loaiKieuPhong << " |\n";
            cout << setw(30) << left << "| Thời gian bắt đầu: ";
            cout << setw(32) << right << thoiGianLucDau << " |\n";
            cout << setw(30) << left << "| Xuất hóa đơn lúc: ";
            cout << setw(31) << right << thoiGianThanhToan << " |\n";
            cout << setw(30) << left << "| Thời gian đã sử dụng:  ";
            cout << setw(30) << right << thoiGianSuDung << " |\n";
            cout << setw(30) << left << "| Số tiền cần thanh toán: ";
            cout << setw(29) << right << giaTien << " |";
            cout << "\n*-------------------------------------------------------*" << "\n";
            //
            //
            r.phong->gioBD = 0;
            r.phong->phutBD = 0;
            r.phong->giayBD = 0;
            r.phong->ngayBD = 0;
            r.phong->thangBD = 0;
            r.phong->namBD = 0;
            //
            //
            // Ghi lịch sử thanh toán ra file
            string fileNameLichSu = "../File/lichsu/lichsuthanhtoan.txt";
            ofstream fileOut(fileNameLichSu, ios::app);
            if (fileOut.fail()) {
                cout << "\n\t(!) Không tìm thấy tập tin" << "\n";
                system("pause");
            } else {
                fileOut << setw(25) << left << "| " + thoiGianLucDau << "|";
                fileOut << setw(25) << left << " " + thoiGianThanhToan << "|";
                fileOut << setw(12) << left << " " + to_string(r.phong->soPhong) << "|";
                if (loaiKieuPhong == "Thường")
                    fileOut << setw(15) << left << " " + loaiKieuPhong << "|";
                else
                    fileOut << setw(14) << left << " " + loaiKieuPhong << "|";
                fileOut << setw(20) << right << giaTien + " " << "|\n";
            }
            fileOut.close();
            //
            //
            // Ghi doanh thu ra file
            double doanhThu;
            string fileNameDoanhThu = "../File/doanhthu/" + NGAYKT + "_" + THANGKT + "_" + NAMKT + ".txt";
            fstream docGhiDoanhThu;
            // Đọc doanh thu cũ vào trước
            docGhiDoanhThu.open(fileNameDoanhThu, ios::in);
            docGhiDoanhThu >> doanhThu;
            docGhiDoanhThu.close();
            // Cộng doanh thu mới vào rồi ghi ngược lại vào file
            docGhiDoanhThu.open(fileNameDoanhThu, ios::out);
            doanhThu += (double)r.phong->giaTien;
            docGhiDoanhThu << to_string((long long)doanhThu);
            docGhiDoanhThu.close();
            //
            //
            // In hóa đơn ra máy in
            string fileNameHoaDon = "../File/xuathoadon.txt";
            fstream ghiHoaDon;
            ghiHoaDon.open(fileNameHoaDon, ios::out);
            ghiHoaDon << "\n*---------------------- STU HOTEL ----------------------*\n";
            ghiHoaDon << "\n*----------------- THÔNG TIN THANH TOÁN ----------------*\n";
            ghiHoaDon << setw(30) << left << "| Số Phòng: ";
            ghiHoaDon << setw(28) << right << r.phong->soPhong << " |\n";
            ghiHoaDon << setw(30) << left << "| Loại phòng: ";
            if (loaiKieuPhong == "Thường")
                ghiHoaDon << setw(31) << right << loaiKieuPhong << " |\n";
            else
                ghiHoaDon << setw(30) << right << loaiKieuPhong << " |\n";
            ghiHoaDon << setw(30) << left << "| Thời gian bắt đầu: ";
            ghiHoaDon << setw(32) << right << thoiGianLucDau << " |\n";
            ghiHoaDon << setw(30) << left << "| Xuất hóa đơn lúc: ";
            ghiHoaDon << setw(31) << right << thoiGianThanhToan << " |\n";
            ghiHoaDon << setw(30) << left << "| Thời gian đã sử dụng: ";
            ghiHoaDon << setw(31) << right << thoiGianSuDung << " |\n";
            ghiHoaDon << setw(30) << left << "| Số tiền cần thanh toán: ";
            ghiHoaDon << setw(29) << right << giaTien << " |";
            ghiHoaDon << "\n*-------------------------------------------------------*\n";
            ghiHoaDon << "\nSTU HOTEL ghi nhận các đóng góp của quý khách nhằm\nnâng cao chất lượng dịch vụ thông qua";
            ghiHoaDon << "\nHotline: 0866 085 276 hoặc";
            ghiHoaDon << "\nEmail: buithuyquyen0397@gmail.com";
            ghiHoaDon << "\nTrân trọng.";
            ghiHoaDon << "\n*------------------- CẢM ƠN QUÝ KHÁCH ------------------*\n";
            //
            //
            cout << "\n\t(!) Thanh toán thành công" << "\n";
            system("pause");
        } else {
            cout << "\n\t(!) Không có phòng đang được sử dụng" << "\n";
            system("pause");
        }
    } else {
        cout << "\n\t(!) Danh sách phòng tính trống" << "\n";
        system("pause");
    }
}

int tinhSoNgayGiuaHaiMocThoiGian(int ngayBD, int thangBD, int namBD, int ngayKT, int thangKT, int namKT) {
    int soNgay = 0;
    while (namKT >= namBD) {
        if (namKT == namBD && thangKT == thangBD) {
            soNgay += ngayKT - ngayBD;
            break;
        } else {
            // Tháng 4, 6, 9, 11 có 30 ngày
            if (thangBD == 4 || thangBD == 6 || thangBD == 9 || thangBD == 11)
                soNgay += 30 - ngayBD;
            // Tháng 1, 3, 5, 7, 8, 10, 12 có 31 ngày
            if (thangBD == 1 || thangBD == 3 || thangBD == 5 || thangBD == 7 || thangBD == 8 || thangBD == 10 || thangBD == 12)
                soNgay += 31 - ngayBD;
            // Tháng 2 có 28 ngày (trừ năm nhuận có 29 ngày)
            if (thangBD == 2) {
                if ((namBD % 4 == 0) && (namBD % 100 != 0) || (namBD % 400 == 0))
                    soNgay += 29 - ngayBD;
                else
                    soNgay += 28 - ngayBD;
            }
            thangBD++, ngayBD = 0;
            if (thangBD == 13)  // tăng năm lên
                namBD++, thangBD = 1;
        }
    }
    return soNgay;
}