//phuhuynh.h
#ifndef PHUHUYNH_H
#define PHUHUYNH_H
#include "dkinput.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

// Khai báo trước
class BenhNhi;

class PhuHuynh {
private:
    string maPhuHuynh;
    string hoTenph ;
    string soDienThoai;
    string diaChi;
    long long canCuocCongDan;
    vector<BenhNhi*> danhSachBenhNhi;
    string taiKhoanph;
    string matKhauph;
    

public:
    PhuHuynh();
    PhuHuynh(const string& ma, const string& hoTen, const string& soDT, const string& diaChi,long long cccd);

    // Getters
    string getMaPhuHuynh() const;
    string getHoTen() const;
    string getSoDienThoai() const;
    string getDiaChi() const;
    long long getCCCD() const;


    // Setters
    void setMaPhuHuynh(const string& ma);
    void setHoTen(const string& ten);
    void setSoDienThoai(const string& sdt);
    void setDiaChi(const string& dc);
    void setCCCD(long long cccd);

    // Danh sach benh nhi
    void themBenhNhi(BenhNhi* benhNhi);
    static PhuHuynh nhapPhuHuynh();
    void luuVaoFile() const;
    // Display
    void hienThi() const;
    static bool maPhuHuynhDaTonTai(const string& ma);
};

#endif
