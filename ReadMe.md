# Read This PC detail:
### TRƯƠNG QUANG TUẤN -1512640
#### Email: 1512640@student.hcmus.edu.vn
**I. Các chức năng**

1.Tạo ra TreeView bên trái, ListView bên phải.

2.Về TreeView 

<ul>
<li> Tạo node root là This PC</li>	
<li> Lấy danh sách các ổ đĩa trong máy bằng hàm GetLogicalDriveStrings, thêm các ổ đĩa vào node root, tạo sẵn thuộc tính cChildren = true để báo hiệu có các node con. </li>
<li> Bắt sự kiện Expanding, lấy ra đường dẫn dấu ở PARAM để biết mình phải xư lí thư mục nào, duyệt nội dung thư mục bằng FindFirstFile & FindNextFile, chỉ lấy các thư mục để thêm vào làm node con.</li>
</ul>
3.Về ListView 
<ul>
<li> Hiển thị toàn bộ thư mục và tập tin tương ứng với một đường dẫn. </li>
<li> Bấm đôi vào một thư mục sẽ thấy toàn bộ thư mục con và tập tin. </li>
</li> Tạo ra ListView có 4 cột: Tên, Loại, Thời gian chỉnh sửa, Dung lượng. </li>
</ul>
**II. Luồng sự kiện chính**
1.Chạy chương trình lên, hiển thị node This PC trên TreeView bên trái ở trạng thái collapse (thu gọn). Bấm vào sẽ xổ xuống các node con là danh sách ổ đĩa.
2. Bên ListView sẽ hiển thị các tập tin hoặc thư mục con tương ứng với TreeView. Double click để mở thư mục con hoặc chương trình mở mặc định đối với tập tin.
**III. Các luồng sự kiện phụ**
1.Cấp phát bộ nhớ động thay vì bộ nhớ tĩnh

