//menulogin.h
#ifndef LOGINMENU_H
#define LOGINMENU_H
#include "benhnhi.h"


#include <string>
#include <vector>
using namespace std;

class LoginMenu {
public:
    // Phụ huynh
    static void hienThiMenuChinh();
    static void menuPhuHuynh(); // Menu tổng phụ huynh
    static void dangKyPhuHuynh(); // Đăng ký tài khoản
    static void dangNhapPhuHuynh(); // Đăng nhập
    static void dangNhapPhuHuynhThucThi();
    static string timMaPhuHuynhTuSDT(const string& sdt);
    static vector<BenhNhi> locBenhNhiTheoMaPH(const std::string& maPH);

    // Nhân viên
    static void dangNhapNhanVienTheoLoai(const string&);
    static void taoTaiKhoanAdmin();
    static void dangNhapNhanVien(); // Menu tổng nhân viên
    static void dangNhapBacSi(); // Đăng nhập bác sĩ
    static void dangNhapLeTan(); // Đăng nhập lễ tân
    static void menuAdmin(); // Menu dành cho admin
    static void taoTaiKhoanNhanVien(bool laBacSi); // Tạo tài khoản bác sĩ/lễ tân
    static void menuPhuHuynh(const string&);
    static void menuLeTan(const string&);
    static void menuBacSi(const string&);
    static void menuQuanTriVien();
    static bool maBenhNhiDaTonTai(const string& mBN);
    static bool maPhuHuynhDaTonTai(const string& ma);
};

#endif
