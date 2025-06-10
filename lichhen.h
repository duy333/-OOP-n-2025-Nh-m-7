//lichhen.h
#ifndef LICH_HEN_H
#define LICH_HEN_H

#include <string>
#include <vector>

using namespace std;

class LichHen {
private:
    string maCuocHen;      // Mã cuộc hẹn duy nhất
    string maBenhNhi;      // Mã bệnh nhi (phải kiểm tra tồn tại)
    string khoaDieuTri;    // Khoa điều trị (phải chọn từ danh sách cố định)
    string maBacSi;        // Mã bác sĩ phụ trách
    string ngayGioHen;     // Thời gian hẹn: dd/mm/yyyy HH:MM

public:
    // Constructor
    LichHen() = default;
    LichHen(const string& maCuocHen, const string& maBN, const string& khoa, const string& maBS, const string& thoiGian);

    // Getter
    string getMaCuocHen() const;
    string getMaBenhNhi() const;
    string getKhoaDieuTri() const;
    string getMaBacSi() const;
    string getNgayGioHen() const;

    // Setter
    void setMaCuocHen(const string& ma);
    void setMaBenhNhi(const string& maBN);
    void setKhoaDieuTri(const string& khoa);
    void setMaBacSi(const string& maBS);
    void setNgayGioHen(const string& ngay);

    // Method chính
    static LichHen nhapLichHen(const string& maPhuHuynhDangNhap);                         // Nhập và kiểm tra mã bệnh nhi, chọn khoa, bác sĩ, giờ
    void hienThi() const;                                 // Hiển thị thông tin
    void luuVaoFile() const;                              // Lưu vào lich<maCuocHen>.txt
    static LichHen timTheoMa(const string& maCuocHen);        // Tìm lịch theo mã
    static vector<LichHen> docTatCaLich();                // Đọc tất cả các lịch hẹn từ thư mục
    static vector<LichHen> docLichTheoBacSi(const string& maBacSi); // Lọc theo mã bác sĩ
    static vector<LichHen> docLichTheoBenhNhi(const string& maBenhNhi);
    static bool tonTaiMaHen(const string& maCuocHen);
    static void huyLichHen(const string& maCuocHen);
    static bool kiemTraTrungLich(const string& maBS, const string& gio);
    
};

#endif
