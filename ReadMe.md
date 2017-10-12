# Read This PC detail:
### TRƯƠNG QUANG TUẤN -1512640
#### Email: 1512640@student.hcmus.edu.vn
**1.Các chức năng:**
       - Tạo ra TreeView bên trái, ListView bên phải. 
       - Về TreeView: 
            <ul>
<li>+Tạo node root là This PC</li>	
           <li> +Lấy danh sách các ổ đĩa trong máy bằng hàm GetLogicalDriveStrings, thêm các ổ đĩa vào node root, tạo sẵn thuộc tính cChildren = true để báo hiệu có các node con. </li>
            <li>+Bắt sự kiện Expanding, lấy ra đường dẫn dấu ở PARAM để biết mình phải xư lí thư mục nào, duyệt nội dung thư mục bằng FindFirstFile & FindNextFile, chỉ lấy các thư mục để thêm vào làm node con.</li>
</ul>
         -Về ListView:
            + Hiển thị toàn bộ thư mục và tập tin tương ứng với một đường dẫn
            + Bấm đôi vào một thư mục sẽ thấy toàn bộ thư mục con và tập tin.
            + Tạo ra ListView có 4 cột: Tên, Loại, Thời gian chỉnh sửa, Dung lượng. 
**2. Luồng sự kiện chính:**
           - Chạy chương trình lên, hiển thị node This PC trên TreeView bên trái ở trạng thái collapse (thu gọn). Bấm vào sẽ xổ xuống các node con là danh sách ổ đĩa.
           - Bên ListView sẽ hiển thị các tập tin hoặc thư mục con tương ứng với TreeView. Double click để mở thư mục con hoặc chương trình mở mặc định đối với tập tin.
**3. Các luồng sự kiện phụ:**
            - Cấp phát bộ nhớ động thay vì bộ nhớ tĩnh.

