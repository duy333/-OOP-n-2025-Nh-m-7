//benhnhi.h
#ifndef BENHNHI_H
#define BENHNHI_H

#include <string>
#include <vector>
#include "phuhuynh.h"
#include "toathuoc.h"
using namespace std;

class BenhNhi {
private:
    string maBenhNhi;
    string hoTenbn;
    string ngaySinh;
    string soBhyt;
    string gioiTinh;
    string chieucao;
    string cannang;
    string maPhuHuynh;
    string tenNguoiGiamHo;
    PhuHuynh phuHuynh;


public:
    BenhNhi();
    BenhNhi(const string& ma, const string& ten, const string& ns, const string& bhyt, const string& gt,
        const string& height, const string& weight, const PhuHuynh& ph);

    // Setters
    void setMaBenhNhi(const string& ma);
    void setHoTen(const string& ten);
    void setNgaySinh(const string& ns);
    void setTheBhyt (const string& bhyt);
    void setGioiTinh(const string& gt);
    void setChieuCao(const string& height);
    void setCanNang(const string& weight);
    void setPhuHuynh(const PhuHuynh& ph);

    // Getters
    string getMaBenhNhi() const;
    string getHoTen() const;
    string getNgaySinh() const;
    string getTheBhyt () const;
    string getGioiTinh() const;
    string getChieuCao() const;
    string getCanNang() const;
    PhuHuynh getPhuHuynh() const;

    // Methods
    void hienThiThongTin() const;
    static BenhNhi nhapBenhNhiCoLienKetPhuHuynh();
    void luuVaoFile(const string& tenFile) const;
    static void chinhSuaBenhNhiTheoID(vector<BenhNhi>& danhSach,const string& maPhuHuynhDangNhap);
    static vector<BenhNhi> docDanhSachTuFile(const string& tenFile = "benhnhi.txt");
    static BenhNhi timBenhNhiTheoMa(const string& maBN);
    static bool maBenhNhiDaTonTai(const string& mBN);

};

#endif
