//toathuoc.cpp
#include "toathuoc.h"
#include "benhnhi.h"
#include "dkinput.h"
#include "lichhen.h"
#include <iostream>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;
#include <map>
#include <iomanip>

using namespace std;

ToaThuoc::ToaThuoc() : daDatLichTruoc(false) {}
ToaThuoc::ToaThuoc(const string& maKham, const string& ngayKham, const string& trieuChung,
                   const string& chanDoan, const vector<Thuoc>& danhSachThuoc)
    : maKham(maKham), ngayKham(ngayKham), trieuChung(trieuChung),
      chanDoan(chanDoan), danhSachThuoc(danhSachThuoc) {}

void ToaThuoc::setMaKham(const string& ma) { maKham = ma; }
void ToaThuoc::setNgayKham(const string& ngay) { ngayKham = ngay; }
void ToaThuoc::setTrieuChung(const string& trieu) { trieuChung = trieu; }
void ToaThuoc::setChanDoan(const string& chuan) { chanDoan = chuan; }
void ToaThuoc::setDanhSachThuoc(const vector<Thuoc>& ds) { danhSachThuoc = ds; }

string ToaThuoc::getMaKham() const { return maKham; }
string ToaThuoc::getMaLichHen() const { return maLichHen; }
bool ToaThuoc::getDaDatLichTruoc() const { return daDatLichTruoc; }
string ToaThuoc::getNgayKham() const { return ngayKham; }
string ToaThuoc::getTrieuChung() const { return trieuChung; }
string ToaThuoc::getChanDoan() const { return chanDoan; }
vector<Thuoc> ToaThuoc::getDanhSachThuoc() const { return danhSachThuoc; }

ToaThuoc ToaThuoc::nhapToaThuoc() {
                ToaThuoc t;
                int n;
                string n_string;
                cout << "Nhap ma kham: ";
                getline(cin, t.maKham);
                do {
                    cout << "Nhap ngay kham benh (dd/mm/yyyy): ";
                    getline(cin, t.ngayKham);
                    if (!kiemTraNgay(t.ngayKham)) cout << "Ngay kham benh khong dung dinh dang!\n";
                } while (!kiemTraNgay(t.ngayKham));
                cout << "Nhap trieu chung: ";
                getline(cin, t.trieuChung);
                cout << "Nhap chan doan: ";
                getline (cin,t.chanDoan);
                 char chon;
                cout << "Co lich hen truoc khong? (y/n): ";
                cin >> chon;
                cin.ignore();
                if (chon == 'y' || chon == 'Y') {
                    t.daDatLichTruoc = true;
                    do {
                        cout << "Nhap ma lich hen: ";
                        getline(cin, t.maLichHen);
                        if (!LichHen::tonTaiMaHen(t.maLichHen)) {
                            cout << "⚠ Ma lich hen khong ton tai. Vui long nhap lai!\n";
                        } else {
                            cout << "✅ Da xac nhan lich hen truoc.\n";
                            break;
                        }
                    } while (true);
                } else {
                    t.daDatLichTruoc = false;
                    t.maLichHen = "";
                }
                do {
                    cout << "Nhap so luong thuoc: ";
                    getline(cin, n_string);
                    if (!kiemTraSoNguyen(n_string))
                        cout << "Vui long nhap so luong bang so!\n";
                } while (!kiemTraSoNguyen(n_string));
                n = stoi(n_string);
                for (int i = 0; i < n; ++i) {
                    Thuoc thuoc;
                    cout << "  Thuoc " << i + 1 << ":\n";
                    // Nhập tên thuốc
                    do {
                        cout << "Ten thuoc: ";
                        getline(cin, thuoc.ten);
                        if (thuoc.ten.empty()) {
                            cout << "⚠ Ten thuoc khong duoc bo trong.\n";
                        }
                    } while (thuoc.ten.empty());

                    // Nhập liều dùng
                    do {
                        cout << "Lieu dung: ";
                        getline(cin, thuoc.lieuDung);
                        if (thuoc.lieuDung.empty()) {
                            cout << "⚠ Lieu dung khong duoc bo trong.\n";
                        }
                    } while (thuoc.lieuDung.empty());

                    // Nhập hướng dẫn
                    do {
                        cout << "Huong dan su dung: ";
                        getline(cin, thuoc.huongDan);
                        if (thuoc.huongDan.empty()) {
                            cout << "⚠ Huong dan khong duoc bo trong.\n";
                        }
                    } while (thuoc.huongDan.empty());
                    t.danhSachThuoc.push_back(thuoc);
                }
                return t;
}

void ToaThuoc::hienThi() const {
    cout << "Ma kham: " << maKham << "\n";
    cout << "Ngay kham: " << ngayKham << "\n";
    cout << "Trieu chung: " << trieuChung << "\n";
    cout << "Chan doan: " << chanDoan << "\n";
    if (daDatLichTruoc) {
        cout << "🕒 Da dat lich hen truoc! Ma lich: " << maLichHen << "\n";
        LichHen lh = LichHen::timTheoMa(maLichHen);
        lh.hienThi();
    } else {
        cout << "📆 Khong co lich hen truoc.\n";
    }
    cout << "Danh sach thuoc:\n";
    for (size_t i = 0; i < danhSachThuoc.size(); ++i) {
        cout << "  - " << danhSachThuoc[i].ten
             << ", lieu dung: " << danhSachThuoc[i].lieuDung
             << ", huong dan: " << danhSachThuoc[i].huongDan << "\n";
    }
}


void ToaThuoc::themThongTinKhamMoi(vector<BenhNhi>& danhSach) {
    string maTim;
    cout << "Nhap ma benh nhi muon them lan kham moi: ";
    getline(cin, maTim);

    for (auto& bn : danhSach) {
        if (bn.getMaBenhNhi() == maTim) {
            ToaThuoc toa = ToaThuoc::nhapToaThuoc();
            string fileTen = "bn" + bn.getMaBenhNhi() + ".txt";

            // Check trùng mã khám
            ifstream fileCheck(fileTen);
            bool trungMaKham = false;
            string dong;
            while (getline(fileCheck, dong)) {
                if (dong.find("Ma kham:") != string::npos && dong.find(toa.getMaKham()) != string::npos) {
                    trungMaKham = true;
                    break;
                }
            }
            fileCheck.close();
            if (trungMaKham) {
                cout << "⚠ Ma kham da ton tai cho benh nhi nay. Vui long nhap ma kham khac.\n";
                return;
            }

            ofstream file(fileTen, ios::app);
            if (!file.is_open()) {
                cerr << "Khong the mo file " << fileTen << " de ghi\n";
                return;
            }

            file << "\n=== LAN KHAM MOI ===\n";
            file << "Ma kham: " << toa.getMaKham() << "\n";
            file << "Ngay kham: " << toa.getNgayKham() << "\n";
            file << "Trieu chung: " << toa.getTrieuChung() << "\n";
            file << "Chan doan: " << toa.getChanDoan() << "\n";
            if (toa.getDaDatLichTruoc()) {
                file << "Da dat lich truoc: Yes\n";
                file << "Ma lich hen: " << toa.getMaLichHen() << "\n";
            } else {
                file << "Da dat lich truoc: No\n";
            }

            file << "--- Toa thuoc ---\n";
            for (const auto& thuoc : toa.getDanhSachThuoc()) {
                file << "- Ten: " << thuoc.ten << "\n";
                file << "  + Lieu dung: " << thuoc.lieuDung << "\n";
                file << "  + Huong dan: " << thuoc.huongDan << "\n";
            }
            file << "---------------------------\n";

            file.close();
            cout << "Da them lan kham moi vao file " << fileTen << "\n";
            return;
        }
    }

    cout << "Khong tim thay benh nhi voi ma: " << maTim << "\n";
}

 void ToaThuoc::timKiemThongTinTheoMa(const string& maBN, const string& maKham,const string& maPhuHuynhDangNhap) {
    string tenFile = "bn" + maBN + ".txt";
    BenhNhi bn = BenhNhi::timBenhNhiTheoMa(maBN);
    if (bn.getPhuHuynh().getMaPhuHuynh() != maPhuHuynhDangNhap) {
        cout << "❌ Ban khong co quyen xem thong tin benh nhi nay!\n";
        return;
    }
    ifstream file(tenFile);
    if (!file.is_open()) {
        cout << "Khong tim thay benh nhi voi ma: " << maBN << ". Vui long nhap lai!\n";
        return;
    }

    string dong;
    bool timThayKham = false;
    bool dangInThongTin = false;

    while (getline(file, dong)) {
        if (dong.find("Ma kham:") != string::npos) {
            if (timThayKham) break; // đã tìm thấy xong lần khám, dừng

            size_t pos = dong.find(":");
            string maTrongFile = (pos != string::npos) ? dong.substr(pos + 2) : "";

            if (maTrongFile == maKham) {
                timThayKham = true;
                dangInThongTin = true;
                cout << "\n=== THONG TIN LAN KHAM ===\n" << dong << "\n";
            } else {
                dangInThongTin = false;
            }
        } else if (dangInThongTin) {
            if (dong.find("---------------------------") != string::npos)
                break;
            cout << dong << "\n";
        }
    }

    if (!timThayKham) {
        cout << "⚠ Ma kham khong ton tai cho benh nhi nay.\n";
    }

    file.close();
}

void ToaThuoc::timKiemThongTinTheoMaBS(const string& maBN, const string& maKham) {
    string tenFile = "bn" + maBN + ".txt";
    ifstream file(tenFile);
    if (!file.is_open()) {
        cout << "Khong tim thay benh nhi voi ma: " << maBN << ". Vui long nhap lai!\n";
        return;
    }

    string dong;
    bool timThayKham = false;
    bool dangInThongTin = false;

    while (getline(file, dong)) {
        if (dong.find("Ma kham:") != string::npos) {
            if (timThayKham) break; // đã tìm thấy xong lần khám, dừng

            size_t pos = dong.find(":");
            string maTrongFile = (pos != string::npos) ? dong.substr(pos + 2) : "";

            if (maTrongFile == maKham) {
                timThayKham = true;
                dangInThongTin = true;
                cout << "\n=== THONG TIN LAN KHAM ===\n" << dong << "\n";
            } else {
                dangInThongTin = false;
            }
        } else if (dangInThongTin) {
            if (dong.find("---------------------------") != string::npos)
                break;
            cout << dong << "\n";
        }
    }

    if (!timThayKham) {
        cout << "⚠ Ma kham khong ton tai cho benh nhi nay.\n";
    }

    file.close();
}

void ToaThuoc::tinhTongHoaDon() {
    string maBN, maKham;
    do {
        cout << "Nhap ma benh nhi: ";
        getline(cin, maBN);
        string fileTen = "bn" + maBN + ".txt";
        if (!fs::exists(fileTen)) {
            cout << "⚠ Ma benh nhi khong ton tai. Vui long nhap lai.\n";
        } else break;
    } while (true);

    string fileTen = "bn" + maBN + ".txt";

    do {
        cout << "Nhap ma kham: ";
        getline(cin, maKham);
        ifstream file(fileTen);
        bool timThay = false;
        string line;
        while (getline(file, line)) {
            if (line.find("Ma kham: ") != string::npos && line.find(maKham) != string::npos) {
                timThay = true;
                break;
            }
        }
        file.close();
        if (!timThay) {
            cout << "⚠ Ma kham khong ton tai cho benh nhi nay. Vui long nhap lai.\n";
        } else break;
    } while (true);

    // Lấy danh sách thuốc
    vector<string> tenThuoc;
    ifstream file(fileTen);
    string line;
    bool trongKham = false, dungKham = false;
    while (getline(file, line)) {
        if (line.find("Ma kham: ") != string::npos) {
            if (line.find(maKham) != string::npos)
                trongKham = true;
            else if (trongKham)
                dungKham = true;
        } else if (trongKham && line.find("- Ten:") != string::npos) {
            string ten = line.substr(line.find(":") + 2);
            tenThuoc.push_back(ten);
        } else if (dungKham) break;
    }
    file.close();

    // Nhập thông tin hóa đơn
    double phiKham, tongThuoc = 0, phiMau = 0, phiSieuAm = 0, phiNuocTieu = 0;
    string nhap;
    cout << "Nhap chi phi kham (VND): ";
    cin >> phiKham;
    cin.ignore();

    for (const auto& ten : tenThuoc) {
        double gia;
        cout << " - Gia cua thuoc '" << ten << "': ";
        cin >> gia;
        tongThuoc += gia;
    }
    cin.ignore();

    cout << "Co xet nghiem mau? (y/n): ";
    getline(cin, nhap);
    if (nhap == "y" || nhap == "Y") phiMau = 120000;

    cout << "Co sieu am? (y/n): ";
    getline(cin, nhap);
    if (nhap == "y" || nhap == "Y") phiSieuAm = 120000;

    cout << "Co xet nghiem nuoc tieu? (y/n): ";
    getline(cin, nhap);
    if (nhap == "y" || nhap == "Y") phiNuocTieu = 100000;

    double tong = phiKham + tongThuoc + phiMau + phiSieuAm + phiNuocTieu;
    double vat = tong * 0.05;
    double tongThanhToan = tong + vat;

    // Ghi hoa don vao file bệnh nhi ngay dưới mã khám tương ứng
    vector<string> noiDung;
    ifstream fileIn(fileTen);
    while (getline(fileIn, line)) {
        noiDung.push_back(line);
        if (line.find("Ma kham: ") != string::npos && line.find(maKham) != string::npos) {
            // Đánh dấu đang trong mã khám cần chèn
            while (getline(fileIn, line)) {
                noiDung.push_back(line);
                if (line.find("---------------------------") != string::npos) {
                    // Ngay sau đó chèn hóa đơn
                    noiDung.push_back("=== HOA DON KHAM BENH ===");
                    noiDung.push_back("Chi phi kham: " + to_string((int)phiKham));
                    noiDung.push_back("Tong gia thuoc: " + to_string((int)tongThuoc));
                    if (phiMau > 0) noiDung.push_back("Phi xet nghiem mau: 120000");
                    if (phiSieuAm > 0) noiDung.push_back("Phi sieu am: 120000");
                    if (phiNuocTieu > 0) noiDung.push_back("Phi xet nghiem nuoc tieu: 100000");
                    noiDung.push_back("VAT (5%): " + to_string((int)vat));
                    noiDung.push_back("Tong thanh toan: " + to_string((int)tongThanhToan));
                    break;
                }
            }
        }
    }
    fileIn.close();

    ofstream fileOut(fileTen, ios::trunc);
    for (const auto& dong : noiDung) {
        fileOut << dong << "\n";
    }
    fileOut.close();

    // Hiển thị
    cout << "\n===== HOA DON KHAM BENH =====\n";
    cout << "Ma benh nhi : " << maBN << "\n";
    cout << "Ma kham     : " << maKham << "\n";
    cout << "Phi kham    : " << phiKham << " VND\n";
    cout << "Thuoc       : " << tongThuoc << " VND\n";
    if (phiMau > 0) cout << "Xet nghiem mau       : 120000 VND\n";
    if (phiSieuAm > 0) cout << "Sieu am              : 120000 VND\n";
    if (phiNuocTieu > 0) cout << "Xet nghiem nuoc tieu : 100000 VND\n";
    cout << "VAT (5%)             : " << vat << " VND\n";
    cout << "Tong cong            : " << tongThanhToan << " VND\n";
}



void ToaThuoc::thongKeDoanhThuTheoQuy() {
    map<int, double> doanhThuTheoQuy; // quý -> tổng tiền
    namespace fs = std::filesystem;

    for (const auto& entry : fs::directory_iterator(".")) {
        string fileName = entry.path().filename().string();
        if (fileName.find("bn") == 0 && fileName.find(".txt") != string::npos) {
            ifstream file(entry.path());
            if (!file.is_open()) continue;

            string line;
            string ngayKham;
            bool trongHoaDon = false;
            double tongTienLanKham = 0;

            while (getline(file, line)) {
                if (line.find("Ngay kham:") != string::npos) {
                    size_t pos = line.find(":");
                    if (pos != string::npos)
                        ngayKham = line.substr(pos + 2);
                }

                if (line.find("=== HOA DON KHAM BENH ===") != string::npos) {
                    trongHoaDon = true;
                    tongTienLanKham = 0;
                    continue;
                }

                if (trongHoaDon) {
                    if (line.find("Tong thanh toan:") != string::npos) {
                        double tien = stod(line.substr(line.find(":") + 2));
                        tongTienLanKham = tien;
                        trongHoaDon = false;

                        // Phân loại theo quý
                        if (ngayKham.size() >= 10) {
                            int thang = stoi(ngayKham.substr(3, 2));
                            int quy = (thang - 1) / 3 + 1;
                            doanhThuTheoQuy[quy] += tongTienLanKham;
                        }
                    }
                }
            }

            file.close();
        }
    }

    // Hiển thị kết quả
    cout << "\n===== THONG KE DOANH THU THEO QUY =====\n";
    for (const auto& [quy, tien] : doanhThuTheoQuy) {
        cout << "Quy " << quy << ": " << fixed << setprecision(0) << tien << " VND\n";
    }
}
void ToaThuoc::xemLichSuKham(const string& maBN) {
    string fileTen = "bn" + maBN + ".txt";
    
    if (!filesystem::exists(fileTen)) {
        cout << "❌ Khong tim thay benh nhi voi ma: " << maBN << "\n";
        return;
    }

    ifstream file(fileTen);
    if (!file.is_open()) {
        cout << "❌ Khong mo duoc file benh nhi.\n";
        return;
    }

    string line;
    bool inLanKham = false;

    cout << "\n====== LICH SU KHAM BENH CUA BENH NHI [" << maBN << "] ======\n";

    while (getline(file, line)) {
        // Phát hiện bắt đầu thông tin khám bệnh
        if (line.find("=== THONG TIN KHAM BENH ===") != string::npos || 
            line.find("=== LAN KHAM MOI ===") != string::npos) {
            cout << "\n🩺 " << line << "\n";
            inLanKham = true;
            continue;
        }

        // In các dòng liên quan đến lần khám
        if (inLanKham) {
            if (line.find("--- Toa thuoc ---") != string::npos) {
                cout << " " << line << "\n";
            } else if (line.find("- Ten:") != string::npos ||
                       line.find("+ Lieu dung:") != string::npos ||
                       line.find("+ Huong dan:") != string::npos) {
                cout << "   " << line << "\n";
            } else if (line.find("Ma lich hen:") != string::npos ||
                       line.find("Khoa hen:") != string::npos ||
                       line.find("Gio hen:") != string::npos) {
                cout << " " << line << "\n";
            } else if (line.find("=== HOA DON KHAM BENH ===") != string::npos ||
                       line.find("Tong thanh toan:") != string::npos) {
                cout << " " << line << "\n";
            } else if (line.find("Ma kham:") != string::npos ||
                       line.find("Ngay kham:") != string::npos ||
                       line.find("Trieu chung:") != string::npos ||
                       line.find("Chan doan:") != string::npos) {
                cout << "🔹 " << line << "\n";
            } else if (line.find("----") != string::npos || line.empty()) {
                inLanKham = false;
            }
        }
    }

    file.close();
    cout << "======================================================\n";
}
