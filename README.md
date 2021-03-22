# unhappy_evolution

## Description

A collection of small functions for daily use.

### Tools

1. Parse json string. Then format it into plain formatted string and formatted structure table view.

+ parse to plain string.
 ![img.png](static/readme/example_json_to_plain_string.png)
  
+ parse to structure.
![img.png](static/readme/example_json_to_structure.png)
  
2. Drag UTF-8 files to window. Then transform these files into GB18030. This is used for mac users sending csv files to windows user.

![img.png](static/readme/example_transform_utf8_to_gbk.png)

3. Drag big csv files and preview lines by your config.

+ You will get summary in this page.
![img.png](static/readme/example_preview_csv.png)
  
+ You will get csv content in this page.
![img.png](static/readme/example_preview_csv_detail.png)
  
Build

+ Install qt5.15.2 on your mac.
+ Found you clang in qt5.15.2 directory and set your clang directory.
+ Build this project with cmake.