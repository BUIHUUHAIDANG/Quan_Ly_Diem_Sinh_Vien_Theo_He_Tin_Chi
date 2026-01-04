# 📚 HỆ THỐNG QUẢN LÝ ĐIỂM SINH VIÊN THEO HỆ TÍN CHỈ

## 1. Giới thiệu
Dự án **Quản lý điểm sinh viên theo hệ tín chỉ** mô phỏng một hệ thống quản lý đào tạo trong các trường đại học, cho phép quản lý **môn học, lớp sinh viên, sinh viên, lớp tín chỉ, đăng ký học phần và điểm số**.
## Người thực hiện

Dự án được thực hiện bởi nhóm sinh viên với mục tiêu rèn luyện kỹ năng lập trình C/C++, 
vận dụng cấu trúc dữ liệu và giải quyết bài toán quản lý thực tế trong môi trường đại học.

**Thành viên nhóm:**
- Sinh viên 1: Bùi Hữu Hải Đăng
- Sinh viên 2: Vũ Anh Khoa
- Sinh viên 3: Lê Trần Hoàng Minh

**Phân công công việc (tham khảo):**
- Thiết kế cấu trúc dữ liệu và kiến trúc chương trình
- Xây dựng các danh sách: Môn học, Sinh viên, Lớp sinh viên
- Xây dựng chức năng Lớp tín chỉ, Đăng ký, Nhập điểm
- Xử lý lưu / load file và kiểm tra ràng buộc dữ liệu
- Kiểm thử và hoàn thiện chương trình

Chương trình được xây dựng bằng **C/C++**, tập trung vào:
- Cấu trúc dữ liệu
- Tối ưu bộ nhớ
---

## 2. Các cấu trúc dữ liệu sử dụng

### 2.1. Danh sách Môn học
- **Cấu trúc**: Cây nhị phân tìm kiếm cân bằng (BST)
- **Thông tin**:
  - `MAMH` (char[10])
  - `TENMH` (char[50])
  - `STCLT` (int) – số tín chỉ lý thuyết
  - `STCTH` (int) – số tín chỉ thực hành

---

### 2.2. Danh sách Lớp sinh viên
- **Cấu trúc**: Mảng con trỏ (tối đa 10.000 lớp)
- **Thông tin**:
  - `MALOP` (char[15])
  - `TENLOP`
  - Con trỏ trỏ đến danh sách sinh viên của lớp


---

### 2.3. Danh sách Sinh viên
- **Cấu trúc**: Danh sách liên kết đơn
- **Thông tin**:
  - `MASV` (char[15])
  - `HO`
  - `TEN`
  - `PHAI`
  - `SODT`
  - `MALOP`


---

### 2.4. Danh sách Lớp tín chỉ
- **Cấu trúc**: Danh sách liên kết đơn
- **Thông tin**:
  - `MALOPTC` (int – tự động tăng)
  - `MAMH`
  - `NIENKHOA`
  - `HOCKY`
  - `NHOM`
  - `SOSVMIN`
  - `SOSVMAX` (≤ 999)
  - `HUYLOP` (bool)
  - Con trỏ `dssvdk` → danh sách sinh viên đăng ký


---

### 2.5. Danh sách Đăng ký
- **Cấu trúc**: Danh sách liên kết đơn
- **Thông tin**:
  - `MASV`
  - `DIEM` (float)
  - `HUYDK` (bool)
  - `MALOPTC`


---

## 3. Các chức năng chính

### a. Mở lớp tín chỉ
- Thêm lớp tín chỉ (ở cuối)
- Xóa lớp tín chỉ (3 vị trí)
- Hiệu chỉnh thông tin lớp tín chỉ

---

### b. In danh sách sinh viên đăng ký lớp tín chỉ
Theo 4 tham số:
- Niên khóa
- Học kỳ
- Nhóm
- Mã môn học

---

### c. Nhập lớp – Nhập sinh viên
- Nhập mã lớp trước
- Nhập nhiều sinh viên cho lớp
- Hỗ trợ:
  - Thêm
  - Xóa
  - Hiệu chỉnh
- Kết thúc khi nhập **MASV rỗng**

---

### d. In danh sách sinh viên của 1 lớp
- Sắp xếp tăng dần theo **TEN + HO (ASCII)**

---

### e. Nhập môn học
- Thêm / Xóa / Hiệu chỉnh môn học

---

### f. In danh sách môn học
- In tăng dần theo **tên môn học**

---

### g. Đăng ký lớp tín chỉ
- Sinh viên nhập `MASV`
- Hệ thống hiển thị thông tin sinh viên
- Nhập **Niên khóa + Học kỳ**
- In các lớp tín chỉ đã mở gồm:
  - MAMH
  - TENMH
  - NHOM
  - Số SV đã đăng ký
  - Số slot còn trống

---

### h. Hủy lớp tín chỉ
- Tự động hủy lớp có số SV đăng ký < SOSVMIN
- Theo niên khóa, học kỳ
- Có xác nhận người dùng

---

### i. Nhập điểm
- Theo niên khóa, học kỳ, nhóm, môn học
- In danh sách:
## 4. Lưu trữ dữ liệu
- Tất cả danh sách đều hỗ trợ:
  - Lưu file
  - Load file
- Kiểm tra dữ liệu nhập:
  - Trùng mã
  - Sai định dạng
  - Vượt giới hạn

---

## 5. Công nghệ sử dụng
- Ngôn ngữ: **C / C++**
- Cấu trúc dữ liệu:
  - Binary Search Tree
  - Linked List
  - Array of Pointers
- File nhị phân

---

## 6. Mục tiêu
- Áp dụng cấu trúc dữ liệu vào bài toán thực tế
- Quản lý chương trình lớn
- Tối ưu bộ nhớ


## Cài đặt và chạy chương trình

### 1. Yêu cầu hệ thống
- Hệ điều hành: Windows / Linux
- Trình biên dịch:  
  - GCC (g++) hoặc  
  - MinGW / Visual Studio (C++)
- Chuẩn ngôn ngữ: C++11 trở lên

---
---
Project/
│── main.cpp
│── MonHoc.h / MonHoc.cpp
│── SinhVien.h / SinhVien.cpp
│── LopSinhVien.h / LopSinhVien.cpp
│── LopTinChi.h / LopTinChi.cpp
│── DangKy.h / DangKy.cpp
│── data/
│   ├── monhoc.dat
│   ├── sinhvien.dat
│   ├── lopsv.dat
│   ├── loptinchi.dat
│   └── dangky.dat
### 2. Biên dịch chương trình

**Sử dụng g++:**
g++ main.cpp MonHoc.cpp LopSinhVien.cpp mylib.cpp CTDL.cpp menu.cpp -o main
### 3. Chạy chương trình
./main


