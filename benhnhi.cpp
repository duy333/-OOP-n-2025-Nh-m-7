//benhnhi.cpp
#include "benhnhi.h"
#include "phuhuynh.h"
#include "toathuoc.h"
#include "dkinput.h"
#include "menulogin.h"
#include <fstream>
#include <limits> // cho cin.ignore khi dùng cin >> int
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

BenhNhi::BenhNhi() : maBenhNhi(""), hoTenbn(""), ngaySinh(""), soBhyt(""), gioiTinh(""),chieucao(""),cannang(""), phuHuynh() {}

BenhNhi::BenhNhi(const string& ma, const string& ten, const string& ns, const string& bhyt, const string& gt,const string& height,const string& weight, const PhuHuynh& ph)
    : maBenhNhi(ma), hoTenbn(ten), ngaySinh(ns), soBhyt(bhyt), gioiTinh(gt),chieucao(height),cannang(weight), phuHuynh(ph) {}

bool BenhNhi::maBenhNhiDaTonTai(const string& maBN) {
    return filesystem::exists("bn" + maBN + ".txt");
}

void BenhNhi::setMaBenhNhi(const string& ma) {
    maBenhNhi = ma;
}

void BenhNhi::setHoTen(const string& ten) {
    hoTenbn = ten;
}

void BenhNhi::setNgaySinh(const string& ns) {
    ngaySinh = ns;
}

void BenhNhi::setTheBhyt(const string& bhyt) {
    soBhyt = bhyt;
}

void BenhNhi::setGioiTinh(const string& gt) {
    gioiTinh = gt;
}

void BenhNhi::setChieuCao(const string& height) {
    chieucao = height;
}

void BenhNhi::setCanNang(const string& weight) {
    cannang = weight;
}

void BenhNhi::setPhuHuynh(const PhuHuynh& ph) {
    phuHuynh = ph;
}

string BenhNhi::getMaBenhNhi() const {
    return maBenhNhi;
}

string BenhNhi::getHoTen() const {
    return hoTenbn;
}

string BenhNhi::getNgaySinh() const {
    return ngaySinh;
}
string BenhNhi::getTheBhyt() const {
    return soBhyt;
}

string BenhNhi::getGioiTinh() const {
    return gioiTinh;
}

string BenhNhi::getChieuCao() const {
    return chieucao;
}

string BenhNhi::getCanNang() const {
    return cannang;
}

PhuHuynh BenhNhi::getPhuHuynh() const {
    return phuHuynh;
}

void BenhNhi::hienThiThongTin() const {
    cout << "\n+================== THONG TIN BENH NHI ==================+\n";
    cout << "| Ma benh nhi : " << maBenhNhi << "\n";
    cout << "| Ho ten      : " << hoTenbn << "\n";
    cout << "| Ngay sinh   : " << ngaySinh << "\n";
    cout << "| The BHYT   : " << soBhyt << "\n";
    cout << "| Gioi tinh   : " << gioiTinh << "\n";
    cout << "| Chieu cao   : " << chieucao << " cm\n";
    cout << "| Can nang    : " << cannang << " kg\n";
    cout << "| Ma phu huynh    : " << phuHuynh.getMaPhuHuynh() << "\n";
    cout << "| Ten nguoi giam ho    : " << phuHuynh.getHoTen() << "\n";
    cout << "+=======================================================+\n";
}

BenhNhi BenhNhi::nhapBenhNhiCoLienKetPhuHuynh() {
    string mabn, ten, ns, bhyt, gt,heightbn,weightbn;
    string maPH, tenGiamHo;
    do{
        cout << "Nhap ma benh nhi: ";
        getline(cin, mabn);
            if (maBenhNhiDaTonTai(mabn)) {
                cout << "⚠ Ma benh nhi da ton tai. Nhap lai.\n";
            } else break;
    } while (true);

    cout << "Nhap ho ten benh nhi: ";
    getline(cin, ten);

    do {
        cout << "Nhap ngay sinh (dd/mm/yyyy): ";
        getline(cin, ns);
        if (!kiemTraNgay(ns)) cout << "Ngay sinh khong dung dinh dang!\n";
    } while (!kiemTraNgay(ns));
    
    do {
        cout << "Nhap so the BHYT: ";
        getline(cin, bhyt);
        if (!kiemTraBHYT(bhyt)) cout << "Vui long nhap so the dung dinh dang cua the BHYT(2 chu cai dau + 13 chu so)!\n";
    } while (!kiemTraBHYT(bhyt));

    do {
        cout << "Nhap gioi tinh (nam/nu): ";
        getline(cin,gt);
        if (!kiemTraGioiTinh(gt)) cout << "Gioi tinh khong dung dinh dang!\n";
    } while (!kiemTraGioiTinh(gt));

    do {
        cout << "Nhap chieu cao (cm): ";
        getline(cin, heightbn);
        if (!kiemTraSoNguyen(heightbn)) cout << "Chieu cao phai la so!\n";
    } while (!kiemTraSoNguyen(heightbn));

    do {
        cout << "Nhap can nang (kg): ";
        getline(cin, weightbn);
        if (!kiemTraSoNguyen(weightbn)) cout << "Can nang phai la so!\n";
    } while (!kiemTraSoNguyen(weightbn));

    // --- Liên kết với phụ huynh ---
    do {
        cout << "Nhap ma phu huynh (vd: 0001): ";
        getline(cin, maPH);
        string filePH = "ph" + maPH + ".txt";
        if (!filesystem::exists(filePH)) {
            cout << "Ma phu huynh khong ton tai. Vui long nhap lai!\n";
        } else break;
    } while (true);

    cout << "Nhap ten nguoi giam ho: ";
    getline(cin, tenGiamHo);

    // Tạo đối tượng PhuHuynh chỉ để lưu liên kết
    PhuHuynh ph;
    ph.setMaPhuHuynh(maPH);
    ph.setHoTen(tenGiamHo);

    return BenhNhi(mabn, ten, ns, bhyt, gt,heightbn,weightbn, ph);
}

void BenhNhi::luuVaoFile(const string& tenFile) const {
    string tenFileMoi = "bn" + maBenhNhi + ".txt";
    ofstream file(tenFileMoi, ios::app);
    if (!file.is_open()) {
        cerr << "Khong the mo file: " << tenFileMoi << endl;
        return;
    }

    file << "=== THONG TIN BENH NHI ===\n";
    file << "Ma benh nhi: " << maBenhNhi << "\n";
    file << "Ho ten: " << hoTenbn << "\n";
    file << "Ngay sinh: " << ngaySinh << "\n";
    file << "The BHYT: " << soBhyt << "\n";
    file << "Gioi tinh: " << gioiTinh << "\n";
    file << "Chieu cao: " << chieucao << "\n";
    file << "Can nang: " << cannang << "\n";

    file << "--- NGUOI GIAM HO ---\n";
    file << "Ma phu huynh: " << phuHuynh.getMaPhuHuynh() << "\n";
    file << "Ten nguoi giam ho: " << phuHuynh.getHoTen() << "\n";

    file << "---------------------------\n";
    file.close();

    cout << "Da luu vao file '" << tenFileMoi << "'\n";
}


void BenhNhi::chinhSuaBenhNhiTheoID(vector<BenhNhi>& danhSach,const string& maPhuHuynhDangNhap) {
    string maTim;
    cout << "Nhap ma benh nhi can chinh sua: ";
    getline(cin, maTim);
    for (size_t i = 0; i < danhSach.size(); ++i) {
    if (danhSach[i].getMaBenhNhi() == maTim) {
        BenhNhi& bn = danhSach[i];  // 🔧 Thêm dòng này
        if (bn.getPhuHuynh().getMaPhuHuynh() != maPhuHuynhDangNhap) {
            cout << "Bạn không có quyền sửa thông tin bệnh nhi này.\n";
            return;
        }
    if (bn.getPhuHuynh().getMaPhuHuynh() != maPhuHuynhDangNhap) {
            cout << "Bạn không có quyền sửa thông tin bệnh nhi này.\n";
            return;
        }

    for (auto& bn : danhSach) {
        if (bn.getMaBenhNhi() == maTim) {
            cout << "Da tim thay benh nhi:\n";
            bn.hienThiThongTin();

            int chon;
            do {
                cout << "\n--- MENU CHINH SUA ---\n";
                cout << "1. Ho ten\n";
                cout << "2. Ngay sinh\n";
                cout << "3. The BHYT\n";
                cout << "4. Gioi tinh\n";
                cout << "5. Chieu cao\n";
                cout << "6. Can nang\n";
                cout << "0. Luu & thoat\n";
                cout << "Lua chon: ";
                cin >> chon;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                switch (chon) {
                    case 1: {
                        string tenMoi;
                        cout << "Nhap ho ten moi: ";
                        getline(cin, tenMoi);
                        bn.setHoTen(tenMoi);
                        break;
                    }
                    case 2: {
                        string nsMoi;
                        do {
                            cout << "Nhap ngay sinh moi (dd/mm/yyyy): ";
                            getline(cin, nsMoi);
                            if (!kiemTraNgay(nsMoi)) cout << "Ngay sinh khong dung dinh dang!\n";
                        } while (!kiemTraNgay(nsMoi));
                        bn.setNgaySinh(nsMoi);
                        break;
                    }
                    case 3: {
                        string bhytMoi;
                        do {
                            cout << "Nhap so the BHYT moi (15 so): ";
                            getline(cin, bhytMoi);
                            if (!kiemTraBHYT(bhytMoi)) cout << "Vui long nhap so the dung dinh dang!\n";
                        } while (!kiemTraBHYT(bhytMoi));
                        bn.setTheBhyt(bhytMoi);
                        break;
                    }
                    case 4: {
                        string gtMoi;
                        do {
                            cout << "Nhap gioi tinh moi (nam/nu): ";
                            getline(cin,gtMoi);
                            if (!kiemTraGioiTinh(gtMoi)) cout << "Gioi tinh khong dung dinh dang!\n";
                        } while (!kiemTraGioiTinh(gtMoi));
                        bn.setGioiTinh(gtMoi);
                        break;
                    }
                    case 5: {
                        string ccMoi;
                        do {
                            cout << "Nhap chieu cao moi (cm): ";
                            getline(cin, ccMoi);
                            if (!kiemTraSoNguyen(ccMoi)) cout << "Chieu cao phai la so!\n";
                        } while (!kiemTraSoNguyen(ccMoi));
                        bn.setChieuCao(ccMoi);
                        break;
                    }
                    case 6: {
                        string cnMoi;
                        do {
                            cout << "Nhap can nang moi (kg): ";
                            getline(cin, cnMoi);
                            if (!kiemTraSoNguyen(cnMoi)) cout << "Can nang phai la so!\n";
                        } while (!kiemTraSoNguyen(cnMoi));
                        bn.setCanNang(cnMoi);
                        break;
                    }
                    case 0: {
                        // Ghi đè lại file riêng
                        string fileTen = "bn" + bn.getMaBenhNhi() + ".txt";
                        ofstream file(fileTen, ios::trunc);
                        if (file.is_open()) {
                            bn.luuVaoFile("bn" + bn.getMaBenhNhi() + ".txt");  // ✅ Ghi đè chính file bệnh nhi

                        }
                        cout << "Da luu va thoat.\n";
                        break;
                    }
                    default:
                        cout << "Lua chon khong hop le.\n";
                }
            } while (chon != 0);

            return;
        }
    }

    cout << "Khong tim thay benh nhi voi ma: " << maTim << "\n";
}
    }
}


vector<BenhNhi> BenhNhi::docDanhSachTuFile(const string& folder) {
    vector<BenhNhi> danhSach;

    for (const auto& entry : fs::directory_iterator(folder)) {
        if (entry.is_regular_file()) {
            string filePath = entry.path().string();
            if (filePath.find("bn") != string::npos && filePath.find(".txt") != string::npos) {
                ifstream file(filePath);
                if (!file.is_open()) continue;

                string line, maBN, hoTen, ns, gt,chieucaobn,cannangbn,maPH,tenPH;
                string bhyt;
                vector<Thuoc> danhSachThuoc;

                while (getline(file, line)) {
                    if (line.find("Ma benh nhi:") != string::npos) maBN = line.substr(line.find(":") + 2);
                    else if (line.find("Ho ten:") != string::npos && hoTen.empty()) hoTen = line.substr(line.find(":") + 2);
                    else if (line.find("Ngay sinh:") != string::npos) ns = line.substr(line.find(":") + 2);
                    else if (line.find("The BHYT:") != string::npos) bhyt = line.substr(line.find(":") + 2);
                    else if (line.find("Gioi tinh:") != string::npos) gt = line.substr(line.find(":") + 2);
                    else if (line.find("hieu cao:") != string::npos) chieucaobn = line.substr(line.find(":") + 2);
                    else if (line.find("Can nang:") != string::npos) cannangbn = line.substr(line.find(":") + 2);
                    else if (line.find("Ma phu huynh:") != string::npos) maPH = line.substr(line.find(":") + 2);
                    else if (line.find("Ten nguoi giam ho:") != string::npos) tenPH = line.substr(line.find(":") + 2);
                }

                // ToaThuoc toa(danhSachThuoc);
                PhuHuynh ph(maPH, tenPH, "", "", 0);
                BenhNhi bn(maBN, hoTen, ns, bhyt, gt, chieucaobn, cannangbn, ph);
                danhSach.push_back(bn);
                file.close();
            }
        }
    }

    return danhSach;
}
BenhNhi BenhNhi::timBenhNhiTheoMa(const string& maBN) {
    vector<BenhNhi> ds = docDanhSachTuFile(".");  // hoặc docTTBenhNhiTuFile nếu bạn dùng tên này
    for (const BenhNhi& bn : ds) {
        if (bn.getMaBenhNhi() == maBN) {
            return bn;
        }
    }
    return BenhNhi(); // hoặc throw nếu không tìm thấy
}

