# 中崙高中資訊研習社 2026 Rev/Pwn 小社課資源

> Author: Grissia

## 題目平台

[ctfd.grissia.com](https://ctfd.grissia.com)

## 注意事項

- 為了方便教學，這個 repo 裡面包含我個人的 exploit 供大家對答案，但是**請不要直接抄**，卡關時自己反覆刁鑽思考也是學習的一環
- 同上，這裡也包含所有 server 端的題目原始碼，但是**解題所需的所有資訊都在 ctfd 上，不要直接參考這邊的資料**
- Good luck, have fun, and happy hacking!

## 專案目錄

```text
ZLCSC_Course_Materials/
├── install.sh                  # 一鍵安裝教學環境
├── README.md                   # 專案主說明
├── docs/                       # 課堂補充教材與範例
│   ├── README.md               # docs 使用說明
│   └── reverse1/               # Reverse 1 相關教材
├── slides/                     # 課程投影片（目前可放置於此）
└── src/                        # 題目服務端原始碼與部署設定
    ├── docker-compose.yml      # 本機啟動題目容器
    ├── pwn/                    # Pwn 題目目錄
    │   ├── nc/
    │   └── ret2win-0/
    └── rev/                    # Reverse 題目目錄
        ├── asm-0/
        ├── crackme-0/
        └── crackme-1/
```


## 課程大綱

- Reverse 1
    - All about reverse: logically & technically
    - Compiler & Assembler
    - Opcode & Assembly
    - Assembly basics
    - Tools installation -> gdb, ida, pwntools, etc 
- Reverse 2
    - ELF structure
    - Stack & Heap
    - Ida free usage
    - *crackme-0*
    - *crackme-1*
- Pwn 1
    - All about PWN
    - Integer Overflow
    - Out of Bound
    - Pwntools basics
    - GDB basics
    - Stack Overflow
- Pwn 2
    - Function prologue and epilogue
    - *ret2win-0*
    - *ret2win-1*
    - Stack-based Protection
    - *ret2win-2*
    - *ret2win-3*
- Pwn 3
    - GNU C Library
    - *ret2libc-0*
    - Dynamic & Static Linking
    - Return Oriented Programming
    - *rop-0*
    - *ret2libc-1*
    - *ret2libc-2*