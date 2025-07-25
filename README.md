# 📚 Library Management System in C++

A simple and interactive **Library Management System** built using **C++**, designed for managing book checkouts, returns, and borrower records. Ideal for small libraries or educational demo projects.

---

## 🧠 Features

✅ Add new books to the library  
🔍 Search for books by **Title**, **Author**, or **ISBN**  
📥 Checkout books with **automatic 7-day due date**  
📤 Return books and calculate **late fines** (₹5 per day)  
📌 Track real-time book availability  
👨‍🏫 Maintain borrower details  

---

## 🛠️ Tech Stack

- **Language:** C++  
- **Libraries:**  
  - `<iostream>` – for input/output  
  - `<vector>` – to manage lists of books and borrowers  
  - `<string>` – for handling text data  
  - `<ctime>` – to manage due dates and time calculations  
  - `<algorithm>` – to help remove borrower records  

---

## 🧮 Fine Policy

- Users are given **7 days** to return a checked-out book.
- If a book is returned late, the fine is **₹5 per day** overdue.
- Fine is automatically calculated during the return process.

---
