//bacsi.cpp
#include "bacsi.h"
#include "dkinput.h"
#include <iostream>
#include <fstream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

BacSi::BacSi() : maBacSi(""), hoTen(""), ngaySinh(""), gioiTinh(""), khoaPhuTrach(""), cccd("") {}
BacSi::BacSi(const string& ma, const string& ten, const string& ns, const string& gt, const string& khoa, const string& cccd)
    : maBacSi(ma), hoTen(ten), ngaySinh(ns), gioiTinh(gt), khoaPhuTrach(khoa), cccd(cccd) {}

void BacSi::setMaBacSi(const string& ma) { maBacSi = ma; }
void BacSi::setHoTen(const string& ten) { hoTen = ten; }
void BacSi::setNgaySinh(const string& ns) { ngaySinh = ns; }
void BacSi::setGioiTinh(const string& gt) { gioiTinh = gt; }
void BacSi::setKhoaPhuTrach(const string& khoa) { khoaPhuTrach = khoa; }
void BacSi::setCCCD(const string& cccdMoi) { cccd = cccdMoi; }

string BacSi::getMaBacSi() const { return maBacSi; }
string BacSi::getHoTen() const { return hoTen; }
string BacSi::getNgaySinh() const { return ngaySinh; }
string BacSi::getGioiTinh() const { return gioiTinh; }
string BacSi::getKhoaPhuTrach() const { return khoaPhuTrach; }
string BacSi::getCCCD() const { return cccd; }

BacSi BacSi::nhapBacSi() {
    string ma, ten, ns, gt,cccd;
    int chonKhoa;
    string khoa = "";
    do{
        cout << "Nhap ma bac si: ";
        getline(cin, ma);
        string fileBS ="bs" + ma + ".txt";
        if (fs::exists(fileBS)) {
            cout << "Ma bac si da ton tai. Nhap ma khac.\n";
        } else break;
    } while (true);
    cout << "Nhap ho ten: ";
    getline(cin, ten);

    do {
        cout << "Nhap ngay sinh (dd/mm/yyyy): ";
        getline(cin, ns);
        if (!kiemTraNgay(ns)) cout << "Ngay sinh khong dung dinh dang!\n";
    } while (!kiemTraNgay(ns));

    do {
        cout << "Nhap gioi tinh (nam/nu): ";
        getline(cin, gt);
        if (!kiemTraGioiTinh(gt)) cout << "Gioi tinh khong dung dinh dang!\n";
    } while (!kiemTraGioiTinh(gt));

    do {
        cout << "Nhap CCCD (12 chu so): ";
        getline(cin, cccd);
        if (!kiemTraCCCD(cccd)) cout << "CCCD khong hop le!\n";
    } while (!kiemTraCCCD(cccd));

    do {
        cout << "\nChon khoa phu trach:\n";
        cout << "1. Khoa Nhi\n";
        cout << "2. Khoa Nhi so sinh\n";
        cout << "3. Khoa Tim mach Nhi\n";
        cout << "4. Khoa Than kinh Nhi\n";
        cout << "5. Khoa Di truyen - Noi tiet Nhi\n";
        cout << "6. Khoa Ho hap - Tieu hoa - Di ung Nhi\n";
        cout << "7. Khoa Dinh ky / Tu van Dinh duong Tre em\n";
        cout << "8. Khoa Tam ly Tre em / Phuc hoi chuc nang Nhi\n";
        cout << "Lua chon (1-8): ";
        cin >> chonKhoa;
        cin.ignore();
    } while (chonKhoa < 1 || chonKhoa > 8);

    switch (chonKhoa) {
        case 1: khoa = "Khoa Nhi"; break;
        case 2: khoa = "Khoa Nhi so sinh"; break;
        case 3: khoa = "Khoa Tim mach Nhi"; break;
        case 4: khoa = "Khoa Than kinh Nhi"; break;
        case 5: khoa = "Khoa Di truyen - Noi tiet Nhi"; break;
        case 6: khoa = "Khoa Ho hap - Tieu hoa - Di ung Nhi"; break;
        case 7: khoa = "Khoa Dinh ky / Tu van Dinh duong Tre em"; break;
        case 8: khoa = "Khoa Tam ly Tre em / Phuc hoi chuc nang Nhi"; break;
    }

    return BacSi(ma, ten, ns, gt, khoa,cccd);
}

void BacSi::hienThiThongTin() const {
    cout << "\n=== THONG TIN BAC SI ===\n";
    cout << "Ma bac si     : " << maBacSi << "\n";
    cout << "Ho ten        : " << hoTen << "\n";
    cout << "Ngay sinh     : " << ngaySinh << "\n";
    cout << "Gioi tinh     : " << gioiTinh << "\n";
    cout << "Khoa phu trach: " << khoaPhuTrach << "\n";
    cout << "CCCD           : " << cccd << "\n";
}

void BacSi::luuVaoFile() const {
    string tenFile = "bs" + maBacSi + ".txt";
    ofstream file(tenFile);
    if (!file.is_open()) {
        cerr << "Khong mo duoc file: " << tenFile << "\n";
        return;
    }

    file << "Ma bac si: " << maBacSi << "\n";
    file << "Ho ten: " << hoTen << "\n";
    file << "Ngay sinh: " << ngaySinh << "\n";
    file << "Gioi tinh: " << gioiTinh << "\n";
    file << "Khoa phu trach: " << khoaPhuTrach << "\n";
    file << "CCCD: " << cccd << "\n";

    file.close();
    cout << "Da luu vao file '" << tenFile << "'\n";
}

vector<BacSi> BacSi::docDanhSachTuFile(const string& folder) {
    vector<BacSi> danhSach;
    for (const auto& entry : fs::directory_iterator(folder)) {
        if (entry.is_regular_file()) {
            string path = entry.path().string();
            if (path.find("bs") != string::npos && path.find(".txt") != string::npos) {
                ifstream file(path);
                if (!file.is_open()) continue;

                string line, ma, ten, ns, gt, khoa,cccd;
                while (getline(file, line)) {
                    if (line.find("Ma bac si:") != string::npos)
                        ma = line.substr(line.find(":") + 2);
                    else if (line.find("Ho ten:") != string::npos)
                        ten = line.substr(line.find(":") + 2);
                    else if (line.find("Ngay sinh:") != string::npos)
                        ns = line.substr(line.find(":") + 2);
                    else if (line.find("Gioi tinh:") != string::npos)
                        gt = line.substr(line.find(":") + 2);
                    else if (line.find("Khoa phu trach:") != string::npos)
                        khoa = line.substr(line.find(":") + 2);
                    else if (line.find("CCCD:") != string::npos)
                        cccd = line.substr(line.find(":") + 2);
                }
                danhSach.emplace_back(ma, ten, ns, gt, khoa, cccd);

                file.close();
            }
        }
    }
    return danhSach;
}
