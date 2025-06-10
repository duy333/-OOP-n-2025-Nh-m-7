//letan.cpp
#include "letan.h"
#include <iostream>
#include <fstream>
#include "dkinput.h"
#include <filesystem>
namespace fs = std::filesystem;


LeTan::LeTan() {}

LeTan::LeTan(const string& ma, const string& ten, const string& ns, const string& gt, const string& cccd)
    : maLeTan(ma), hoTen(ten), ngaySinh(ns), gioiTinh(gt), cccd(cccd) {}

void LeTan::setMaLeTan(const string& ma) { maLeTan = ma; }
void LeTan::setHoTen(const string& ten) { hoTen = ten; }
void LeTan::setNgaySinh(const string& ns) { ngaySinh = ns; }
void LeTan::setGioiTinh(const string& gt) { gioiTinh = gt; }
void LeTan::setCCCD(const string& c) { cccd = c; }

string LeTan::getMaLeTan() const { return maLeTan; }
string LeTan::getHoTen() const { return hoTen; }
string LeTan::getNgaySinh() const { return ngaySinh; }
string LeTan::getGioiTinh() const { return gioiTinh; }
string LeTan::getCCCD() const { return cccd; }

LeTan LeTan::nhapLeTan() {
    string ma, ten, ns, gt, cccd;
    do{
        cout << "Nhap ma le tan: ";
        getline(cin, ma);
        string fileLT = "lt"+ ma + ".txt";
        if (fs::exists(fileLT)) {
            cout << "Ma le tan da ton tai. Nhap ma khac.\n";
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
        if (!kiemTraGioiTinh(gt)) cout << "Gioi tinh khong hop le!\n";
    } while (!kiemTraGioiTinh(gt));

    do {
        cout << "Nhap CCCD (12 so): ";
        getline(cin, cccd);
        if (!kiemTraCCCD(cccd)) cout << "CCCD khong dung!\n";
    } while (!kiemTraCCCD(cccd));

    return LeTan(ma, ten, ns, gt, cccd);
}

void LeTan::hienThiThongTin() const {
    cout << "\n--- THONG TIN LE TAN ---\n";
    cout << "Ma le tan : " << maLeTan << "\n";
    cout << "Ho ten    : " << hoTen << "\n";
    cout << "Ngay sinh : " << ngaySinh << "\n";
    cout << "Gioi tinh : " << gioiTinh << "\n";
    cout << "CCCD      : " << cccd << "\n";
}

void LeTan::luuVaoFile() const {
    string tenFile = "lt" + maLeTan + ".txt";
    ofstream file(tenFile);
    if (!file) {
        cerr << "Khong mo duoc file de ghi.\n";
        return;
    }

    file << "Ma le tan: " << maLeTan << "\n";
    file << "Ho ten: " << hoTen << "\n";
    file << "Ngay sinh: " << ngaySinh << "\n";
    file << "Gioi tinh: " << gioiTinh << "\n";
    file << "CCCD: " << cccd << "\n";

    file.close();
}

LeTan LeTan::docTuFile(const string& maLeTan) {
    string tenFile = "lt" + maLeTan + ".txt";
    ifstream file(tenFile);
    if (!file) {
        cerr << "Khong mo duoc file: " << tenFile << "\n";
        return LeTan();
    }

    string ma, ten, ns, gt, cccd;
    string line;
    while (getline(file, line)) {
        if (line.find("Ma le tan:") != string::npos) ma = line.substr(line.find(":") + 2);
        else if (line.find("Ho ten:") != string::npos) ten = line.substr(line.find(":") + 2);
        else if (line.find("Ngay sinh:") != string::npos) ns = line.substr(line.find(":") + 2);
        else if (line.find("Gioi tinh:") != string::npos) gt = line.substr(line.find(":") + 2);
        else if (line.find("CCCD:") != string::npos) cccd = line.substr(line.find(":") + 2);
    }

    return LeTan(ma, ten, ns, gt, cccd);
}
vector<LeTan> LeTan::docDanhSachTuFile(const string& thuMuc) {
    vector<LeTan> danhSach;
    for (const auto& entry : fs::directory_iterator(thuMuc)) {
        string tenFile = entry.path().filename().string();
        if (tenFile.substr(0, 2) == "lt" && tenFile.substr(tenFile.length() - 4) == ".txt") {
            ifstream file(entry.path());
            if (file.is_open()) {
                string ma, ten, ns, gt, cccd;
                string line;
                while (getline(file, line)) {
                    if (line.find("Ma le tan:") != string::npos)
                        ma = line.substr(line.find(":") + 2);
                    else if (line.find("Ho ten:") != string::npos)
                        ten = line.substr(line.find(":") + 2);
                    else if (line.find("Ngay sinh:") != string::npos)
                        ns = line.substr(line.find(":") + 2);
                    else if (line.find("Gioi tinh:") != string::npos)
                        gt = line.substr(line.find(":") + 2);
                    else if (line.find("CCCD:") != string::npos)
                        cccd = line.substr(line.find(":") + 2);
                }
                danhSach.emplace_back(ma, ten, ns, gt, cccd);
                file.close();
            }
        }
    }
    return danhSach;
}
