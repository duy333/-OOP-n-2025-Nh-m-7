//lichhen.cpp
#include "lichhen.h"
#include "benhnhi.h"
#include "bacsi.h"
#include "dkinput.h"
#include "menulogin.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;
using namespace std;

LichHen::LichHen(const string& maCuocHen, const string& maBN, const string& khoa, const string& maBS, const string& thoiGian)
    : maCuocHen(maCuocHen), maBenhNhi(maBN), khoaDieuTri(khoa), maBacSi(maBS), ngayGioHen(thoiGian) {}

string LichHen::getMaCuocHen() const { return maCuocHen; }
string LichHen::getMaBenhNhi() const { return maBenhNhi; }
string LichHen::getKhoaDieuTri() const { return khoaDieuTri; }
string LichHen::getMaBacSi() const { return maBacSi; }
string LichHen::getNgayGioHen() const { return ngayGioHen; }

void LichHen::setMaCuocHen(const string& ma) { maCuocHen = ma; }
void LichHen::setMaBenhNhi(const string& maBN) { maBenhNhi = maBN; }
void LichHen::setKhoaDieuTri(const string& khoa) { khoaDieuTri = khoa; }
void LichHen::setMaBacSi(const string& maBS) { maBacSi = maBS; }
void LichHen::setNgayGioHen(const string& ngay) { ngayGioHen = ngay; }

void LichHen::hienThi() const {
    cout << "=== THONG TIN LICH HEN ===\n";
    cout << "Ma cuoc hen: " << maCuocHen << "\n";
    cout << "Ma benh nhi: " << maBenhNhi << "\n";
    cout << "Khoa dieu tri: " << khoaDieuTri << "\n";
    cout << "Ma bac si: " << maBacSi << "\n";
    cout << "Thoi gian hen: " << ngayGioHen << "\n";
}

void LichHen::luuVaoFile() const {
    string tenFile = "lich" + maCuocHen + ".txt";
    ofstream file(tenFile);
    if (!file.is_open()) {
        cerr << "Khong the mo file " << tenFile << " de ghi.\n";
        return;
    }

    file << "Ma cuoc hen: " << maCuocHen << "\n";
    file << "Ma benh nhi: " << maBenhNhi << "\n";
    file << "Khoa dieu tri: " << khoaDieuTri << "\n";
    file << "Ma bac si: " << maBacSi << "\n";
    file << "Thoi gian hen: " << ngayGioHen << "\n";

    file.close();
    cout << "Da luu thong tin lich hen vao " << tenFile << "\n";
}

LichHen LichHen::nhapLichHen(const string& maPhuHuynhDangNhap) {
    string maCuocHen, maBN, khoa, ngayGio, maBS;
    vector<string> dsKhoa = {
        "Khoa Nhi",
        "Khoa Nhi so sinh",
        "Khoa Tim mach Nhi",
        "Khoa Than kinh Nhi",
        "Khoa Di truyen - Noi tiet Nhi",
        "Khoa Ho hap - Tieu hoa - Di ung Nhi",
        "Khoa Kham dinh ky / Tu van dinh duong Tre em",
        "Khoa Tam ly Tre em / Phuc hoi chuc nang Nhi"
    };

    cout << "Nhap ma cuoc hen: ";
    getline(cin, maCuocHen);

    do {
        cout << "Nhap ma benh nhi: ";
        getline(cin, maBN);
        string fileBN = "bn" + maBN + ".txt";
        BenhNhi bn = BenhNhi::timBenhNhiTheoMa(maBN);
        if (bn.getPhuHuynh().getMaPhuHuynh() != maPhuHuynhDangNhap) {
            cout << "❌ Ban khong co quyen dat lich cho benh nhi nay!\nVui long chon benh nhi trong danh sach cua ban!";
            return LichHen();  // trả về rỗng
        } else break;
        if (!fs::exists(fileBN)) {
            cout << "❌ Ma benh nhi khong ton tai. Vui long nhap lai.\n";
        } else break;
    } while (true);

    cout << "--- Chon khoa dieu tri ---\n";
    for (int i = 0; i < dsKhoa.size(); ++i) {
        cout << i + 1 << ". " << dsKhoa[i] << "\n";
    }

    int chon;
    do {
        cout << "Lua chon (1-" << dsKhoa.size() << "): ";
        cin >> chon;
        cin.ignore();
        if (chon < 1 || chon > dsKhoa.size()) {
            cout << "Lua chon khong hop le. Nhap lai.\n";
        }
    } while (chon < 1 || chon > dsKhoa.size());
    khoa = dsKhoa[chon - 1];

    // Chọn bác sĩ theo khoa
    vector<BacSi> dsBS = BacSi::docDanhSachTuFile(".");
    vector<string> bacSiPhuTrach;

    cout << "--- Danh sach bac si phu trach khoa " << khoa << " ---\n";
    for (const auto& bs : dsBS) {
        if (bs.getKhoaPhuTrach() == khoa) {
            cout << "Ma BS: " << bs.getMaBacSi() << ", Ho ten: " << bs.getHoTen() << "\n";
            bacSiPhuTrach.push_back(bs.getMaBacSi());

        }
    }

    if (bacSiPhuTrach.empty()) {
        cout << "⚠ Khong co bac si phu trach khoa nay. Hay them bac si truoc.\n";
        return LichHen();
    }

    do {
        cout << "Nhap ma bac si muon chon: ";
        getline(cin, maBS);
        if (find(bacSiPhuTrach.begin(), bacSiPhuTrach.end(), maBS) == bacSiPhuTrach.end()) {
            cout << "❌ Ma bac si khong dung. Nhap lai.\n";
        } else break;
    } while (true);

do {
    cout << "Nhap thoi gian hen (dd/mm/yyyy hh:mm): ";
        getline(cin, ngayGio);
        if (!kiemTraNgayGio(ngayGio)) {
            cout << "❌ Dinh dang ngay gio khong hop le. Vui long nhap lai.\n";
        }
    } while (!kiemTraNgayGio(ngayGio));

    // Check lịch trùng của bệnh nhi
    for (const auto& entry : fs::directory_iterator(".")) {
        if (entry.path().string().find("lich") != string::npos) {
            ifstream file(entry.path());
            if (!file.is_open()) continue;

            string line, maBNtemp, gioTemp;
            while (getline(file, line)) {
                if (line.find("Ma benh nhi:") != string::npos) maBNtemp = line.substr(line.find(":") + 2);
                else if (line.find("Thoi gian hen:") != string::npos) gioTemp = line.substr(line.find(":") + 2);
            }
            if (maBNtemp == maBN && gioTemp == ngayGio) {
                cout << "⚠ Benh nhi da co lich hen vao thoi gian nay. Vui long chon thoi gian khac.\n";
                return LichHen();
            }
        }
    }

    // Check lịch trùng của bác sĩ
    if (kiemTraTrungLich(maBS, ngayGio)) {
        cout << "⚠ Bac si da co lich hen vao thoi gian nay. Vui long chon bac si khac hoac thoi gian khac.\n";
        return LichHen();
    }

    return LichHen(maCuocHen, maBN, khoa, maBS, ngayGio);
}

LichHen LichHen::timTheoMa(const string& maCuocHen) {
    string tenFile = "lich" + maCuocHen + ".txt";
    ifstream file(tenFile);
    if (!file.is_open()) {
        cerr << "❌ Khong tim thay lich hen voi ma: " << maCuocHen << "\n";
        return LichHen();
    }

    string line, maBN, khoa, maBS, time;
    while (getline(file, line)) {
        if (line.find("Ma benh nhi:") != string::npos) maBN = line.substr(line.find(":") + 2);
        else if (line.find("Khoa dieu tri:") != string::npos) khoa = line.substr(line.find(":") + 2);
        else if (line.find("Ma bac si:") != string::npos) maBS = line.substr(line.find(":") + 2);
        else if (line.find("Thoi gian hen:") != string::npos) time = line.substr(line.find(":") + 2);
    }
    file.close();
    return LichHen(maCuocHen, maBN, khoa, maBS, time);
}

vector<LichHen> LichHen::docTatCaLich() {
    vector<LichHen> ds;
    for (const auto& file : fs::directory_iterator(".")) {
        string ten = file.path().filename().string();
        if (ten.rfind("lich", 0) == 0 && ten.find(".txt") != string::npos) {
            string maCuocHen = ten.substr(4, ten.size() - 8); // "lichXXXX.txt"
            ds.push_back(timTheoMa(maCuocHen));
        }
    }
    return ds;
}

vector<LichHen> LichHen::docLichTheoBacSi(const string& maBacSi) {
    vector<LichHen> all = docTatCaLich();
    vector<LichHen> ketQua;
    for (const auto& lh : all) {
        if (lh.getMaBacSi() == maBacSi) {
            ketQua.push_back(lh);
        }
    }
    return ketQua;
}

vector<LichHen> LichHen::docLichTheoBenhNhi(const string& maBenhNhi) {
    vector<LichHen> danhSach;
    for (const auto& entry : fs::directory_iterator(".")) {
        if (entry.is_regular_file()) {
            string path = entry.path().string();
            if (path.find("lich") != string::npos && path.find(".txt") != string::npos) {
                ifstream file(path);
                if (!file.is_open()) continue;

                string line, ma, khoa, maBS, time;
                while (getline(file, line)) {
                    if (line.find("Ma benh nhi:") != string::npos)
                        ma = line.substr(line.find(":") + 2);
                    else if (line.find("Khoa dieu tri:") != string::npos)
                        khoa = line.substr(line.find(":") + 2);
                    else if (line.find("Ma bac si:") != string::npos)
                        maBS = line.substr(line.find(":") + 2);
                    else if (line.find("Thoi gian hen:") != string::npos)
                        time = line.substr(line.find(":") + 2);
                }

                if (ma == maBenhNhi) {
                    string tenFile = entry.path().filename().string();
                    string maLich = tenFile.substr(4, tenFile.size() - 8); // remove "lich" and ".txt"
                    danhSach.emplace_back(maLich, ma, khoa, maBS, time);
                }

                file.close();
            }
        }
    }

    return danhSach;
}


bool LichHen::kiemTraTrungLich(const string& maBS, const string& gio) {
    for (const auto& entry : fs::directory_iterator(".")) {
        if (entry.path().string().find("lich") != string::npos) {
            ifstream file(entry.path());
            if (!file.is_open()) continue;

            string line;
            string bs, gioDat;
            while (getline(file, line)) {
                if (line.find("Ma bac si:") != string::npos)
                    bs = line.substr(line.find(":") + 2);
                else if (line.find("Thoi gian hen:") != string::npos)
                    gioDat = line.substr(line.find(":") + 2);
            }

            if (bs == maBS && gioDat == gio)
                return true;
        }
    }
    return false;
}


bool LichHen::tonTaiMaHen(const string& maCuocHen) {
    string fileName = "lich" + maCuocHen + ".txt";
    return fs::exists(fileName);
}

void LichHen::huyLichHen(const string& maCuocHen) {
    string fileName = "lich" + maCuocHen + ".txt";
    if (fs::exists(fileName)) {
        fs::remove(fileName);
        cout << "🗑 Da huy lich hen: " << maCuocHen << "\n";
    } else {
        cout << "⚠ Ma lich hen khong ton tai.\n";
    }
}