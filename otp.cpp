#include "otp.h"
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <ctime>
#include <cmath>

// Định nghĩa secret cố định
const std::string OTP::secret = "MYAPPSECRET12345"; // Đúng cú pháp
time_t OTP::otpGeneratedTime = 0;

std::string OTP::generateTOTP(size_t digits, int period) {
    // Lưu thời gian tạo OTP
    otpGeneratedTime = time(nullptr);

    // Lấy thời gian hiện tại và tính số bước thời gian (time step)
    uint64_t time_step = static_cast<uint64_t>(otpGeneratedTime) / period;

    // Chuyển time_step thành dạng binary (big-endian)
    std::vector<uint8_t> time_bytes(8);
    for (int i = 7; i >= 0; --i) {
        time_bytes[i] = static_cast<uint8_t>(time_step & 0xFF);
        time_step >>= 8;
    }

    // Tính HMAC-SHA1 với secret cố định
    std::vector<uint8_t> hmac_result = hmac_sha1(secret, time_bytes);

    // Dynamic truncation (theo RFC 4226)
    int offset = hmac_result[hmac_result.size() - 1] & 0x0F;
    uint32_t binary_code = 
        ((hmac_result[offset] & 0x7F) << 24) |
        ((hmac_result[offset + 1] & 0xFF) << 16) |
        ((hmac_result[offset + 2] & 0xFF) << 8) |
        (hmac_result[offset + 3] & 0xFF);

    // Lấy số chữ số mong muốn
    binary_code = binary_code % static_cast<uint32_t>(std::pow(10, digits));
    
    // Định dạng mã OTP với số 0 đằng trước nếu cần
    std::string otp = std::to_string(binary_code);
    while (otp.length() < digits) {
        otp = "0" + otp;
    }
    return otp;
}

std::vector<uint8_t> OTP::hmac_sha1(const std::string& key, const std::vector<uint8_t>& message) {
    std::vector<uint8_t> result(EVP_MAX_MD_SIZE);
    unsigned int result_len = 0;

    HMAC(EVP_sha1(),
         key.data(), key.size(),
         message.data(), message.size(),
         result.data(), &result_len);

    result.resize(result_len);
    return result;
}
