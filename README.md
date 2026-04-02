# CrapDB

Small SQL-Like Database in C

---

### Database layout

*Columns*:

| ID: uint32 | USERNAME: 32 byte char | EMAIL: 255 bye char |

*Table*:

1 table, 4Kb per page, 100 pages

---

### SQL Commands

CrapDB currently support 3 SQL-Like commands

- `SELECT` 
- `INSERT`
- `DELETE`

With 2 Meta commands:

- `.help`
- `.exit`

---

### Platform

Developed and tested on Linux with gcc, not sure if it works on windows
