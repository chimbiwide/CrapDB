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

With 2 Meta commands:

- `.help`
- `.exit`

---

### Platform

This database is designed to run on Linux systems only, as auto completion depends on `readline-dev` which is a GNU library. Future ports to Unix systems might be possible.
