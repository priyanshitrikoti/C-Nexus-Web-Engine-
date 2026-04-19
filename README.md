# C-Nexus-Web-Engine-
A lightweight, high-performance Mini Web Server built from scratch using C++ and Windows Socket Programming (Winsock2) featuring a real-time dashboard.
# 🌐 C-Nexus: High-Performance C++ Web Engine

A lightweight and efficient **Mini Web Server** built from scratch using **C++** and **Windows Socket Programming (Winsock2)**. This project demonstrates the core mechanics of the HTTP protocol, networking, and server-side logic without using any high-level frameworks.

---

## 🚀 Features

- **Socket-Level Communication:** Built using the `Winsock2` library for low-level network control.
- **Dynamic Server Status:** Real-time tracking of Server Uptime, Request Counts, and Live Status.
- **Real-Time Clock API:** A dedicated endpoint that serves the current system time dynamically to the frontend.
- **Interactive Form (GET/POST):** Fully functional handling of HTTP GET and POST methods with JSON-style data feedback.
- **API Tester:** Built-in UI to test various endpoints like `/api/time`, `/api/status`, and CSS loading.
- **Modern UI:** A clean, responsive dashboard designed with HTML5 and CSS3.

---

## 🛠️ Tech Stack

- **Backend:** C++ (Standard ISO/IEC 14882)
- **Networking:** Winsock2 API (Windows Sockets)
- **Frontend:** HTML5, CSS3, JavaScript (for API calls)
- **Protocol:** HTTP/1.1

---

## 📸 Screenshots

| Dashboard Overview | Form Handling & API Test |
|---|---|
| ![Dashboard](https://via.placeholder.com/400x250?text=Server+Status+UI) | ![Form](https://via.placeholder.com/400x250?text=GET+POST+Handling) |
*(Note: Replace these placeholders with your actual images after uploading them to GitHub)*

---

## ⚙️ Implementation Details

- **Initialization:** Uses `WSAStartup` to initialize the Windows socket environment.
- **Request Parsing:** Manually parses HTTP request lines to identify Methods (GET/POST) and URIs.
- **Response Construction:** Generates standard-compliant HTTP headers including `Content-Type`, `Content-Length`, and `Connection`.
- **API Logic:** Implements specialized routing for `/api/time` to provide real-time backend data.

---

## 🏃 How to Run

1. **Prerequisites:** A C++ compiler (GCC/MinGW or Visual Studio) on a Windows machine.
2. **Clone the Repo:**
   ```bash
   git clone [https://github.com/yourusername/C-Nexus-Web-Engine.git](https://github.com/yourusername/C-Nexus-Web-Engine.git)
