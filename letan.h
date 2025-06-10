//letan.h
#ifndef LETAN_H
#define LETAN_H
#include <vector>
#include <string>
using namespace std;

class LeTan {
private:
    string maLeTan;
    string hoTen;
    string ngaySinh;
    string gioiTinh;
    string cccd;

public:
    LeTan();
    LeTan(const string& ma, const string& ten, const string& ns, const string& gt, const string& cccd);

    // Setters
    void setMaLeTan(const string& ma);
    void setHoTen(const string& ten);
    void setNgaySinh(const string& ns);
    void setGioiTinh(const string& gt);
    void setCCCD(const string& cccd);

    // Getters
    string getMaLeTan() const;
    string getHoTen() const;
    string getNgaySinh() const;
    string getGioiTinh() const;
    string getCCCD() const;

    // Functions
    static LeTan nhapLeTan();
    void hienThiThongTin() const;
    void luuVaoFile() const;
    static LeTan docTuFile(const string& maLeTan);
    static vector<LeTan> docDanhSachTuFile(const string& thuMuc = ".");

};

#endif
