# Quan_Ly_Diem_Sinh_Vien_Theo_He_Tin_Chi
Ta tổ chức các danh sách sau: 
- Danh sách môn học: cây nhị phân tìm kiếm cân bằng(MAMH (C10), TENMH (C50), STCLT (số tín chỉ lý thuyết – số nguyên), STCTH (số tín chỉ thực hành – số nguyên))
- Danh sách Lop sinh viên: danh sách tuyến tính là 1 mảng con trỏ có tối đa 10000 lớp. Mỗi lớp có thông tin (MALOP (C15), TENLOP, con trỏ): con trỏ sẻ trỏ đến danh sách sinh viên thuộc lớp đó.
- Danh sách sinh viên : danh sách liên kết đơn (MASV (C15), HO, TEN,  PHAI, SODT)
- Danh sách Lop Tín chỉ: danh sách liên kết đơn, mỗi lớp tín chỉ có các thông tin (MALOPTC (số nguyên tự động tăng),  MAMH, Niên khóa, Học kỳ, Nhóm, số sv min, số sv max, hủy lớp (boolean), con trỏ dssvdk): con trỏ dssvdk sẻ trỏ đến danh sách sinh viên  đăng ký lớp tín chỉ.
- Danh sách Đăng ký (danh sách liên kết đơn): ( MASV ,   DIEM (số thực), hủy đăng ký (bool))
