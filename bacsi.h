//bacsi.h
#ifndef BACSI_H
#define BACSI_H

#include <string>
#include <vector>
using namespace std;

class BacSi {
private:
    string maBacSi;
    string hoTen;
    string ngaySinh;
    string gioiTinh;
    string khoaPhuTrach;
    string cccd;

public:
    BacSi();
    BacSi(const string& ma, const string& ten, const string& ns, const string& gt, const string& khoa,const string& cccd);

    // Setters
    void setMaBacSi(const string& ma);
    void setHoTen(const string& ten);
    void setNgaySinh(const string& ns);
    void setGioiTinh(const string& gt);
    void setKhoaPhuTrach(const string& khoa);
    void setCCCD(const string& cccd);

    // Getters
    string getMaBacSi() const;
    string getHoTen() const;
    string getNgaySinh() const;
    string getGioiTinh() const;
    string getKhoaPhuTrach() const;
    string getCCCD() const; 

    // Functional methods
    static BacSi nhapBacSi();
    void hienThiThongTin() const;
    void luuVaoFile() const;
    static vector<BacSi> docDanhSachTuFile(const string& folder = ".");
};

#endif
