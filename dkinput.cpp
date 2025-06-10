//dkinput.cpp
#include "dkinput.h"
#include <regex>
#include <algorithm>
#include <cctype>

bool kiemTraNgay(const string& ngay) {
    return regex_match(ngay, regex(R"(\d{2}/\d{2}/\d{4})"));
}

bool kiemTraGioiTinh(const string& gt) {
    string lower = gt;
    for (char& c : lower) c = tolower(c);
    return (lower == "nam" || lower == "nu");
}

bool kiemTraSoNguyen(const string& input) {
    return !input.empty() && all_of(input.begin(), input.end(), ::isdigit);
}

bool kiemTraSDT(const string& sdt) {
    return sdt.length() == 10 && kiemTraSoNguyen(sdt);
}

bool kiemTraCCCD(const string& cccd) {
    return cccd.length() == 12 && kiemTraSoNguyen(cccd);
}

bool kiemTraBHYT(const string& bhyt) {
    if (bhyt.length() != 15)
        return false;
    if (!isupper(bhyt[0]) || !isupper(bhyt[1]))
        return false;
    for (size_t i = 2; i < bhyt.length(); ++i) {
        if (!isdigit(bhyt[i]))
            return false;
    }
    return true;
}

// Kiểm tra định dạng ngày và giờ: dd/mm/yyyy hh:mm (24h)
bool kiemTraNgayGio(const string& ngayGio) {
    // Ví dụ: "21/05/2025 14:30"
    regex rg("^\\d{2}/\\d{2}/\\d{4} \\d{2}:\\d{2}$");
    if (!regex_match(ngayGio, rg)) return false;

    // Kiểm tra sâu hơn: hợp lệ ngày, giờ
    int dd, mm, yyyy, hh, min;
    if (sscanf(ngayGio.c_str(), "%d/%d/%d %d:%d", &dd, &mm, &yyyy, &hh, &min) != 5)
        return false;

    if (dd < 1 || dd > 31 || mm < 1 || mm > 12 || yyyy < 1900 || yyyy > 2100)
        return false;
    if (hh < 0 || hh > 23 || min < 0 || min > 59)
        return false;

    return true;
}
bool kiemTraMatKhau(const string& mk) {
    if (mk.length() > 8) return false;

    bool coChuHoa = false;
    bool coSo = false;
    bool coDacBiet = false;

    for (char c : mk) {
        if (isupper(c)) coChuHoa = true;
        else if (isdigit(c)) coSo = true;
        else if (ispunct(c)) coDacBiet = true;
    }

    return coChuHoa && coSo && coDacBiet;
}