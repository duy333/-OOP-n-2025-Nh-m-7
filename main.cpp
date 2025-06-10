//main.cpp
#include "benhnhi.h"
#include "phuhuynh.h"
#include "toathuoc.h"
#include "bacsi.h"
#include "lichhen.h"
#include "letan.h"
#include <iostream>
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

bool maBenhNhiDaTonTai(const string& ma) {
    return filesystem::exists("bn" + ma + ".txt");
}

bool maPhuHuynhDaTonTai(const string& ma) {
    return filesystem::exists("ph" + ma + ".txt");
}

bool maBacSiDaTonTai(const string& ma) {
    return filesystem::exists("bs" + ma + ".txt");
}

int main() {
    vector<BenhNhi> danhSachBN = BenhNhi::docDanhSachTuFile(".");
    int luaChon;
    do {
        cout << "\n========= MENU QUAN LY PHONG KHAM =========\n";
        cout << "1. Them benh nhi moi\n";
        cout << "2. Them phu huynh moi\n";
        cout << "3. Chinh sua thong tin benh nhi theo ID\n";
        cout << "4. Them thong tin kham moi\n";
        cout << "5. Tim thong tin kham benh theo ma benh nhi & ma kham\n";
        cout << "6. Them bac si moi\n";
        cout << "7. Xem danh sach bac si\n";
        cout << "8. Dat lich hen kham\n";
        cout << "9. Xem lich hen cua bac si\n";
        cout << "10. Tinh tong hoa don lan kham\n";
        cout << "11. Them le tan moi\n";
        cout << "12.Xem lich hen cua benh nhi\n";
        cout << "0. Thoat\n";
        cout << "===========================================\n";
        cout << "Nhap lua chon: ";
        cin >> luaChon;
        cin.ignore();

        switch (luaChon) {
            case 1: {
                string ma;
                do {
                    cout << "Nhap ma benh nhi (vd: 0001): ";
                    getline(cin, ma);
                    if (maBenhNhiDaTonTai(ma)) {
                        cout << "⚠ Ma benh nhi da ton tai. Nhap lai.\n";
                    } else break;
                } while (true);

                BenhNhi bn = BenhNhi::nhapBenhNhiCoLienKetPhuHuynh();
                danhSachBN.push_back(bn);
                bn.luuVaoFile("");
                break;
            }
            case 2: {
                string maPH;
                do {
                    cout << "Nhap ma phu huynh (vd: 0001): ";
                    getline(cin, maPH);
                    if (maPhuHuynhDaTonTai(maPH)) {
                        cout << "⚠ Ma phu huynh da ton tai. Nhap lai.\n";
                    } else break;
                } while (true);

                PhuHuynh ph = PhuHuynh::nhapPhuHuynh();
                break;
            }
            case 3: {
                BenhNhi::chinhSuaBenhNhiTheoID(danhSachBN);
                break;
            }
            case 4: {
                ToaThuoc::themThongTinKhamMoi(danhSachBN);
                break;
            }
            case 5: {
                string maBN, maKham;
                cout << "Nhap ma benh nhi: ";
                getline(cin, maBN);
                cout << "Nhap ma kham: ";
                getline(cin, maKham);
                ToaThuoc::timKiemThongTinTheoMa(maBN, maKham);
                break;
            }
            case 6: {
                string maBS;
                do {
                    cout << "Nhap ma bac si (vd: 0001): ";
                    getline(cin, maBS);
                    if (maBacSiDaTonTai(maBS)) {
                        cout << "⚠ Ma bac si da ton tai. Nhap lai.\n";
                    } else break;
                } while (true);

                BacSi bs = BacSi::nhapBacSi();
                bs.luuVaoFile();
                break;
            }
            case 7: {
                vector<BacSi> danhSachBS = BacSi::docDanhSachTuFile(".");
                for (const auto& bs : danhSachBS) {
                    bs.hienThiThongTin();
                }
                break;
            }
            case 8: {
                LichHen lh = LichHen::nhapLichHen();
                if (!lh.getMaCuocHen().empty()) {
                    lh.luuVaoFile();
                }
                break;
            }
            case 9: {
                string maBS;
                cout << "Nhap ma bac si: ";
                getline(cin, maBS);
                vector<LichHen> lich = LichHen::docLichTheoBacSi(maBS);
                if (lich.empty()) {
                    cout << "⚠ Khong co lich hen nao cho bac si nay.\n";
                } else {
                    for (const auto& lh : lich) {
                        lh.hienThi();
                    }
                }
                break;
            }
            case 10: {
                ToaThuoc::tinhTongHoaDon();
                break;
            }
            case 11: {  // Giả sử chức năng thêm lễ tân là số 6
            string maLT;
            do {
                cout << "Nhap ma le tan moi: ";
                getline(cin, maLT);

                string tenFile = "lt" + maLT + ".txt";
                if (fs::exists(tenFile)) {
                    cout << "❌ Ma le tan da ton tai! Vui long nhap ma khac.\n";
                } else {
                    break;
                }
            } while (true);

            LeTan lt = LeTan::nhapLeTan();
            lt.setMaLeTan(maLT); // Gán lại mã đã được kiểm tra ở trên
            lt.luuVaoFile();
            lt.hienThiThongTin();
            break;
            }
            case 12: {
            string maBN;
            cout << "Nhap ma benh nhi: ";
            getline(cin, maBN);

            if (!filesystem::exists("bn" + maBN + ".txt")) {
                cout << "⚠ Ma benh nhi khong ton tai.\n";
                break;
            }

            vector<LichHen> danhSach = LichHen::docLichTheoBenhNhi(maBN);
            if (danhSach.empty()) {
                cout << "⚠ Benh nhi khong co lich hen nao.\n";
            } else {
                cout << "\n=== Danh sach lich hen cua benh nhi " << maBN << " ===\n";
                for (const auto& lh : danhSach) {
                    lh.hienThi();
                    cout << "----------------------\n";
                }
            }

            break;
            }


            case 0:
                cout << "Tam biet!\n";
                break;
            default:
                cout << "Lua chon khong hop le. Vui long nhap lai.\n";
        }
    } while (luaChon != 0);

    return 0;
}
