#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define NOMINMAX
#include <iostream>
#include <string>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include <ctime>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>

#pragma comment(lib, "ws2_32.lib")

class MiniWebServer {
private:
    SOCKET server_fd;
    const int PORT = 8080;
    int request_count = 0;
    std::time_t start_time = std::time(0);

    std::string getMimeType(const std::string& path) {
        if (path.find(".html") != std::string::npos) return "text/html";
        if (path.find(".css") != std::string::npos) return "text/css";
        if (path.find(".js") != std::string::npos) return "application/javascript";
        return "application/octet-stream";
    }

    std::string getCurrentTime() {
        auto now = std::time(nullptr);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

    void sendResponse(SOCKET client, std::string status, std::string type, std::string body) {
        std::string res = "HTTP/1.1 " + status + "\r\n";
        res += "Content-Type: " + type + "\r\n";
        res += "Content-Length: " + std::to_string(body.length()) + "\r\n";
        res += "Connection: close\r\n\r\n" + body;
        send(client, res.c_str(), (int)res.length(), 0);
    }

public:
    MiniWebServer() {
        WSADATA wsa;
        WSAStartup(MAKEWORD(2,2), &wsa);
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        
        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(PORT);
        
        bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
        listen(server_fd, 5);
        std::cout << "Server started at http://localhost:8080" << std::endl;
    }

    void start() {
        while(true) {
            SOCKET client = accept(server_fd, NULL, NULL);
            if (client != INVALID_SOCKET) {
                request_count++; 
                
                char buf[2048] = {0};
                recv(client, buf, 2048, 0);
                
                std::string req(buf);
                std::stringstream ss(req);
                std::string method, path;
                ss >> method >> path;

                // --- 1. API Status Logic ---
                if (path == "/api/status") {
                    int uptime = (int)std::difftime(std::time(0), start_time);
                    std::string json = "{";
                    json += "\"uptime\": \"" + std::to_string(uptime) + "s\",";
                    json += "\"requests\": " + std::to_string(request_count) + ",";
                    json += "\"status\": \"Online\"";
                    json += "}";
                    sendResponse(client, "200 OK", "application/json", json);
                }
                // --- 2. API Time Logic ---
                else if (path == "/api/time") {
                    std::string timeJson = "{\"time\":\"" + getCurrentTime() + "\"}";
                    sendResponse(client, "200 OK", "application/json", timeJson);
                }
                // --- 3. UI/Static Files Logic ---
                else {
                    std::string filePath = (path == "/") ? "/index.html" : path;
                    
                    // EXE agar 'src' folder mein hai, toh ek level bahar jaake 'public' dhundo
                    std::string fullPath = "../public" + filePath; 

                    std::ifstream file(fullPath, std::ios::binary);
                    if (file.is_open()) {
                        std::stringstream buffer;
                        buffer << file.rdbuf();
                        sendResponse(client, "200 OK", getMimeType(filePath), buffer.str());
                        std::cout << "Success: Served " << fullPath << std::endl;
                    } else {
                        // Agar file nahi mili toh console pe path print karo debug ke liye
                        sendResponse(client, "404 Not Found", "text/plain", "404: File Not Found");
                        std::cout << "Error: Could not find " << fullPath << std::endl;
                    }
                }
                closesocket(client);
            }
        }
    }

    ~MiniWebServer() {
        closesocket(server_fd);
        WSACleanup();
    }
};

int main() {
    MiniWebServer server;
    server.start();
    return 0;
}