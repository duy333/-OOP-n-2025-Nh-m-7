//phuhuynh.cpp
#include "phuhuynh.h"
#include "dkinput.h"
#include "benhnhi.h"
#include <filesystem>
#include <fstream>
PhuHuynh::PhuHuynh() : maPhuHuynh(""), hoTenph(""), soDienThoai(""), diaChi(""), canCuocCongDan(0){}

PhuHuynh::PhuHuynh(const string& ma,const string& hoTen, const string& soDT, const string& diaChi, long long cccd)
    : maPhuHuynh(ma),hoTenph(hoTen), soDienThoai(soDT), diaChi(diaChi), canCuocCongDan(cccd) {}

bool PhuHuynh::maPhuHuynhDaTonTai(const string& ma) {
    return filesystem::exists("ph" + ma + ".txt");
}

string PhuHuynh::getMaPhuHuynh() const { 
    return maPhuHuynh; 
}

string PhuHuynh::getHoTen() const {
    return hoTenph;
}

string PhuHuynh::getSoDienThoai() const {
    return soDienThoai;
}

string PhuHuynh::getDiaChi() const {
    return diaChi;
}

long long PhuHuynh::getCCCD() const {
    return canCuocCongDan;
}

void PhuHuynh::setMaPhuHuynh(const string& ma) { 
    maPhuHuynh = ma; 
}

void PhuHuynh::setHoTen(const string& ten) {
    hoTenph = ten;
}

void PhuHuynh::setCCCD(long long cccd) {
    canCuocCongDan = cccd;
}

void PhuHuynh::setSoDienThoai(const string& sdt) {
    soDienThoai = sdt;
}

void PhuHuynh::setDiaChi(const string& dc) {
    diaChi = dc;
}

void PhuHuynh::themBenhNhi(BenhNhi* benhNhi) {
    danhSachBenhNhi.push_back(benhNhi);
}

PhuHuynh PhuHuynh::nhapPhuHuynh() {
    string ma, ten, sdt, dc,cccd_string;
    long long cccd;
    do{
    cout << "Nhap ma phu huynh: ";
    getline(cin, ma);
        if (maPhuHuynhDaTonTai(ma)) {
        cout << "⚠ Ma phu huynh da ton tai. Nhap lai.\n";
        } else break;
    } while (true);    

     cout << "--- Nhap thong tin phu huynh ---\n";
    cout << "Ho ten phu huynh: ";
    getline(cin, ten);

    do {
        cout << "Nhap so dien thoai: ";
        getline(cin,sdt);
        if (!kiemTraSDT(sdt)) cout << "So dien thoai khong ton tai!\n";
    } while (!kiemTraSDT(sdt));
    
    cout << "Dia chi: ";
    getline(cin, dc);

    do {
        cout << "Nhap CCCD (12 so): ";
        getline(cin,cccd_string);
        if (!kiemTraCCCD(cccd_string)) cout << "CCCD khong dung dinh dang!\n";
    } while (!kiemTraCCCD(cccd_string));
    cccd=stoll(cccd_string);
    PhuHuynh ph(ma, ten, sdt, dc, cccd);
    ph.luuVaoFile();
    return ph;
}

void PhuHuynh::luuVaoFile() const {
    string tenFile = "ph" + maPhuHuynh + ".txt";
    ofstream file(tenFile);
    if (file.is_open()) {
        file << "\n========== THONG TIN PHU HUYNH ==========\n"<<"\n";
        file << "Ma phu huynh: " << maPhuHuynh << "\n";
        file << "Ho ten: " << hoTenph << "\n";
        file << "So dien thoai: " << soDienThoai << "\n";
        file << "Dia chi: " << diaChi << "\n";
        file << "CCCD: " << canCuocCongDan << "\n";
        file.close();
        cout << "Da luu thong tin vao file '" << tenFile << "'\n";
    } else {
        cerr << "Khong the mo file de ghi: " << tenFile << "\n";
    }
}


void PhuHuynh::hienThi() const {
    cout << "\n========== THONG TIN PHU HUYNH ==========\n";
    cout << "Ma phu huynh: " << maPhuHuynh << endl;
    cout << "Ho ten phu huynh: " << hoTenph << endl;
    cout << "So dien thoai: " << soDienThoai << endl;
    cout << "Dia chi: " << diaChi << endl;
    cout << "CCCD: " << canCuocCongDan << endl;
    cout << "Tai khoan: " << taiKhoanph << "\n";

    cout << "--- Danh sach benh nhi cua phu huynh ---" << endl;
    if (danhSachBenhNhi.empty()) {
        cout << "(Khong co benh nhi nao)\n";
    } else {
        for (const auto& bn : danhSachBenhNhi) {
            cout << "-----------------------------" << endl;
            bn->hienThiThongTin();
        }
    }
}
