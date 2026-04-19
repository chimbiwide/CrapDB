# CrapDB

Small SQL-Like Database in C

---

### Database layout

*Columns*:

| ID: uint32 | USERNAME: 32 byte char | BIO: 255 byte char |

*Table*:

1 table, 4Kb per page, 100 pages

---

### SQL Commands

CrapDB currently support 3 SQL-Like commands

- `SELECT` 
- `INSERT`
- `DELETE`
- `UPDATE`
- `COUNT`

With 2 Meta commands:

- `.help`
- `.exit`

---

### Compiling

Requirements: **gcc**/**clang** **make**

Tested to work on Linux and MacOS.
