#pragma once

namespace Console
{
	extern void Size(HWND console, int width, int height);
	extern void Alpha(HWND console);
	extern std::string RandomStr(const size_t length);
	extern std::string Encrypt(const std::string& data);
	extern std::string Decrypt(const std::string& encryptedData);
}