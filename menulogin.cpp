//menulogin.cpp
#include "menulogin.h"
#include "dkinput.h"
#include "phuhuynh.h"
#include "bacsi.h"
#include "letan.h"
#include "benhnhi.h"
#include "toathuoc.h"
#include "lichhen.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

bool LoginMenu::maBenhNhiDaTonTai(const string& maBN) {
    return filesystem::exists("bn" + maBN + ".txt");
}

bool LoginMenu::maPhuHuynhDaTonTai(const string& ma) {
    return filesystem::exists("ph" + ma + ".txt");
}

void LoginMenu::hienThiMenuChinh() {
    int luaChon;
    do {
        cout << "\n===== DANG NHAP =====\n";
        cout << "1. Dang nhap voi tu cach Phu huynh\n";
        cout << "2. Dang nhap voi tu cach Nhan vien\n";
        cout << "0. Thoat\n";
        cout << "Lua chon: ";
        cin >> luaChon;
        cin.ignore();
        switch (luaChon) {
            case 1:
                dangNhapPhuHuynh();
                break;
            case 2:
                dangNhapNhanVien();
                break;
            case 0:
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while (luaChon != 0);
}

void LoginMenu::dangNhapPhuHuynh() {
    int chon;
    do {
        cout << "\n--- PHU HUYNH ---\n";
        cout << "1. Dang nhap\n";
        cout << "2. Chua co tai khoan? Dang ky tai day!\n";
        cout << "0. Quay lai\n";
        cout << "Lua chon: ";
        cin >> chon;
        cin.ignore();
        switch (chon) {
            case 1:
                dangNhapPhuHuynhThucThi();
                break;
            case 2:
                dangKyPhuHuynh();
                break;
            case 0:
                return;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while (chon != 0);
}

void LoginMenu::dangKyPhuHuynh() {
    string sdt, matkhau, xacnhan;
    do {
        cout << "Nhap so dien thoai: ";
        getline(cin, sdt);
        if (!kiemTraSDT(sdt)) cout << "So dien thoai khong hop le!\n";
    } while (!kiemTraSDT(sdt));

    ifstream check("ph_" + sdt + ".txt");
    if (check.is_open()) {
        cout << "So dien thoai da duoc dang ky!\n";
        return;
    }

    do {
        cout << "Nhap mat khau (Toi da 8 ky tu, co it nhat 1 chu hoa, 1 chu so, 1 ky tu dac biet): ";
        getline(cin, matkhau);
        if (!kiemTraMatKhau(matkhau)) {
            cout << "Mat khau khong hop le! Yeu cau:\n";
            cout << "- Toi da 8 ky tu\n- Co it nhat 1 chu hoa\n- 1 chu so\n- 1 ky tu dac biet\n";
        }
    } while (!kiemTraMatKhau(matkhau));

    do {
        cout << "Nhap lai mat khau: ";
        getline(cin, xacnhan);
        if (xacnhan != matkhau) cout << "Mat khau khong khop!\n";
    } while (xacnhan != matkhau);

    ofstream out("ph_" + sdt + ".txt");
    out << sdt << "\n" << matkhau << "\n";
    out.close();

    cout << "Dang ky thanh cong. Moi ban nhap thong tin phu huynh:\n";
    PhuHuynh ph = PhuHuynh::nhapPhuHuynh();
    ph.setSoDienThoai(sdt);
    ph.luuVaoFile();
}

void LoginMenu::dangNhapPhuHuynhThucThi() {
    string sdt, matkhau, captcha;
    do {
        cout << "Nhap so dien thoai: ";
        getline(cin, sdt);
        if (!kiemTraSDT(sdt)) cout << "So dien thoai khong hop le!\n";
    } while (!kiemTraSDT(sdt));

    ifstream in("ph_" + sdt + ".txt");
    if (!in.is_open()) {
        cout << "Khong tim thay tai khoan!\n";
        return;
    }

    string sdtDoc, matkhauDoc;
    getline(in, sdtDoc);
    getline(in, matkhauDoc);
    in.close();

    cout << "Nhap mat khau: ";
    getline(cin, matkhau);

    if (matkhau != matkhauDoc) {
        cout << "Sai mat khau!\n";
        return;
    }

    // Sinh captcha
    srand(time(0));
    string captchaSinh;
    for (int i = 0; i < 5; ++i) {
        captchaSinh += 'A' + rand() % 26;
    }

    cout << "Captcha: " << captchaSinh << "\nNhap lai captcha: ";
    getline(cin, captcha);

    if (captcha != captchaSinh) {
        cout << "Captcha sai!\n";
        return;
    }

    cout << "Dang nhap thanh cong! (Phu huynh)\n";
    LoginMenu lm;
    lm.menuPhuHuynh(sdt);
}

void LoginMenu::dangNhapNhanVien() {
    int chon;
    do {
        cout << "\n--- NHAN VIEN ---\n";
        cout << "1. Dang nhap voi vai tro Bac si\n";
        cout << "2. Dang nhap voi vai tro Le tan\n";
        cout << "0. Quay lai\n";
        cout << "Lua chon: ";
        cin >> chon;
        cin.ignore();
        switch (chon) {
            case 1:
                dangNhapNhanVienTheoLoai("bs");
                break;
            case 2:
                dangNhapNhanVienTheoLoai("lt");
                break;
            case 666:
                taoTaiKhoanAdmin();
                break;
            case 0:
                return;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while (chon != 0);
}

void LoginMenu::dangNhapNhanVienTheoLoai(const string& loai) {
    string ma, mk;
    cout << "Nhap ma " << (loai == "bs" ? "bac si" : "le tan") << ": ";
    getline(cin, ma);
    cout << "Nhap mat khau: ";
    getline(cin, mk);
    string fileTen = (loai == "bs" ? "tkbs" : "tklt") + ma + ".txt";
    ifstream file(fileTen);
    string line, username, password;
    if (file.is_open()) {
        getline(file, line);
        if (line.find("Username: ") != string::npos)
            username = line.substr(line.find(":") + 2);

        getline(file, line);
        if (line.find("Password: ") != string::npos)
            password = line.substr(line.find(":") + 2);

        file.close();
        if (username == ma && password == mk) {
            cout << "✅ Dang nhap thanh cong!\n";
            if (loai == "bs") menuBacSi(ma);
            else if (loai == "lt") menuLeTan(ma);
        } else {
            cout << "❌ Ten dang nhap hoac mat khau sai.\n";
        }
    } else {
        cout << "❌ Khong tim thay tai khoan.\n";
    }
}


void LoginMenu::taoTaiKhoanAdmin() {
    string loai, ma, mk;
       string username, password;
    cout << "Nhap ten dang nhap admin: ";
    getline(cin, username);
    cout << "Nhap mat khau: ";
    getline(cin, password);

    // Ví dụ đơn giản: hardcoded
    if (username == "admin" && password == "admin123") {
        cout << "Dang nhap thanh cong voi quyen Quan tri vien.\n";
        menuQuanTriVien();
    } 
    else {
        cout << "Thong tin dang nhap sai!\n";
    }
}

string LoginMenu::timMaPhuHuynhTuSDT(const string& sdt) {
    namespace fs = std::filesystem;
    for (const auto& entry : fs::directory_iterator(".")) {
        if (entry.path().string().find("ph") != string::npos) {
            ifstream file(entry.path());
            string line, maPH, soDT;
            while (getline(file, line)) {
                if (line.find("Ma phu huynh:") != string::npos)
                    maPH = line.substr(line.find(":") + 2);
                else if (line.find("So dien thoai:") != string::npos)
                    soDT = line.substr(line.find(":") + 2);
            }
            if (soDT == sdt) return maPH;
        }
    }
    return "";
}

vector<BenhNhi> LoginMenu::locBenhNhiTheoMaPH(const string& maPH) {
    vector<BenhNhi> tatCa = BenhNhi::docDanhSachTuFile(".");
    vector<BenhNhi> ketQua;
    for (const auto& bn : tatCa) {
        if (bn.getPhuHuynh().getMaPhuHuynh() == maPH) {
            ketQua.push_back(bn);
        }
    }
    return ketQua;
}
void LoginMenu::menuPhuHuynh(const string& sdt) {
    string maPH = timMaPhuHuynhTuSDT(sdt);
    string maPhuHuynhDangNhap = maPH;
    if (maPH.empty()) {
        cout << "Không tìm thấy mã phụ huynh từ số điện thoại!\n";
        return;
    }

    while (true) {
        cout << "\n--- MENU PHU HUYNH ---\n";
        cout << "1. Dang ky ho so benh nhi moi\n";
        cout << "2. Dat lich kham cho tre\n";
        cout << "3. Cap nhat thong tin benh nhi theo ma\n";
        cout << "4. Xem ket qua kham va toa thuoc\n";
        cout << "0. Dang xuat\n";
        cout << "Chon chuc nang: ";
        int chon;
        cin >> chon;
        cin.ignore();

        vector<BenhNhi> danhSachBN = locBenhNhiTheoMaPH(maPH);

        switch (chon) {
            case 1: {
                BenhNhi bn = BenhNhi::nhapBenhNhiCoLienKetPhuHuynh();
                danhSachBN.push_back(bn);
                bn.luuVaoFile("");
                break;
            }
            case 2: {
                if (danhSachBN.empty()) {
                    cout << "Ban chua co benh nhi nao.\n";
                } else {
                    cout << "Danh sach benh nhi cua ban:\n";
                    for (const auto& bn : danhSachBN) {
                        cout << "- " << bn.getMaBenhNhi() << " | " << bn.getHoTen() << "\n";
                    }
                    // LichHen::nhapLichHen(maPhuHuynhDangNhap);
                    LichHen lh = LichHen::nhapLichHen(maPhuHuynhDangNhap);
                    if (!lh.getMaCuocHen().empty()) {
                        lh.luuVaoFile();
                    }
                    break;
                }
            }
            case 3: {
                if (danhSachBN.empty()) {
                    cout << "Ban chua co benh nhi nao.\n";
                } else {
                    cout << "Danh sach benh nhi cua ban:\n";
                    for (const auto& bn : danhSachBN) {
                        cout << "- " << bn.getMaBenhNhi() << " | " << bn.getHoTen() << "\n";
                    }
                    BenhNhi::chinhSuaBenhNhiTheoID(danhSachBN,maPhuHuynhDangNhap);
                }
                break;
            }
            case 4: {
                if (danhSachBN.empty()) {
                    cout << "Ban chua co benh nhi nao.\n";
                } else {
                    cout << "Danh sach benh nhi cua ban:\n";
                    for (const auto& bn : danhSachBN) {
                        cout << "- " << bn.getMaBenhNhi() << " | " << bn.getHoTen() << "\n";
                    }
                    string maBN;
                    cout << "Nhap ma benh nhi can xem: ";
                    getline(cin, maBN);
                    bool hopLe = false;
                    for (const auto& bn : danhSachBN) {
                        if (bn.getMaBenhNhi() == maBN) {
                            hopLe = true;
                            break;
                        }
                    }
                    if (!hopLe) {
                        cout << "Ma benh nhi khong thuoc quyen quan ly cua ban.\n";
                        break;
                    }
                    string maKham;
                    cout << "Nhap ma kham can xem: ";
                    getline(cin, maKham);
                    ToaThuoc::timKiemThongTinTheoMa(maBN, maKham,maPhuHuynhDangNhap);
                }
                break;
            }
            case 0:
                return;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    }
}

void LoginMenu::menuLeTan(const string& maLeTan) {
    int choice;
    do {
        cout << "\n===== MENU LE TAN =====\n";
        cout << "1. Xem lich hen cua benh nhi\n";
        cout << "2. Xem lich hen cua bac si\n";
        cout << "3. Tinh toan va luu hoa don cho lan kham\n";
        cout << "0. Dang xuat\n";
        cout << "Chon chuc nang: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
            string maBN;
            cout << "Nhap ma benh nhi: ";
            getline(cin, maBN);

            if (!filesystem::exists("bn" + maBN + ".txt")) {
                cout << "⚠ Ma benh nhi khong ton tai.\n";
                break;
            }

            vector<LichHen> danhSach = LichHen::docLichTheoBenhNhi(maBN);
            if (danhSach.empty()) {
                cout << "⚠ Benh nhi khong co lich hen nao.\n";
            } else {
                cout << "\n=== Danh sach lich hen cua benh nhi " << maBN << " ===\n";
                for (const auto& lh : danhSach) {
                    lh.hienThi();
                    cout << "----------------------\n";
                }
            }

            break;
            }

            case 2: {
                string maBS;
                cout << "Nhap ma bac si: ";
                getline(cin, maBS);
                 if (!filesystem::exists("bs" + maBS + ".txt")) {
                cout << "⚠ Ma benh nhi khong ton tai.\n";
                break;
                }
                vector<LichHen> lich = LichHen::docLichTheoBacSi(maBS);
                if (lich.empty()) {
                    cout << "⚠ Khong co lich hen nao cho bac si nay.\n";
                } else {
                    for (const auto& lh : lich) {
                        lh.hienThi();
                    }
                }
                break;
            }
            case 3: {
                ToaThuoc::tinhTongHoaDon();
                break;
            }
            case 0:
                cout << "Dang xuat thanh cong.\n";
                break;
            default:
                cout << "Lua chon khong hop le. Vui long thu lai.\n";
        }
} while (choice != 0);
}
void LoginMenu::menuBacSi(const string& maBacSi) {
    int choice;
    do {
        cout << "\n===== MENU BAC SI =====\n";
        cout << "1. Xem danh sach benh nhi theo lich hen\n";
        cout << "2. Kham va chan doan benh (Them thong tin kham moi)\n";
        cout << "3. In toa thuoc\n";
        cout << "4. Quan ly lich su benh an theo benh nhi\n";
        cout << "0. Dang xuat\n";
        cout << "Chon chuc nang: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string maBS=maBacSi;
                vector<LichHen> lich = LichHen::docLichTheoBacSi(maBS);
                if (lich.empty()) {
                    cout << "⚠ Khong co lich hen nao cho bac si nay.\n";
                } else {
                    for (const auto& lh : lich) {
                        lh.hienThi();
                    }
                }
                break;
            }
            case 2: {
                vector<BenhNhi> danhSachBN = BenhNhi::docDanhSachTuFile(".");
                ToaThuoc::themThongTinKhamMoi(danhSachBN);
                break;
            }
            case 3: {
                cout << "=== Chuc nang in toa thuoc ===\n";
                string maBN, maKham;
                cout << "Nhap ma benh nhi: ";
                getline(cin, maBN);
                cout << "Nhap ma kham: ";
                getline(cin, maKham);
                ToaThuoc::timKiemThongTinTheoMaBS(maBN, maKham);
                break;
            }
            case 4: {
                cout << "=== Quan ly lich su benh an ===\n";
                string maBN;
                cout << "Nhap ma benh nhi: ";
                getline(cin, maBN);
                ToaThuoc::xemLichSuKham(maBN); // yêu cầu hàm này đã có trong ToaThuoc
                break;
            }
            case 0:
                cout << "Dang xuat thanh cong.\n";
                break;
            default:
                cout << "Lua chon khong hop le. Vui long thu lai.\n";
        }

    } while (choice != 0);
}
void LoginMenu::menuQuanTriVien() {
    int choice;
    do {
        cout << "\n===== MENU QUAN TRI VIEN =====\n";
        cout << "1. Tao tai khoan bac si\n";
        cout << "2. Tao tai khoan le tan\n";
        cout << "3. Quan ly thong tin bac si\n";
        cout << "4. Quan ly thong tin le tan\n";
        cout << "5. Thong ke luong kham / doanh thu theo quy\n";
        cout << "0. Dang xuat\n";
        cout << "Chon chuc nang: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string maBS;
                do {
                    cout << "Nhap ma bac si (VD: bs0001): ";
                    getline(cin, maBS);
                    string fileBS ="bs" + maBS + ".txt";
                    if (fs::exists(fileBS)) {
                        cout << "Ma bac si da ton tai. Nhap ma khac.\n";
                    } else break;
                } while (true);

                string matKhau;
                do {
                    cout << "Nhap mat khau: ";
                    getline(cin, matKhau);
                    if (!kiemTraMatKhau(matKhau)) {
                        cout << "Mat khau khong hop le!\n";
                        cout << "(Toi da 8 ky tu, co it nhat 1 chu hoa, 1 chu so, 1 ky tu dac biet)\n";
                    }
                } while (!kiemTraMatKhau(matKhau));

                ofstream out("tkbs" + maBS + ".txt");
                if (out.is_open()) {
                    out << "Username: " << maBS << "\n";
                    out << "Password: " << matKhau << "\n"; // Lưu mật khẩu vào file
                    out.close();
                }


                BacSi bs = BacSi::nhapBacSi();
                bs.luuVaoFile();
                break;
            }
            case 2: {
                string maLT;
                do {
                    cout << "Nhap ma le tan (VD: lt0001): ";
                    getline(cin, maLT);
                    string fileLT = "lt"+ maLT + ".txt";
                    if (fs::exists(fileLT)) {
                        cout << "Ma le tan da ton tai. Nhap ma khac.\n";
                    } else break;
                } while (true);

                string matKhau;
                do {
                    cout << "Nhap mat khau: ";
                    getline(cin, matKhau);
                    if (!kiemTraMatKhau(matKhau)) {
                        cout << "Mat khau khong hop le!\n";
                        cout << "(Toi da 8 ky tu, co it nhat 1 chu hoa, 1 chu so, 1 ky tu dac biet)\n";
                    }
                } while (!kiemTraMatKhau(matKhau));

                ofstream out("tklt" + maLT + ".txt");
                if (out.is_open()) {
                    out << "Username: " << maLT << "\n";
                    out << "Password: " << matKhau << "\n";
                    out.close();
                }

                LeTan lt = LeTan::nhapLeTan();
                lt.luuVaoFile();
                break;
            }
            case 3: {
                cout << "=== Danh sach bac si ===\n";
                vector<BacSi> dsBS = BacSi::docDanhSachTuFile(".");
                for (const auto& bs : dsBS) {
                    bs.hienThiThongTin();
                    cout << "------------------------\n";
                }
                break;
            }
            case 4: {
                cout << "=== Danh sach le tan ===\n";
                vector<LeTan> dsLT = LeTan::docDanhSachTuFile(".");
                for (const auto& lt : dsLT) {
                    lt.hienThiThongTin();
                    cout << "------------------------\n";
                }
                break;
            }
            case 5: {
                cout << "=== Thong ke doanh thu ===\n";
                ToaThuoc::thongKeDoanhThuTheoQuy();  // Đảm bảo hàm này tồn tại trong toathuoc
                break;
            }
            case 0:
                cout << "Dang xuat thanh cong.\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }

    } while (choice != 0);
}