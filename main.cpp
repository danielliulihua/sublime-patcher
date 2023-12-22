#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>

#ifdef __linux__
int main() {
    const char* filePath = "sublime_text";
    std::fstream file(filePath, std::ios::in | std::ios::out | std::ios::binary);

    std::vector<unsigned char> srPtr = { 0x80, 0x78, 0x05, 0x00, 0x0F, 0x94, 0xC1 };
    std::vector<unsigned char> rpPtr = { 0xC6, 0x40, 0x05, 0x01, 0x48, 0x85, 0xC9 };

    const size_t chunkSize = 1024 * 1024;
    std::vector<unsigned char> chunk(chunkSize);

    size_t fileSize = 0;

    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    while (file.read(reinterpret_cast<char*>(chunk.data()), chunkSize)) {
        auto it = std::search(chunk.begin(), chunk.end(), srPtr.begin(), srPtr.end());
        while (it != chunk.end()) {
            std::copy(rpPtr.begin(), rpPtr.end(), it);
            it = std::search(it + srPtr.size(), chunk.end(), srPtr.begin(), srPtr.end());
        }
        file.seekp(-static_cast<std::streamoff>(chunkSize), std::ios::cur);
        file.write(reinterpret_cast<const char*>(chunk.data()), chunk.size());

        file.seekp(0, std::ios::end);
    }
    file.close();
    if (system(("sudo chmod 755 " + std::string(filePath)).c_str()) != 0) {
        return 1;
    }
    if (system(("sudo chown root " + std::string(filePath)).c_str()) != 0) {
        return 1;
    }
    if (system(("sudo chgrp root " + std::string(filePath)).c_str()) != 0) {
        return 1;
    }
    std::cout << "Patched successfully" << std::endl;
    return 0;
}
#else
int main() {
    const char* filePath = "sublime_text.exe";
    std::fstream file("sublime_text.exe", std::ios::in | std::ios::out | std::ios::binary);
    file.seekg(0, std::ios::end);
    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<unsigned char> content(fileSize);
    file.read(reinterpret_cast<char*>(content.data()), fileSize);

    std::vector<unsigned char> srPtr = { 0x80, 0x78, 0x05, 0x00, 0x0F, 0x94, 0xC1 };
    std::vector<unsigned char> rpPtr = { 0xC6, 0x40, 0x05, 0x01, 0x48, 0x85, 0xC9 };

    auto it = std::search(content.begin(), content.end(), srPtr.begin(), srPtr.end());
    while (it != content.end()) {
        std::copy(rpPtr.begin(), rpPtr.end(), it);
        it = std::search(it + srPtr.size(), content.end(), srPtr.begin(), srPtr.end());
    }
    file.seekp(0, std::ios::beg);
    file.write(reinterpret_cast<const char*>(content.data()), fileSize);

    std::cout << "Patched successfully" << std::endl;
    file.close();
    return 0;
}
#endif
