#include<stdio.h>
#include <xlsxwriter.h>
int main() {
    // 创建Excel文件和工作表对象
    lxw_workbook  *workbook = workbook_new("data.xlsx");
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);

    // 定义单元格格式
    lxw_format *header_format = workbook_add_format(workbook);
    format_set_bold(header_format);
    format_set_font_size(header_format, 12);

    // 编写标题行，输出到Excel中
    worksheet_write_string(worksheet, 0, 0, "姓名", header_format);
    worksheet_write_string(worksheet, 0, 1, "年龄", header_format);
    worksheet_write_string(worksheet, 0, 2, "性别", header_format);

    // 编写数据行，输出到Excel中
    worksheet_write_string(worksheet, 1, 0, "张三", NULL);
    worksheet_write_number(worksheet, 1, 1, 25, NULL);
    worksheet_write_string(worksheet, 1, 2, "男", NULL);

    worksheet_write_string(worksheet, 2, 0, "李四", NULL);
    worksheet_write_number(worksheet, 2, 1, 30, NULL);
    worksheet_write_string(worksheet, 2, 2, "女", NULL);

    worksheet_write_string(worksheet, 3, 0, "王五", NULL);
    worksheet_write_number(worksheet, 3, 1, 28, NULL);
    worksheet_write_string(worksheet, 3, 2, "男", NULL);

    // 关闭并保存Excel文件
    workbook_close(workbook);
    return 0;
}