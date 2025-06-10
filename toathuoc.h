//toathuoc.h
#ifndef TOATHUOC_H
#define TOATHUOC_H
#include "benhnhi.h"
#include "dkinput.h"
#include <string>
#include <vector>
using namespace std;

struct Thuoc {
    string ten;
    string lieuDung;
    string huongDan;
};

class ToaThuoc {
private:
    string maKham;
    string ngayKham;
    string trieuChung;
    string chanDoan;
    string maLichHen;
    bool daDatLichTruoc;
    vector<Thuoc> danhSachThuoc;

public:
    ToaThuoc();
    ToaThuoc(const string& maKham, const string& ngayKham, const string& trieuChung, const string& chanDoan, const vector<Thuoc>& danhSachThuoc);

    // Setters
    void setMaKham(const string& ma);
    string getMaLichHen() const;
    bool getDaDatLichTruoc() const;
    void setNgayKham(const string& ngay);
    void setTrieuChung(const string& trieu);
    void setChanDoan(const string& chuan);
    void setDanhSachThuoc(const vector<Thuoc>& ds);

    // Getters
    string getMaKham() const;
    string getNgayKham() const;
    string getTrieuChung() const;
    string getChanDoan() const;
    vector<Thuoc> getDanhSachThuoc() const;

    // Nhập và hiển thị
    static ToaThuoc nhapToaThuoc();
    void hienThi() const;

    // Mới thêm theo yêu cầu
    static void themThongTinKhamMoi(vector<BenhNhi>& danhSach);
    static void timKiemThongTinTheoMa(const string& maBN, const string& maKham,const string& maPhuHuynhDangNhap);
    static void timKiemThongTinTheoMaBS(const string& maBN, const string& maKham);
    static void tinhTongHoaDon();
    static void thongKeDoanhThuTheoQuy();
    static void xemLichSuKham(const string& maBN);


};

#endif


